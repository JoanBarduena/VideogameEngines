#pragma once
#include "Globals.h"
#include "Module.h"
#include "FBO.h"
#include "GameObject.h"
#include "SceneWindow.h"
#include "GameObject.h"

class ModuleViewport : public Module
{
public: 
	ModuleViewport(bool start_enabled = true);
	~ModuleViewport();

	bool Start(); 
	update_status PreUpdate(float dt); 
	update_status Update(float dt); 
	update_status PostUpdate(float dt); 
	bool CleanUp();

	void DrawRecursively(GameObject* GO);
	void SetGameObjectStatic(GameObject* go);

	GameObject* CreateGameObject();
	GameObject* CreateCanvas();
	GameObject* CreateImage(GameObject* parent);


public: 
	FBO* fbo_scene = nullptr; 
	FBO* fbo_game = nullptr; 

	GameObject* root = nullptr;
	GameObject* canvas = nullptr; 
	GameObject* image = nullptr; 

	std::vector<GameObject*> game_objects;
	uint num_canvas = 1, num_image = 1;

	std::vector<ComponentMesh*> static_meshes;

	SceneWindow* g_window = nullptr; 

	bool render_grid = false;
};