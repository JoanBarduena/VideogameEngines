#include "Globals.h"
#include "ModuleViewport.h"

ModuleViewport::ModuleViewport(bool start_enabled) :Module(start_enabled)
{
}

ModuleViewport::~ModuleViewport()
{
}

bool ModuleViewport::Start()
{
	bool ret = true; 

	//App->scene_intro->CreateCanvas(); 

	return ret;
}

update_status ModuleViewport::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleViewport::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

bool ModuleViewport::CleanUp()
{
	bool ret = true; 

	return ret;
}

