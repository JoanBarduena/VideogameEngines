#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"

#include "ComponentUI.h"

#include "SDL/include/SDL_opengl.h"
#include "par/parshapes.h"

#include "mmgr/mmgr.h"

ModuleSceneIntro::ModuleSceneIntro(bool start_enabled) : Module(start_enabled)
{ 
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	App->Console_Log("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(0.0f, 50.0f, 25.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	//HouseTexture = App->texture->LoadTexturePath("Assets/Baker_house.png");
	//App->geometry->LoadFileFromPath("Assets/BakerHouse.fbx"); 

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
	return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}


void ModuleSceneIntro::Create_Sphere(int slices, int stacks, float x, float y, float z, float size)
{
	Body = par_shapes_create_parametric_sphere(slices, stacks);

	position.x = x;
	position.y = y;
	position.z = z;

	par_shapes_scale(Body, size, size, size);
	par_shapes_translate(Body, position.x, position.y, position.z);

	App->geometry->LoadParShapes(Body, position); 
}

void ModuleSceneIntro::Create_Cube(float x, float y, float z, float size)
{
	/*Body = par_shapes_create_cube();

	position.x = x;
	position.y = y;
	position.z = z;

	par_shapes_scale(Body, size, size, size);
	par_shapes_translate(Body, position.x, position.y, position.z);

	App->geometry->LoadParShapes(Body, position);*/ 

	/*float vertices[] = {
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

	glEnable(GL_DEPTH_TEST);*/
}

void ModuleSceneIntro::Create_Cylinder(float x, float y, float z, uint size, int slices, uint stacks)
{
	Body = par_shapes_create_cylinder(slices, stacks);

	position.x = x;
	position.y = y;
	position.z = z;

	const float xaxis[] = { 1, 0, 0 };

	par_shapes_scale(Body, size, size, size);
	par_shapes_translate(Body, position.x, position.y, position.z);
	par_shapes_rotate(Body, 1.57f, xaxis);

	App->geometry->LoadParShapes(Body, position);
}

void ModuleSceneIntro::Create_Torus(float x, float y, float z, uint size, uint radius, int slices, uint stacks)
{
	Body = par_shapes_create_torus(slices, stacks, radius);

	position.x = x;
	position.y = y;
	position.z = z;

	par_shapes_scale(Body, size, size, size);
	par_shapes_translate(Body, position.x, position.y, position.z);

	App->geometry->LoadParShapes(Body, position);
}

void ModuleSceneIntro::Create_Trefoil(float x, float y, float z, uint size, uint radius, int slices, uint stacks)
{
	Body = par_shapes_create_trefoil_knot(slices, stacks, radius); 

	position.x = x;
	position.y = y;
	position.z = z;

	par_shapes_scale(Body, size, size, size);
	par_shapes_translate(Body, position.x, position.y, position.z);

	App->geometry->LoadParShapes(Body, position);
}


