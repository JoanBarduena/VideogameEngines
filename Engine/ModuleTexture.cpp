#include "ModuleTexture.h"
#include "Application.h"


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