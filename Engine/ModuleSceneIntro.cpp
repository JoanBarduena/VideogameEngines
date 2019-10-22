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
	/*glBegin(GL_TRIANGLES);  

	glVertex3f(0.f, 0.f, 0.f);  
	glVertex3f(10.f, 0.f, 0.f);
	glVertex3f(0.f, 10.f, 0.f); 

	glEnd();
	glLineWidth(2.0f);*/

	Create_Cube(0, 0, 0, 2); 

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::Create_Cube(float x, float y, float z, float size)
{
	float vertices[] = {  
	//front
	x + 0.0,	y + 0.0,	z + size,
	x + size,	y + 0.0,	z + size,
	x + size,   y + size,	z + size,
	x + 0.0,	y + size,	z + size,
	// back
	x + 0.0,	y + 0.0,	z + 0.0,
	x + size,	y + 0.0,    z + 0.0,
	x + size,	y + size,   z + 0.0,
	x + 0.0,	y + size,	z + 0.0
	};

	uint indices[] = {	
	//front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	uint my_id = 0;
	glGenBuffers(1, (GLuint*) &(my_id));
	glBindBuffer(GL_ARRAY_BUFFER, my_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	uint my_indices = 0;
	glGenBuffers(1, (GLuint*) &(my_indices));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, NULL);
	glDisableClientState(GL_VERTEX_ARRAY);

	//glEnable(GL_DEPTH_TEST);
}