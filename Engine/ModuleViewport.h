#pragma once
#include "Globals.h"
#include "Module.h"
#include "Application.h"

class FrameBuffer; 

class ModuleViewport : public Module
{
public: 
	ModuleViewport(bool start_enabled = true);
	~ModuleViewport();

	bool Start(); 
	update_status PreUpdate(float dt); 
	update_status PostUpdate(float dt); 
	bool CleanUp(); 

};