#pragma once
#include "Module.h"
#include "Globals.h"
#include "glew/include/GL/glew.h"
#include <vector>

struct tex_data
{

};


class ModuleTexture : public Module
{
public:
	ModuleTexture(Application* app, bool start_enabled = true);
	~ModuleTexture();

	bool Init();
	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void CreateCheckerTexture();

private:

	uint image_name;
	GLubyte check_image[100][100][4];
};

