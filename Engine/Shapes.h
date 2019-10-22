#ifndef __SHAPES_H__
#define __SHAPES_H__

#include "Globals.h"
#include <vector>

struct par_shapes_mesh_s;

struct Position {
	float x, y, z; 
};

class Shapes
{
public:

	Shapes();
	~Shapes(); 

	void CreateBuffer();
	void RenderObject();

	void Create_Sphere(int slices, int stacks, float x, float y, float z, float size);
	void Create_Cube(float x, float y, float z, float size);


public: 

	par_shapes_mesh_s* Body = nullptr;

	std::vector<par_shapes_mesh_s*> vector_shapes; 

	uint id_vertex; 
	uint id_index; 
	uint id_texture; 

	uint Texture = 0; 

	Position position; 
};

#endif 