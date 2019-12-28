#pragma once

#include "imGui/imgui.h"
#include "glew/include/GL/glew.h"

class FrameBuffer
{
public:

	FrameBuffer();
	~FrameBuffer();

	bool Start(ImVec2 size);
	bool Draw();
	bool CleanUp();

	void RestartBuffers();
	void PrepareDepth();
	void PrepareTexture();

	GLuint GetTexture() const;
	ImVec2 GetTextureSize() const;

public:

	GLuint fbo = 0;
	GLuint rbo = 0;
	GLuint fboTexture = 0;

	ImVec2 Fsize; 
};