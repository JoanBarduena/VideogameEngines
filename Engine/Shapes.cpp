#include "Globals.h"
#include "Application.h"
#include "Shapes.h"

#include "par/parshapes.h"

Shapes::Shapes() {}

Shapes::~Shapes() {}

void Shapes::CreateBuffer()
{
	if (obj != nullptr)
	{
		//vertex
		glGenBuffers(1, (GLuint*) & (id_vertex));
		glBindBuffer(GL_ARRAY_BUFFER, id_vertex);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * obj->npoints * 3, obj->points, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//indices
		glGenBuffers(1, (GLuint*) & (id_index));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_index);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(PAR_SHAPES_T) * obj->ntriangles * 3, obj->triangles, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		//texture
		glGenBuffers(1, (GLuint*) & (id_texture)); // 
		glBindBuffer(GL_ARRAY_BUFFER, id_texture);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * obj->npoints * 6, obj->tcoords, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

void Shapes::RenderObject()
{
	glEnableClientState(GL_VERTEX_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, id_vertex);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_index);
	glDrawElements(GL_TRIANGLES, obj->ntriangles * 3, GL_UNSIGNED_SHORT, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableClientState(GL_VERTEX_ARRAY);
}

void Shapes::Create_Sphere()
{
	par_shapes_mesh* par_shapes_create_parametric_sphere(int slices, int stacks);

	CreateBuffer(); 
}

void Shapes::Create_Cube(float x, float y, float z, float size)
{
	obj = par_shapes_create_cube();

	position.x = x; 
	position.y = y; 
	position.z = z; 

	par_shapes_scale(obj, size, size, size); 
	par_shapes_translate(obj, position.x, position.y, position.z); 

	CreateBuffer(); 
}


