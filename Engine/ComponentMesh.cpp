#include "ComponentMesh.h"

#include "mmgr/mmgr.h"

ComponentMesh::ComponentMesh(GameObject * GObj):Component(GObj, Type::Mesh)
{
}

ComponentMesh::~ComponentMesh()
{
}

void ComponentMesh::CleanUp()
{
	glDeleteBuffers(1, (GLuint*)&id_vertex); 
	glDeleteBuffers(1, (GLuint*)&id_index);
	glDeleteBuffers(1, (GLuint*)&id_texture);

	if (indices != nullptr)
	{
		delete[] indices;
		indices = nullptr; 
	}

	if (vertices != nullptr)
	{
		delete[] vertices;
		vertices = nullptr;
	}

	if (texture_coords != nullptr)
	{
		delete[] texture_coords;
		texture_coords = nullptr;
	}
}
