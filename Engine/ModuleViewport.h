#pragma once
#include "Globals.h"
#include "Module.h"

class FBO; 
class SceneWindow; 

class ModuleViewport : public Module
{
public: 
	ModuleViewport(bool start_enabled = true);
	~ModuleViewport();

	bool Start(); 
	update_status PreUpdate(float dt); 
	update_status PostUpdate(float dt); 
	bool CleanUp(); 

public: 
	FBO* fbo_scene = nullptr; 
	FBO* fbo_game = nullptr; 

	GameObject* root = nullptr;

	SceneWindow* g_window = nullptr; 
};