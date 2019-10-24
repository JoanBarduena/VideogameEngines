#pragma once
#include "Module.h"
#include "Globals.h"
#include "glew/include/GL/glew.h"
#include <vector>

class ModuleTexture : public Module
{
public:
	ModuleTexture(Application* App, bool start_enabled = true);
	~ModuleTexture();

	bool Init();
	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	uint CreateCheckerTexture() const;
	uint LoadTexturePath(std::string image_path);
	uint LoadTextureFromPixels(const void * img, uint TextureWidth, uint TextureHeight, int internalFormat, uint format);

	uint checkersTextureID = 0;

	GLuint image_name = 0;
};

