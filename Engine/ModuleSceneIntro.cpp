#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"

#include "SDL/include/SDL_opengl.h"
#include "par/parshapes.h"

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

	HouseTexture = App->texture->LoadTexturePath("Assets/Baker_house.png");
	App->geometry->LoadGeometry("Assets/BakerHouse.fbx"); 

	Texture = HouseTexture; 
	
	//Create_Cube(0,0,0,2);
	//Create_Sphere(50,20,0,1,0,1); 
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

	for (int i = 0; i < vector_shapes.size(); i++)
	{
		RenderObject();
	}
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::CreateBuffer()
{
	if (Body != nullptr)
	{
		//vertex
		glGenBuffers(1, (GLuint*) &(id_vertex));
		glBindBuffer(GL_ARRAY_BUFFER, id_vertex);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * Body->npoints * 3, Body->points, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//indices
		glGenBuffers(1, (GLuint*) &(id_index));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_index);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(PAR_SHAPES_T) * Body->ntriangles * 3, Body->triangles, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		//texture
		glGenBuffers(1, (GLuint*)&(id_texture));
		glBindBuffer(GL_ARRAY_BUFFER, id_texture);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * Body->npoints * 6, Body->tcoords, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

void ModuleSceneIntro::RenderObject()
{
	glEnableClientState(GL_VERTEX_ARRAY);

	//Enable texture
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Texture);
	glBindBuffer(GL_ARRAY_BUFFER, id_texture);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);

	//vertex
	glBindBuffer(GL_ARRAY_BUFFER, id_vertex);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	//index
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_index);
	glDrawElements(GL_TRIANGLES, Body->ntriangles * 3, GL_UNSIGNED_SHORT, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisableClientState(GL_VERTEX_ARRAY);
}

void ModuleSceneIntro::Create_Sphere(int slices, int stacks, float x, float y, float z, float size)
{
	Body = par_shapes_create_parametric_sphere(slices, stacks);

	position.x = x;
	position.y = y;
	position.z = z;

	par_shapes_scale(Body, size, size, size);
	par_shapes_translate(Body, position.x, position.y, position.z);

	vector_shapes.push_back(Body);

	Texture = App->texture->checkersTextureID;

	CreateBuffer();
}

void ModuleSceneIntro::Create_Cube(float x, float y, float z, float size)
{
	Body = par_shapes_create_cube();

	position.x = x;
	position.y = y;
	position.z = z;

	par_shapes_scale(Body, size, size, size);
	par_shapes_translate(Body, position.x, position.y, position.z);

	//vector_shapes.push_back(Body);

	CreateBuffer();
}
