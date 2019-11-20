#pragma once
#include "Component.h"
#include "Globals.h"

#include "MathGeoLib/include/MathBuildConfig.h"
#include "MathGeoLib/include/MathGeoLib.h"

#include "glew/include/GL/glew.h"

class ComponentMesh : public Component
{
public:

	ComponentMesh(GameObject* GObj); 
	~ComponentMesh();

	void CleanUp();


	uint id_index = 0; // index in VRAM
	uint num_index = 0;
	uint* indices = nullptr;

	uint id_vertex = 0; // unique vertex in VRAM
	uint num_vertex = 0;
	float3* vertices = nullptr;

	uint id_texture = 0;
	uint num_texture = 0;
	float* texture_coords = nullptr;
};