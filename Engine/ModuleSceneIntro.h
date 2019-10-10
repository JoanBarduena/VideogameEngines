#pragma once
#include "Module.h"
#include "Globals.h"
#include "Timer.h"

struct PhysBody3D;
struct PhysMotor3D;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	update_status PostUpdate(float dt); 
	bool CleanUp();

	void Create_Cube(float x, float y, float z, float size);
	uint num_indices = 36; 

};
