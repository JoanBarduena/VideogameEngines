#pragma once
#include "Component.h"
#include "Globals.h"

#include "MathGeoLib/include/MathBuildConfig.h"
#include "MathGeoLib/include/MathGeoLib.h"

class ComponentMesh : public Component
{
public:

	ComponentMesh(GameObject* GObj); 
	~ComponentMesh(); 

	uint id_index = 0; // index in VRAM
	uint num_index = 0;
	uint* index = nullptr;

	uint id_vertex = 0; // unique vertex in VRAM
	uint num_vertex = 0;
	float3* vertex = nullptr;

	uint id_texture = 0;
	uint num_texture = 0;
	float* texture_pos = nullptr;

	uint texture = 0;

};