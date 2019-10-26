#pragma once
#include "Module.h"
#include "Globals.h"
#include "glew/include/GL/glew.h"
#include <vector>

struct TextureStruct
{
	uint textureID = 0;
	string path;
	uint height;
	uint width;
};

class ModuleTexture : public Module
{
public:
	ModuleTexture(bool start_enabled = true);
	~ModuleTexture();

	bool Init();
	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	TextureStruct* CreateCheckerTexture() const;
	TextureStruct* LoadTexturePath(const char* image_path);
	uint LoadTextureFromPixels(const void * img, uint TextureWidth, uint TextureHeight, int internalFormat, uint format) const;

	GLuint image_name = 0;
};
