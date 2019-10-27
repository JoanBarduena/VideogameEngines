#pragma once
#include "Module.h"
#include "Window.h"

#include "glew/include/GL/glew.h"
#include "SDL/include/SDL.h"

class ConfigurationWindow : public Window
{
public: 

	ConfigurationWindow(); 
	~ConfigurationWindow(); 

	bool Start();
	bool Draw(); 
	bool CleanUp(); 

	void SetGLEnum(bool is_enabled, GLenum cap); 

	bool gl_depth_test = true;
	bool gl_cull_face = true;
	bool gl_lighting = true;
	bool gl_color_material = true;
	bool gl_texture_2D = false;

	int cpu_count = 0, system_ram = 0, cpu_cache = 0;
	SDL_bool RDTSC, MMX, SSE, SSE2, SSE3;
};
