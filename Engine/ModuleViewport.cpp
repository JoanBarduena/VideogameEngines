#include "Globals.h"
#include "Application.h"
#include "ModuleViewport.h"

ModuleViewport::ModuleViewport(bool start_enabled) :Module(start_enabled)
{
}

ModuleViewport::~ModuleViewport()
{
	root->DeleteGO(root, true);
}

bool ModuleViewport::Start()
{
	bool ret = true; 

	root = App->scene_intro->CreateGameObject();
	root->name = "ROOT";

	fbo_scene = new FBO(); 
	fbo_scene->Start((uint)App->window->GetWinSize().x, App->window->GetWinSize().y);

	return ret;
}

update_status ModuleViewport::PreUpdate(float dt)
{
	fbo_scene->Draw();

	return UPDATE_CONTINUE;
}

update_status ModuleViewport::PostUpdate(float dt)
{

	fbo_scene->Undraw(); 
	//LOG("%d", App->gui->game_w->Wsize.x); 

	return UPDATE_CONTINUE;
}

bool ModuleViewport::CleanUp()
{
	bool ret = true;

	RELEASE(fbo_scene); 
	RELEASE(fbo_game); 

	return ret;
}

