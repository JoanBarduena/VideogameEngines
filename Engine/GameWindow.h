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

	ImVec2 size_;
	ImVec2 new_size;

private:

	FrameBuffer* fbo = nullptr;   
};
