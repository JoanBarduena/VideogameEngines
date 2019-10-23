#include "Globals.h"
#include "ModuleGeometry.h"
#include "Application.h"

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

ModuleGeometry::ModuleGeometry(Application* app, bool start_enabled) : Module(app, start_enabled)
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
	for (int i = 0; i < meshes.size(); ++i)
	{
		App->renderer3D->DrawMesh(meshes[i]); 
	}

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

	meshes.clear(); 

	return ret;
}

void ModuleGeometry::LoadGeometry(const char* full_path)
{
	const aiScene* scene = aiImportFile(full_path, aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes())
	{

		for (int i = 0; i < scene->mNumMeshes; ++i)
		{
			mesh_data* m = new mesh_data;

			aiMesh *new_mesh = scene->mMeshes[i];

			m->num_vertex = new_mesh->mNumVertices;
			m->vertex = new float3[m->num_vertex];
			//memcpy(m->vertex, new_mesh->mVertices, sizeof(float) * m->num_vertex);

			App->Console_Log("New mesh with %d vertices", m->num_vertex);

			for (uint i = 0; i < new_mesh->mNumVertices; ++i)
			{
				m->vertex[i].x = new_mesh->mVertices[i].x;
				m->vertex[i].y = new_mesh->mVertices[i].y;
				m->vertex[i].z = new_mesh->mVertices[i].z;
			}

			if (new_mesh->HasFaces())
			{
				m->num_index = new_mesh->mNumFaces * 3;
				m->index = new uint[m->num_index]; // assume each face is a triangle

				for (uint i = 0; i < new_mesh->mNumFaces; ++i)
				{
					if (new_mesh->mFaces[i].mNumIndices != 3)
						App->Console_Log("WARNING, geometry face with != 3 indices!");
					else
						memcpy(&m->index[i * 3], new_mesh->mFaces[i].mIndices, 3 * sizeof(uint));
				}
			}
			if (new_mesh->HasTextureCoords(0))
			{
				m->num_texture = m->num_vertex;
				m->texture_pos = new float[m->num_texture * 2];

				for (int i = 0; i < m->num_texture; ++i)
				{
					m->texture_pos[i * 2] = new_mesh->mTextureCoords[0][i].x;
					m->texture_pos[(i * 2) + 1] = new_mesh->mTextureCoords[0][i].y;
				}
			}
			//Generate buffer for each mesh and send vertex and indices to VRAM
			VertexBuffer(m->id_vertex, m->num_vertex, m->vertex); 
			IndexBuffer(m->id_index, m->num_index, m->index); 
			TextureBuffer(m->id_texture, m->num_texture, m->texture_pos); 
			//Allocate new_mesh inside an array of mesh_data
			meshes.push_back(m); 
		}	
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		aiReleaseImport(scene);
		App->Console_Log("Succesfully loaded mesh with path: %s", full_path);
	}
	else
		App->Console_Log("Error loading scene %s", full_path);
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