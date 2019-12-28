#pragma once
#include "Window.h"
#include "FBO.h"
#include "glew/include/GL/glew.h"

#include "imGui/imgui.h"
#include "imGui/imgui_impl_sdl.h"
#include "imGui/imgui_impl_opengl3.h"

class SceneWindow : public Window
{
public: 

	SceneWindow(); 
	~SceneWindow(); 

	bool Start(); 
	bool Draw(); 
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt); 
	bool CleanUp();
	bool OnResize();

	ImVec2 w_Size;
	ImVec2 w_NewSize;

private:
	FBO* fbo = nullptr; 
	float worldposx = 0; 
	float worldposy = 0; 
	float width, height; 
	float pos_y, pos_x; 
};
