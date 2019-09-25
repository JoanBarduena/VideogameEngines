#ifndef __MODULEGUI_H__
#define __MODULEGUI_H__

#include "Module.h"

#include "imGui/imgui.h"
#include "imGui/imgui_impl_sdl.h"
#include "imGui/imgui_impl_opengl3.h"

class ModuleGui : public Module
{
public:
	ModuleGui(Application* app, bool start_enabled = true);
	~ModuleGui(); 

	bool Init(); 
	bool Start(); 
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt); 
	bool CleanUp(); 

private:

	bool show_demo_window = true; 
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
};

#endif