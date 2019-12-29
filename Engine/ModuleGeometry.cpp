#include "Globals.h"
#include "ModuleGeometry.h"
#include "Application.h"
#include "SceneImporter.h"

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cfileio.h"
#pragma comment (lib, "Assimp/libx86/assimp.lib")

#include "glew/include/GL/glew.h"
#include "SDL/include/SDL_opengl.h"

#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */
#pragma comment(lib, "glew/libx86/glew32.lib")

#include "mmgr/mmgr.h"

ModuleGeometry::ModuleGeometry(bool start_enabled) : Module(start_enabled)
{}

ModuleGeometry::~ModuleGeometry()
{}

bool ModuleGeometry::Start()
{
	bool ret = true;

	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);

	return ret;
}

update_status ModuleGeometry::PreUpdate(float dt)
{

	return UPDATE_CONTINUE;
}

update_status ModuleGeometry::Update(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleGeometry::PostUpdate(float dt)
{

	return UPDATE_CONTINUE;
}

bool ModuleGeometry::CleanUp()
{
	bool ret = true;

	aiDetachAllLogStreams();
	return ret;
}

void ModuleGeometry::LoadFileFromPath(std::string full_path)
{
	const aiScene* file = aiImportFile(full_path.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);

	if (file != nullptr && file->HasMeshes()) //Load sucesful
	{
		aiNode* node = file->mRootNode;

		GameObject* goLoader = App->viewport->CreateGameObject();
		std::string goName = App->GetNameFromPath(full_path);

		goLoader->name = goName;
		goLoader->unactive_name = goName.append(" [not active]");

		//Define the gameobject as a child of the RootNode
		App->viewport->root->DefineChilds(goLoader);

		//Importer mesh
		SceneImporter exporter;
		std::string output_file;

		if (node->mNumChildren > 0)
		{
			for (int i = 0; i < node->mNumChildren; ++i)
			{
				LoadNodeFromParent(file, node->mChildren[i], goLoader, full_path, exporter, output_file);
			}
		}

		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		aiReleaseImport(file);
		App->Console_Log("Succesfully loaded mesh with path: %s", full_path);
	}
	else
		App->Console_Log("[WARNING]: Error loading mesh with path %s", full_path);
}

void ModuleGeometry::LoadNodeFromParent(const aiScene* file, aiNode* node, GameObject* parent, std::string full_path, SceneImporter exporter, std::string output_file)
{
	aiVector3D nPosition;
	aiVector3D nScaling;
	aiQuaternion nRotation;

	//Decomposing transform matrix into translation rotation and scale
	node->mTransformation.Decompose(nScaling, nRotation, nPosition);

	float3 nPos(nPosition.x, nPosition.y, nPosition.z);
	float3 nScale(nScaling.x, nScaling.y, nScaling.z);
	Quat nRot(nRotation.x, nRotation.y, nRotation.z, nRotation.w);

	//Skipp all dummy modules. Assimp loads this fbx nodes to stack all transformations
	std::string node_name = node->mName.C_Str();

	bool dummyFound = true;

	while (dummyFound)
	{
		//All dummy modules have one children (next dummy module or last module containing the mesh)
		if (node_name.find("_$AssimpFbx$_") != std::string::npos && node->mNumChildren == 1)
		{
			//Dummy module have only one child node, so we use that one as our next GameObject
			node = node->mChildren[0];

			// Accumulate transform 
			node->mTransformation.Decompose(nScaling, nRotation, nPosition);

			node_name = node->mName.C_Str();

			//if we find a dummy node we "change" our current node into the dummy one and search
			//for other dummy nodes inside that one.
			dummyFound = true;
		}
		else
			dummyFound = false;
	}

	GameObject* obj = App->viewport->CreateGameObject();
	ComponentTransform* transform = obj->GetComponentTransform();

	//Adding mTransformation to the Loader GameObject.
	transform->SetPosition(nPos);
	transform->SetScale(nScale);
	transform->SetQuatRotation(nRot);

	// Childs of parent 
	parent->DefineChilds(obj);
	obj->name = node_name;
	obj->unactive_name = node_name.append(" [not active]");

	// Store initial values so then we can RESET the position, scale and rotation.
	obj->reset_pos = nPos;
	obj->reset_rotation = nRot;
	obj->reset_scale = nScale;

	// Use scene->mNumMeshes to iterate on scene->mMeshes array
	for (int i = 0; i < node->mNumMeshes; ++i)
	{
		aiMesh* new_mesh = file->mMeshes[node->mMeshes[i]];

		GameObject* child = nullptr;

		if (node->mNumMeshes > 1)
		{
			node_name = new_mesh->mName.C_Str();

			if (node_name == "")
				node_name = obj->name + "_submesh";
			if (i > 0)
				node_name.append(" (" + std::to_string(i + 1) + ")");

			child = App->viewport->CreateGameObject();
			obj->DefineChilds(child);
			child->name = node_name;
			child->unactive_name = node_name.append(" [not active]");
		}
		else
		{
			child = obj;
		}

		child->CreateComponent(Component::Type::MESH);
		ComponentMesh* mesh = child->GetComponentMesh();

		DefineTextureType(file, new_mesh, child, full_path);

		mesh->num_vertex = new_mesh->mNumVertices;
		mesh->vertices = new float3[mesh->num_vertex];

		for (uint i = 0; i < new_mesh->mNumVertices; ++i)
		{
			mesh->vertices[i].x = new_mesh->mVertices[i].x;
			mesh->vertices[i].y = new_mesh->mVertices[i].y;
			mesh->vertices[i].z = new_mesh->mVertices[i].z;
		}

		if (new_mesh->HasFaces())
		{
			mesh->num_index = new_mesh->mNumFaces * 3;
			mesh->indices = new uint[mesh->num_index]; // assume each face is a triangle

			for (uint i = 0; i < new_mesh->mNumFaces; ++i)
			{
				if (new_mesh->mFaces[i].mNumIndices != 3)
					App->Console_Log("WARNING, geometry face with != 3 indices!");
				else
					memcpy(&mesh->indices[i * 3], new_mesh->mFaces[i].mIndices, 3 * sizeof(uint));
			}
		}
		if (new_mesh->HasTextureCoords(0))
		{
			mesh->num_texture = mesh->num_vertex;
			mesh->texture_coords = new float[mesh->num_texture * 2];

			for (int i = 0; i < mesh->num_texture; ++i)
			{
				mesh->texture_coords[i * 2] = new_mesh->mTextureCoords[0][i].x;
				mesh->texture_coords[(i * 2) + 1] = new_mesh->mTextureCoords[0][i].y;
			}
		}

		mesh->UpdateAABB();

		exporter.ExportMesh(child->name.data(), LIBRARY_MESH_FOLDER, output_file, mesh);

		//Generate buffer for each mesh and send vertex, indices and textures to VRAM
		VertexBuffer(mesh->id_vertex, mesh->num_vertex, mesh->vertices);
		IndexBuffer(mesh->id_index, mesh->num_index, mesh->indices);
		TextureBuffer(mesh->id_texture, mesh->num_texture, mesh->texture_coords);

		//App->scene_intro->static_meshes.push_back(obj->mesh);
	}

	if (node->mNumChildren > 0)
	{
		for (int i = 0; i < node->mNumChildren; ++i)
		{
			LoadNodeFromParent(file, node->mChildren[i], obj, full_path, exporter, output_file);
		}
	}
}

void ModuleGeometry::LoadParShapes(par_shapes_mesh* par_mesh, Position pos)
{
	GameObject* obj = App->viewport->CreateGameObject();
	App->viewport->root->DefineChilds(obj);

	obj->CreateComponent(Component::Type::MESH);
	ComponentMesh* mesh = obj->GetComponentMesh();

	// VERTEX ----------------
	mesh->num_vertex = par_mesh->npoints;
	mesh->vertices = new float3[mesh->num_vertex];

	for (int i = 0; i < mesh->num_vertex; i++)
	{
		int j = i * 3;
		mesh->vertices[i].x = par_mesh->points[j];
		mesh->vertices[i].y = par_mesh->points[j + 1];
		mesh->vertices[i].z = par_mesh->points[j + 2];
	}

	// INDEX ------------
	mesh->num_index = par_mesh->ntriangles * 3;
	mesh->indices = new uint[mesh->num_index];

	for (int i = 0; i < mesh->num_index; i++)
	{
		mesh->indices[i] = (uint)par_mesh->triangles[i];
	}

	// TEXTURE ----------------
	mesh->num_texture = par_mesh->npoints;
	mesh->texture_coords = new float[mesh->num_texture * 2];

	//Copy the par_shapes texture coordinates
	for (int i = 0; i < mesh->num_texture * 2; ++i)
		mesh->texture_coords[i] = par_mesh->tcoords[i];

	//Checkers texture to primitive
	obj->CreateComponent(Component::Type::TEXTURE);
	ComponentTexture* c_texture = obj->GetComponentTexture();

	c_texture->texture = App->Mtexture->CreateCheckerTexture();

	//Generate the buffers 
	VertexBuffer(mesh->id_vertex, mesh->num_vertex, mesh->vertices);
	IndexBuffer(mesh->id_index, mesh->num_index, mesh->indices);
	//Generate the buffer for texture coords
	TextureBuffer(mesh->id_texture, mesh->num_texture, mesh->texture_coords);
}

void ModuleGeometry::LoadImageFBX(std::string full_path, GameObject* goImage)
{
	const aiScene* scene = aiImportFile(full_path.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes())
	{
		for (int i = 0; i < scene->mNumMeshes; ++i)
		{
			goImage->CreateComponent(Component::Type::MESH);
			ComponentMesh* mesh = goImage->GetComponentMesh();

			aiMesh* new_mesh = scene->mMeshes[i];

			mesh->num_vertex = new_mesh->mNumVertices; //obj->getcomponentmesh->num_vertex
			mesh->vertices = new float3[mesh->num_vertex];
			//memcpy(m->vertex, new_mesh->mVertices, sizeof(float) * m->num_vertex);

			//App->Console_Log("New mesh with %d vertices", mesh->num_vertex);

			for (uint i = 0; i < new_mesh->mNumVertices; ++i)
			{
				mesh->vertices[i].x = new_mesh->mVertices[i].x;
				mesh->vertices[i].y = new_mesh->mVertices[i].y;
				mesh->vertices[i].z = new_mesh->mVertices[i].z;
			}

			if (new_mesh->HasFaces())
			{
				mesh->num_index = new_mesh->mNumFaces * 3;
				mesh->indices = new uint[mesh->num_index]; // assume each face is a triangle

				for (uint i = 0; i < new_mesh->mNumFaces; ++i)
				{
					if (new_mesh->mFaces[i].mNumIndices != 3)
						App->Console_Log("WARNING, geometry face with != 3 indices!");
					else
						memcpy(&mesh->indices[i * 3], new_mesh->mFaces[i].mIndices, 3 * sizeof(uint));
				}
			}

			ComponentTexture* c_texture = goImage->GetComponentTexture();
			c_texture = (ComponentTexture*)goImage->CreateComponent(Component::Type::TEXTURE);

			if (new_mesh->HasTextureCoords(0))
			{
				mesh->num_texture = mesh->num_vertex;
				mesh->texture_coords = new float[mesh->num_texture * 2];

				for (int i = 0; i < mesh->num_texture; ++i)
				{
					mesh->texture_coords[i * 2] = new_mesh->mTextureCoords[0][i].x;
					mesh->texture_coords[(i * 2) + 1] = new_mesh->mTextureCoords[0][i].y;
				}
			}
			//Generate buffer for each mesh and send vertex and indices to VRAM
			VertexBuffer(mesh->id_vertex, mesh->num_vertex, mesh->vertices);
			IndexBuffer(mesh->id_index, mesh->num_index, mesh->indices);
			TextureBuffer(mesh->id_texture, mesh->num_texture, mesh->texture_coords);
		}
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		aiReleaseImport(scene);
		//App->Console_Log("Succesfully loaded mesh with path: %s", full_path);
	}
	else
		App->Console_Log("[ERROR]: Loading image %s", full_path);

}

void ModuleGeometry::VertexBuffer(uint& id, uint& size, float3* vertices)
{
	glGenBuffers(1, (GLuint*) & (id));
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float3) * size, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ModuleGeometry::IndexBuffer(uint& id, uint& size, const uint* indices)
{
	glGenBuffers(1, (GLuint*) & (id));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * size, indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ModuleGeometry::TextureBuffer(uint& id, uint& num_texture, float* texture_pos)
{
	glGenBuffers(1, (GLuint*) & (id));
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * num_texture * 2, texture_pos, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ModuleGeometry::DefineTextureType(const aiScene* file, const aiMesh* new_mesh, GameObject* obj, std::string full_path)
{
	aiMaterial* material = file->mMaterials[new_mesh->mMaterialIndex];
	uint numTextures = material->GetTextureCount(aiTextureType_DIFFUSE);

	aiString path;
	material->GetTexture(aiTextureType_DIFFUSE, 0, &path);

	ComponentTexture* c_texture = (ComponentTexture*)obj->CreateComponent(Component::Type::TEXTURE);

	if (path.C_Str() != nullptr && path.length > 0)
	{
		std::string directory = App->GetDirectoryFromPath(full_path);
		directory.append("/");
		directory.append(path.C_Str());

		c_texture->texture = App->Mtexture->LoadTexturePath(directory.c_str());
	}
}
