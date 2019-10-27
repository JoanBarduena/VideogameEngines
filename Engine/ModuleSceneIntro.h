#pragma once
#include "Module.h"
#include "Globals.h"
#include "Timer.h"
#include "GameObject.h"
#include "par/parshapes.h"

struct Position {
	float x, y, z;
};

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(bool start_enabled = true); 
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	update_status PostUpdate(float dt);

	GameObject* CreateGameObject(); 

	void Create_Sphere(int slices, int stacks, float x, float y, float z, float size);
	void Create_Cube(float x, float y, float z, float size);

	bool CleanUp();

	uint num_indices = 36; 

	uint id_vertex;
	uint id_index;
	uint id_texture;

	TextureStruct* HouseTexture; 

	par_shapes_mesh_s* Body = nullptr;
	std::vector<par_shapes_mesh_s*> vector_shapes;

	Position position; 

	std::vector<GameObject*> game_objects;
};
