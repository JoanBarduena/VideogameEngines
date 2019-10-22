#pragma once
#include "Globals.h"

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

	void Create_Sphere();
	void Create_Cube(float x, float y, float z, float size);


public: 

	par_shapes_mesh_s* obj = nullptr;

	uint id_vertex; 
	uint id_index; 
	uint id_texture; 

	Position position; 
};