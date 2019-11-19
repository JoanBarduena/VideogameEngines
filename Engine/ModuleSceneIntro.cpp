#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"

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

	// Initialize root 
	root = CreateGameObject();
	root->name = "Root";	

	App->camera->Move(vec3(0.0f, 5.0f, 15.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	HouseTexture = App->texture->LoadTexturePath("Assets/Baker_house.png");
	App->geometry->LoadGeometry("Assets/BakerHouse.fbx"); 
	
	for (std::vector<GameObject*>::iterator iterator = game_objects.begin(); iterator != game_objects.end(); iterator++)
	{
		(*iterator)->texture->texture = HouseTexture; 
	}

	//Create_Cube(0,0,0,2);
	//Create_Sphere(50,20,5,1,0,1); 
	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	App->Console_Log("Unloading Intro scene");
	
	root->CleanUp(); 

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	glLineWidth(2.0f);

	// Grid plane made with GL_Lines
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

	for (std::vector<GameObject*>::iterator iterator = game_objects.begin(); iterator != game_objects.end(); iterator++)
	{
		if((*iterator)->active)
			App->renderer3D->DrawMesh((*iterator));
	}

	return UPDATE_CONTINUE;
}


GameObject * ModuleSceneIntro::CreateGameObject()
{
	std::string GOname = "GameObject "; 
	GOname.append(std::to_string(game_objects.size()));

	GameObject* object = nullptr; 
	object = new GameObject(GOname);
	object->id = game_objects.size();

	object->unactive_name = GOname.append(" [not active]");

	game_objects.push_back(object); 

	if (object->id != 0)
		root->DefineChilds(object); 

	return object; 
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
	Body = par_shapes_create_cube();

	position.x = x;
	position.y = y;
	position.z = z;

	par_shapes_scale(Body, size, size, size);
	par_shapes_translate(Body, position.x, position.y, position.z);

	App->geometry->LoadParShapes(Body, position); 

	//float vertices[] = {
	//	//front
	//	x + 0.0,	y + 0.0,	z + size,
	//	x + size,	y + 0.0,	z + size,
	//	x + size,   y + size,	z + size,
	//	x + 0.0,	y + size,	z + size,
	//	// back
	//	x + 0.0,	y + 0.0,	z + 0.0,
	//	x + size,	y + 0.0,    z + 0.0,
	//	x + size,	y + size,   z + 0.0,
	//	x + 0.0,	y + size,	z + 0.0
	//};

	//uint indices[] = {
	//	//front
	//		0, 1, 2,
	//		2, 3, 0,
	//		// right
	//		1, 5, 6,
	//		6, 2, 1,
	//		// back
	//		7, 6, 5,
	//		5, 4, 7,
	//		// left
	//		4, 0, 3,
	//		3, 7, 4,
	//		// bottom
	//		4, 5, 1,
	//		1, 0, 4,
	//		// top
	//		3, 2, 6,
	//		6, 7, 3
	//};

	//uint my_id = 0;
	//glGenBuffers(1, (GLuint*) &(my_id));
	//glBindBuffer(GL_ARRAY_BUFFER, my_id);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//uint my_indices = 0;
	//glGenBuffers(1, (GLuint*) &(my_indices));
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_indices);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//glEnableClientState(GL_VERTEX_ARRAY);
	//glVertexPointer(3, GL_FLOAT, 0, NULL);
	//glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, NULL);
	//glDisableClientState(GL_VERTEX_ARRAY);

	//glEnable(GL_DEPTH_TEST);
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


