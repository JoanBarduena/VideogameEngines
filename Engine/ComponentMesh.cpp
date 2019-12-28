#include "ComponentMesh.h"
#include "Application.h"

#include "mmgr/mmgr.h"
#include "Color.h"

ComponentMesh::ComponentMesh(GameObject * GObj):Component(GObj, Type::MESH)
{
}

ComponentMesh::~ComponentMesh()
{
}

ComponentMesh* ComponentMesh::CreateMesh(float3* vertex)
{
	return this;
}

bool ComponentMesh::CleanUp()
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
	return true; 
}

void ComponentMesh::DrawAABB()
{
	float3 minPoint = float3(aabb.minPoint);
	float3 maxPoint = float3(aabb.maxPoint);

	int num_v = aabb.NumVerticesInEdgeList();
	math::float3* vertices = new math::float3[num_v];
	aabb.ToEdgeList((float3*)vertices);

	glBegin(GL_LINES);
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);

	for (uint i = 0; i < aabb.NumVerticesInEdgeList(); i++)
	{
		glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
	}

	delete[] vertices; 

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glEnd();

}

void ComponentMesh::UpdateAABB()
{
	aabb.SetNegativeInfinity();
	aabb.Enclose(vertices, num_vertex);
}


const AABB& ComponentMesh::GetAABB() const
{
	return aabb;
}
