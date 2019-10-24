#pragma once
#include "Module.h"
#include "Globals.h"
#include "Timer.h"
#include "Shapes.h"

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true); 
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	update_status PostUpdate(float dt); 
	bool CleanUp();

	uint num_indices = 36; 

	Shapes* object = nullptr; 
};
