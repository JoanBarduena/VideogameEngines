#ifndef __MODULEGUI_H__
#define __MODULEGUI_H__

#include "Module.h"
#include "Console.h"

#include "SDL/include/SDL.h"

#include "imGui/imgui.h"
#include "imGui/imgui_impl_sdl.h"
#include "imGui/imgui_impl_opengl3.h"

#include "PCG/entropy.h"
#include "PCG/pcg_variants.h"

#include "glew/include/GL/glew.h"

#include "Window.h"
#include "ConfigurationWindow.h"
#include "ConsoleWindow.h"
#include "HierarchyWindow.h"
#include "InspectorWindow.h"

class ModuleGui : public Module
{
public:
	ModuleGui(bool start_enabled = true);
	~ModuleGui(); 

	bool Init(); 
	bool Start(); 
	bool Draw(); 
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt); 
	bool CleanUp(); 

	void CreateMainWorkingSpace();

	ImGuiIO* io = nullptr;
	bool p_open = true;

	pcg_state_setseq_32 bounded;
	int interval = 0, min = 0, max = 0;

	update_status exit_application = UPDATE_CONTINUE; 

public:

	//Windows 
	ConfigurationWindow* config_w = nullptr; 
	ConsoleWindow* console_w = nullptr; 
	InspectorWindow* inspector_w = nullptr;
	HierarchyWindow* hierarchy_w = nullptr; 

	std::list<Window*> windows;

public:

	bool show_main_window = false;
	bool show_demo_window = false; 
	bool show_random_num_window = false;
	bool show_config_window = true; 
	bool show_about_modal = false;
	bool show_app_console = true;
	bool show_hierarchy_window = true; 
	bool show_inspector_window = true; 

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
};


#endif