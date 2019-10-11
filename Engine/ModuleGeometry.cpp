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
	mesh_data* m = new mesh_data; 

	const aiScene* scene = aiImportFile(full_path, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene != nullptr && scene->HasMeshes())
	{
		for (int i = 0; i < scene->mNumMeshes; ++i)
		{
			aiMesh *new_mesh = scene->mMeshes[i];
			m->num_vertex = new_mesh->mNumVertices;
			m->vertex = new float[m->num_vertex * 3];
			memcpy(m->vertex, new_mesh->mVertices, sizeof(float) * m->num_vertex * 3);
			App->Console_Log("New mesh with %d vertices", m->num_vertex);

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
			//Generate buffer for each mesh and send vertex and indices to VRAM
			VertexBuffer(m->id_vertex, m->num_vertex, m->vertex); 
			IndexBuffer(m->id_index, m->num_index, m->index); 
		}	
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		aiReleaseImport(scene);
	}
	else
		App->Console_Log("Error loading scene %s", full_path);
}

void ModuleGeometry::VertexBuffer(uint id, uint size, const float* vertices)
{
	glGenBuffers(1, (GLuint*) &(id));
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uint)*size, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ModuleGeometry::IndexBuffer(uint id, uint size, const uint* indices)
{
	glGenBuffers(1, (GLuint*) &(id));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint)*size, indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}