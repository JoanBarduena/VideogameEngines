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

void ModuleGeometry::LoadGeometry(const char* full_path)
{
	const aiScene* file = aiImportFile(full_path, aiProcessPreset_TargetRealtime_MaxQuality);
	const aiNode* node = file->mRootNode; 

	aiVector3D position; 
	aiVector3D scaling;
	aiQuaternion rotation; 

	node->mTransformation.Decompose(scaling, rotation, position); 

	float3 pos(position.x, position.y, position.z); 
	float3 scale(scaling.x, scaling.y, scaling.z); 
	Quat rot(rotation.x, rotation.y, rotation.z, rotation.w); 

	string name = node->mName.C_Str(); 

	if (file != nullptr && file->HasMeshes())
	{
		for (int i = 0; i < file->mNumMeshes; ++i)
		{
			GameObject* obj = App->scene_intro->CreateGameObject(); //GameObject* obj = creategameobject(); 

			aiMesh *new_mesh = file->mMeshes[i];

			obj->mesh->num_vertex = new_mesh->mNumVertices; //obj->getcomponentmesh->num_vertex
			obj->mesh->vertices = new float3[obj->mesh->num_vertex];
			memcpy(obj->mesh->vertices, new_mesh->mVertices, sizeof(float3) * obj->mesh->num_vertex);

			App->Console_Log("New mesh with %d vertices", obj->mesh->num_vertex);

			for (uint i = 0; i < new_mesh->mNumVertices; ++i)
			{
				obj->mesh->vertices[i].x = new_mesh->mVertices[i].x;
				obj->mesh->vertices[i].y = new_mesh->mVertices[i].y;
				obj->mesh->vertices[i].z = new_mesh->mVertices[i].z;
			}

			if (new_mesh->HasFaces())
			{
				obj->mesh->num_index = new_mesh->mNumFaces * 3;
				obj->mesh->indices = new uint[obj->mesh->num_index]; // assume each face is a triangle

				for (uint i = 0; i < new_mesh->mNumFaces; ++i)
				{
					if (new_mesh->mFaces[i].mNumIndices != 3)
						App->Console_Log("[WARNING]: Geometry face with != 3 indices!");
					else
						memcpy(&obj->mesh->indices[i * 3], new_mesh->mFaces[i].mIndices, 3 * sizeof(uint));
				}
			}
			if (new_mesh->HasTextureCoords(0))
			{
				obj->mesh->num_texture = obj->mesh->num_vertex;
				obj->mesh->texture_coords = new float[obj->mesh->num_texture * 2];

				for (int i = 0; i < obj->mesh->num_texture; ++i)
				{
					obj->mesh->texture_coords[i * 2] = new_mesh->mTextureCoords[0][i].x;
					obj->mesh->texture_coords[(i * 2) + 1] = new_mesh->mTextureCoords[0][i].y;
				}
			}
			//Generate buffer for each mesh and send vertex and indices to VRAM
			VertexBuffer(obj->mesh->id_vertex, obj->mesh->num_vertex, obj->mesh->vertices);
			IndexBuffer(obj->mesh->id_index, obj->mesh->num_index, obj->mesh->indices);
			TextureBuffer(obj->mesh->id_texture, obj->mesh->num_texture, obj->mesh->texture_coords);	
		}	
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		aiReleaseImport(file);
		App->Console_Log("Succesfully loaded mesh with path: %s", full_path);
	}
	else
		App->Console_Log("[WARNING]: Error loading mesh with path %s", full_path);
}

void ModuleGeometry::LoadParShapes(par_shapes_mesh* par_mesh, Position pos)
{
	GameObject* obj = App->scene_intro->CreateGameObject();

	// VERTEX ----------------
	obj->mesh->num_vertex = par_mesh->npoints;
	obj->mesh->vertices = new float3[obj->mesh->num_vertex];

	for (int i = 0; i < obj->mesh->num_vertex; i++)
	{
		int j = i * 3;
		obj->mesh->vertices[i].x = par_mesh->points[j];
		obj->mesh->vertices[i].y = par_mesh->points[j + 1];
		obj->mesh->vertices[i].z = par_mesh->points[j + 2];
	}

	// INDEX ------------
	obj->mesh->num_index = par_mesh->ntriangles * 3;
	obj->mesh->indices = new uint[obj->mesh->num_index];

	for (int i = 0; i < obj->mesh->num_index; i++)
	{
		obj->mesh->indices[i] = (uint)par_mesh->triangles[i];
	}

	// TEXTURE ----------------
	obj->mesh->num_texture = par_mesh->npoints;
	obj->mesh->texture_coords = new float[obj->mesh->num_texture * 2];

	//Copy the par_shapes texture coordinates
	for (int i = 0; i < obj->mesh->num_texture * 2; ++i)
		obj->mesh->texture_coords[i] = par_mesh->tcoords[i];

	//Checkers texture to primitive
	obj->texture->texture = App->texture->CreateCheckerTexture();

	//obj->transform->position.x = pos.x;
	//obj->transform->position.y = pos.y;
	//obj->transform->position.z = pos.z; 

	//Generate the buffers 
	VertexBuffer(obj->mesh->id_vertex, obj->mesh->num_vertex, obj->mesh->vertices);
	IndexBuffer( obj->mesh->id_index, obj->mesh->num_index, obj->mesh->indices);
	//Generate the buffer for texture coords
	TextureBuffer(obj->mesh->id_texture, obj->mesh->num_texture, obj->mesh->texture_coords);
}

void ModuleGeometry::VertexBuffer(uint &id, uint &size, float3* vertices)
{
	glGenBuffers(1, (GLuint*) &(id));
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float3)*size, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ModuleGeometry::IndexBuffer(uint &id, uint &size, const uint* indices)
{
	glGenBuffers(1, (GLuint*) &(id));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint)*size, indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ModuleGeometry::TextureBuffer(uint &id, uint &num_texture, float* texture_pos)
{
	glGenBuffers(1, (GLuint*) &(id));
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * num_texture * 2, texture_pos, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}