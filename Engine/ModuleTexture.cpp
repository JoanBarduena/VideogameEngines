#include "ModuleTexture.h"
#include "Application.h"
#include "ModuleGeometry.h"

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cfileio.h"
#pragma comment (lib, "Assimp/libx86/assimp.lib")

#include "glew/include/GL/glew.h"
#include "SDL/include/SDL_opengl.h"

#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */
#pragma comment(lib, "glew/libx86/glew32.lib")

ModuleTexture::ModuleTexture(Application* app, bool start_enabled) : Module(app, start_enabled)
{}


ModuleTexture::~ModuleTexture()
{}

bool ModuleTexture::Init() 
{
	bool ret = true;

	return ret;
}


bool ModuleTexture::Start()
{
	bool ret = true;

	CreateCheckerTexture();

	return ret;
}

update_status ModuleTexture::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleTexture::Update(float dt)
{
		

	return UPDATE_CONTINUE;
}

update_status ModuleTexture::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

bool ModuleTexture::CleanUp()
{
	bool ret = true;

	return ret;
}

void ModuleTexture::CreateCheckerTexture()
{
	GLubyte checkImage[CHECKERS_HEIGHT][CHECKERS_WIDTH][4];
	for (int i = 0; i < CHECKERS_HEIGHT; i++) {
		for (int j = 0; j < CHECKERS_WIDTH; j++) {
			int c = ((((i & 0x8) == 0) ^ (((j & 0x8)) == 0))) * 255;
			checkImage[i][j][0] = (GLubyte)c;
			checkImage[i][j][1] = (GLubyte)c;
			checkImage[i][j][2] = (GLubyte)c;
			checkImage[i][j][3] = (GLubyte)255;
		}
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &image_name);
	glBindTexture(GL_TEXTURE_2D, image_name);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, CHECKERS_WIDTH, CHECKERS_HEIGHT,
		0, GL_RGBA, GL_UNSIGNED_BYTE, check_image);
	
}
