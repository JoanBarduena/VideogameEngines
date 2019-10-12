#pragma once
#include "Module.h"
#include "Globals.h"

class ModuleTexture : public Module
{
public:
	ModuleTexture(Application* app, bool start_enabled = true);
	~ModuleTexture();

	bool Init();
	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

};

