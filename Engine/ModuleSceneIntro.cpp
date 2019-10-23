#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "SDL/include/SDL_opengl.h"
#include "Shapes.h"

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

	App->geometry->LoadGeometry("Assets/BakerHouse.fbx"); 

	object = new Shapes();
	object->Create_Cube(0,0,0,2);
	object->Create_Sphere(10,10,0,0,0,2); 

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
	glLineWidth(2.0f);

	glBegin(GL_LINES);
	glColor3ub(255, 255, 255);
	for (float i = -10; i <= 10; ++i)
	{
		glVertex3f(i, 0.f, 0.f);
		glVertex3f(i, 0, 10.f);

		glVertex3f(0.f, 0.f, i);
		glVertex3f(10.f, 0, i);

		glVertex3f(i, 0.f, 0.f);
		glVertex3f(i, 0, -10.f);

		glVertex3f(0.f, 0.f, i);
		glVertex3f(-10.f, 0, i);
	}
	glEnd();
	return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::PostUpdate(float dt)
{
	for (int i = 0; i < App->geometry->meshes.size(); ++i)
		App->renderer3D->DrawMesh(App->geometry->meshes[i]);

	for (int i = 0; i < object->vector_shapes.size(); i++)
	{
		object->RenderObject();
	}
	return UPDATE_CONTINUE;
}

