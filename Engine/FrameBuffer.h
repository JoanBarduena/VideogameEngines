#pragma once

#include "imGui/imgui.h"
#include "imGui/imgui_impl_sdl.h"
#include "imGui/imgui_impl_opengl3.h"

class FrameBuffer
{
public:

	FrameBuffer();
	~FrameBuffer();

	bool Start(ImVec2 size);
	bool Draw();
	bool CleanUp();
	void RestartBuffers();

	unsigned int fbo;
	unsigned int rbo;
	unsigned int texture;
};