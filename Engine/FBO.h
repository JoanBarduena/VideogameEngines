#pragma once

#include "Globals.h"
#include "imGui/imgui.h"
#include "glew/include/GL/glew.h"

class FBO
{
public:

	FBO();
	~FBO();

	bool Start(uint width, uint height);
	bool Draw();
	void Undraw();
	bool CleanUp();

	void RestartBuffers();
	void PrepareDepth();
	void PrepareTexture();

	uint GetTexture() const;
	ImVec2 GetTextureSize() const;

public:

	uint fbo_b = 0;
	uint rbo = 0;
	uint fboTexture = 0;

	ImVec2 size; 
};