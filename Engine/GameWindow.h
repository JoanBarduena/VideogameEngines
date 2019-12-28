#pragma once
#include "Window.h"
#include "FrameBuffer.h"
#include "glew/include/GL/glew.h"

#include "imGui/imgui.h"
#include "imGui/imgui_impl_sdl.h"
#include "imGui/imgui_impl_opengl3.h"

class GameWindow : public Window
{
public: 

	GameWindow(); 
	~GameWindow(); 

	bool Start(); 
	bool Draw(); 
	bool CleanUp();
	bool OnResize();

	ImVec2 size_;
	ImVec2 new_size;

private:

	FrameBuffer* fbo = nullptr; 
	float worldposx = 0; 
	float worldposy = 0; 
};
