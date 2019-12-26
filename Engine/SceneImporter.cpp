#include "Globals.h"
#include "Application.h"
#include "SceneImporter.h"
#include "ModuleFileSystem.h"

// DevIL library ----------------------------
#include "DevIL/IL/il.h"
#include "DevIL/IL/ilu.h"
#include "DevIL/IL/ilut.h"

#pragma comment (lib, "DevIL/libx86/DevIL.lib")
#pragma comment (lib, "DevIL/libx86/ILU.lib")
#pragma comment (lib, "DevIL/libx86/ILUT.lib")

#include "mmgr/mmgr.h"

//#include "glew/include/GL/glew.h"

SceneImporter::SceneImporter(){}

SceneImporter::~SceneImporter() 
{

}

bool SceneImporter::Init()
{
	bool ret = true; 
	// Checking current version
	if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION || iluGetInteger(ILU_VERSION_NUM) < ILU_VERSION || ilutGetInteger(ILUT_VERSION_NUM) < ILUT_VERSION)
	{
		App->Console_Log("DevIL version is different...exiting!\n");
		ret = false;
	}
	else
	{
		App->Console_Log("Initializing DevIL");

		ilInit();
		iluInit();
		ilutInit();

		// Initialize DevIL's OpenGL access
		ilutRenderer(ILUT_OPENGL);
	}

	return ret; 
}

bool SceneImporter::ImportMesh(const char* path, ComponentMesh* mesh)
{
	bool ret = true;

	char* buffer = nullptr; 
	App->filesystem->Load(path, &buffer);

	char* cursor = buffer;

	// amount of indices / vertices / colors / normals / texture_coords
	uint ranges[3]; // 3 ranges at the moment
	uint bytes = sizeof(ranges);
	memcpy(ranges, cursor, bytes);

	mesh->num_index = ranges[0]; // indices
	mesh->num_vertex = ranges[1]; // vertices 
	mesh->num_texture = ranges[2]; // texture_coords

	// Load indices
	cursor += bytes;
	bytes = sizeof(uint) * mesh->num_index;
	mesh->indices = new uint[mesh->num_index];
	memcpy(mesh->indices, cursor, bytes);

	// Load vertices 
	cursor += bytes; 
	bytes = sizeof(float) * mesh->num_vertex * 3; 
	mesh->vertices = new float3[mesh->num_vertex]; 
	memcpy(mesh->vertices, cursor, bytes); 

	// Load texture_coords 
	cursor += bytes; 
	bytes = sizeof(float) * mesh->num_texture * 2; 
	mesh->texture_coords = new float[mesh->num_texture]; 
	memcpy(mesh->texture_coords, cursor, bytes); 

	return ret;
}



bool SceneImporter::ExportMesh(const char* name, const char* path, std::string& output_file, ComponentMesh* mesh)
{
	bool ret = true; 

	// amount of indices / vertices / colors / normals / texture_coords / AABB
	uint ranges[3] = { mesh->num_index, mesh->num_vertex, mesh->num_texture };

	// size of allocation for ranges, indices, vertices and texture_coords
	uint size = sizeof(ranges) + sizeof(uint) * mesh->num_index + sizeof(float) * mesh->num_vertex * 3 + sizeof(float) * mesh->num_texture * 2;

	// Allocate
	char* data = new char[size];
	char* cursor = data;

	// First store ranges
	uint bytes = sizeof(ranges);
	memcpy(cursor, ranges, bytes);

	// Store indices
	cursor += bytes;
	bytes = sizeof(uint) * mesh->num_index;
	memcpy(cursor, mesh->indices, bytes);

	// Store vertices 
	cursor += bytes; 
	bytes = sizeof(float) * mesh->num_vertex * 3;
	memcpy(cursor, mesh->vertices, bytes);

	// Store texture_coords
	cursor += bytes; 
	bytes = sizeof(float) * mesh->num_texture * 2; 
	memcpy(cursor, mesh->texture_coords, bytes); 

	// Save a new extension .mesh 
	App->filesystem->SaveUnique(output_file, data, size, path, name, "mesh"); 

	RELEASE_ARRAY(data);
	return ret;
}