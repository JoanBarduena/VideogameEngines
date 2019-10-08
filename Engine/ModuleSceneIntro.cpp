#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "SDL/include/SDL_opengl.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	App->Console_Log("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(0.0f, 5.0f, 15.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	App->Console_Log("Unloading Intro scene");
	
	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::PostUpdate(float dt)
{
	glLineWidth(2.0f);
	glBegin(GL_TRIANGLES);  

	glVertex3f(0.f, 0.f, 0.f);  
	glVertex3f(10.f, 0.f, 0.f);
	glVertex3f(0.f, 10.f, 0.f); 

	glEnd();
	glLineWidth(2.0f);

	return UPDATE_CONTINUE;
}