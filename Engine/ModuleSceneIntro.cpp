#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"

#include "SDL/include/SDL_opengl.h"
#include "par/parshapes.h"

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

	App->camera->Move(vec3(0.0f, 5.0f, 15.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	HouseTexture = App->texture->LoadTexturePath("Assets/Baker_house.png");
	App->geometry->LoadGeometry("Assets/BakerHouse.fbx"); 
	
	for (std::vector<GameObject*>::iterator iterator = game_objects.begin(); iterator != game_objects.end(); iterator++)
	{
		(*iterator)->Comp_Texture->texture = HouseTexture; 
	}

	//Create_Cube(0,0,0,2);
	Create_Sphere(50,20,5,1,0,1); 
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

	for (std::vector<GameObject*>::iterator iterator = game_objects.begin(); iterator != game_objects.end(); iterator++)
	{
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

	game_objects.push_back(object); 

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
}
