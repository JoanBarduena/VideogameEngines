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
	void SetGLEnum(bool is_enabled, GLenum cap); 

	void DemoWindow();
	void RNGWindow();
	void ConfigWindow();
	void AboutWindow();

	void CreateMainWorkingSpace();

	ImGuiIO* io = nullptr;
	bool p_open = true;

	pcg_state_setseq_32 bounded;
	int interval = 0, min = 0, max = 0;

	int cpu_count = 0, system_ram = 0, cpu_cache = 0;
	SDL_bool RDTSC, MMX, SSE, SSE2, SSE3; 

	bool gl_depth_test = true;
	bool gl_cull_face = true;
	bool gl_lighting = true;
	bool gl_color_material = true;
	bool gl_texture_2D = true; 
	
	Console gui_console;
	bool console_log = true; 
	int vector_size = 0; 

private:

	bool show_main_window = false;
	bool show_demo_window = false; 
	bool show_random_num_window = false;
	bool show_config_window = false; 
	bool show_about_modal = false;
	bool show_app_console = false; 

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
};


#endif