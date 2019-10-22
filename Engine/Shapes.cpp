#include "Shapes.h"
#include "Application.h"
#include "Module.h"

#include "par/parshapes.h"

Shapes::Shapes() {}

Shapes::~Shapes() {}

void Shapes::CreateBuffer()
{
	if (Body != nullptr)
	{
		//vertex
		glGenBuffers(1, (GLuint*) & (id_vertex));
		glBindBuffer(GL_ARRAY_BUFFER, id_vertex);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * Body->npoints * 3, Body->points, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//indices
		glGenBuffers(1, (GLuint*) & (id_index));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_index);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(PAR_SHAPES_T) * Body->ntriangles * 3, Body->triangles, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		//texture
		glGenBuffers(1, (GLuint*) & (id_texture));
		glBindBuffer(GL_ARRAY_BUFFER, id_texture);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * Body->npoints * 6, Body->tcoords, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

void Shapes::RenderObject()
{
	glEnableClientState(GL_VERTEX_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, id_vertex);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_index);
	glDrawElements(GL_TRIANGLES, Body->ntriangles * 3, GL_UNSIGNED_SHORT, nullptr);

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Texture);
	glBindBuffer(GL_ARRAY_BUFFER, id_texture);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisableClientState(GL_VERTEX_ARRAY);
}

void Shapes::Create_Sphere(int slices, int stacks, float x, float y, float z, float size)
{
	Body = par_shapes_create_parametric_sphere(slices, stacks);

	position.x = x;
	position.y = y;
	position.z = z;

	par_shapes_scale(Body, size, size, size);
	par_shapes_translate(Body, position.x, position.y, position.z);

	vector_shapes.push_back(Body);

	CreateBuffer(); 
}

void Shapes::Create_Cube(float x, float y, float z, float size)
{
	Body = par_shapes_create_cube();

	position.x = x; 
	position.y = y; 
	position.z = z; 

	par_shapes_scale(Body, size, size, size); 
	par_shapes_translate(Body, position.x, position.y, position.z); 

	vector_shapes.push_back(Body);

	CreateBuffer(); 
}


