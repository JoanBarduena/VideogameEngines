#include "Globals.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
#include "GameObject.h"

#include "glew/include/GL/glew.h"
#include "SDL/include/SDL_opengl.h"

#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */
#pragma comment(lib, "glew/libx86/glew32.lib")

#include "mmgr/mmgr.h"

ModuleRenderer3D::ModuleRenderer3D(bool start_enabled) : Module(start_enabled)
{
}

// Destructor
ModuleRenderer3D::~ModuleRenderer3D()
{}

// Called before render is available
bool ModuleRenderer3D::Init()
{
	App->Console_Log("[CREATING]: 3D Renderer context");
	bool ret = true;

	//Create context
	context = SDL_GL_CreateContext(App->window->window);
	if(context == NULL)
	{
		App->Console_Log("[WARNING]: OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	
	if(ret == true)
	{
		//Use Vsync
		if(VSYNC && SDL_GL_SetSwapInterval(1) < 0)
			App->Console_Log("[WARNING]: Unable to set VSync! SDL Error: %s\n", SDL_GetError());

		//Init Glew
		GLenum error = glewInit();

		//Initialize Projection Matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();


		if(error != GL_NO_ERROR)
		{
			App->Console_Log("[ERROR]: initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}

		//Orthogonal view
		glOrtho(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 1.0f, -1.0f);

		//Initialize Modelview Matrix
		glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();

		//Check for error
		error = glGetError();

		if(error != GL_NO_ERROR)
		{
			App->Console_Log("[ERROR]: initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}
		
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glClearDepth(1.0f);
		
		//Initialize clear color
		glClearColor(0.f, 0.f, 0.f, 1.f);

		//Check for error
		error = glGetError();
		if(error != GL_NO_ERROR)
		{
			App->Console_Log("[ERROR]: initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}
		
		GLfloat LightModelAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightModelAmbient);
		
		lights[0].ref = GL_LIGHT0;
		lights[0].ambient.Set(0.25f, 0.25f, 0.25f, 1.0f);
		lights[0].diffuse.Set(0.75f, 0.75f, 0.75f, 1.0f);
		lights[0].SetPos(0.0f, 0.0f, 2.5f);
		lights[0].Init();
		
		GLfloat MaterialAmbient[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MaterialAmbient);

		GLfloat MaterialDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MaterialDiffuse);
		
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		lights[0].Active(true);
		glEnable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_TEXTURE_2D);
	}

	// Projection matrix for
	OnResize(SCREEN_WIDTH, SCREEN_HEIGHT);

	return ret;
}

// PreUpdate: clear buffer
update_status ModuleRenderer3D::PreUpdate(float dt)
{
	Color c = App->camera->background;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(App->camera->GetViewMatrix());

	// light 0 on cam pos
	lights[0].SetPos(App->camera->Position.x, App->camera->Position.y, App->camera->Position.z);

	for(uint i = 0; i < MAX_LIGHTS; ++i)
		lights[i].Render();

	return UPDATE_CONTINUE;
}

// PostUpdate present buffer to screen
update_status ModuleRenderer3D::PostUpdate(float dt)
{
	DrawAABB(); 
	App->gui->Draw(); 
	SDL_GL_SwapWindow(App->window->window);
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRenderer3D::CleanUp()
{
	App->Console_Log("Destroying 3D Renderer");

	SDL_GL_DeleteContext(context);

	return true;
}


void ModuleRenderer3D::OnResize(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	ProjectionMatrix = perspective(60.0f, (float)width / (float)height, 0.125f, 512.0f);
	glLoadMatrixf(&ProjectionMatrix);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//Make a Draw() method in ModuleRenderer that receives a mesh and draws it
void ModuleRenderer3D::DrawMesh(GameObject* GO)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	ComponentMesh* mesh = GO->GetComponentMesh();
	ComponentTexture* c_texture = GO->GetComponentTexture(); 

	if (c_texture != nullptr)
		glBindTexture(GL_TEXTURE_2D, c_texture->texture.textureID); //getcomponenttexture->structtexture->id
	else
		glBindTexture(GL_TEXTURE_2D, App->Mtexture->DefaultTexture.textureID);

	if (mesh != nullptr)
	{
		glBindBuffer(GL_ARRAY_BUFFER, mesh->id_vertex); //Gameobject->Getcomponentmesh->id_vertex
		glVertexPointer(3, GL_FLOAT, 0, NULL);

		glBindBuffer(GL_ARRAY_BUFFER, mesh->id_texture);
		glTexCoordPointer(2, GL_FLOAT, 0, NULL);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->id_index);
		glDrawElements(GL_TRIANGLES, mesh->num_index, GL_UNSIGNED_INT, nullptr);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);

		glDisableClientState(GL_VERTEX_ARRAY);
	}

	if(render_aabb)
		mesh->DrawAABB(); 
}

void ModuleRenderer3D::AddAABB(const AABB& container, const Color& color)
{
	aabbs.push_back(RenderBox<AABB>(&container, color));
}

void ModuleRenderer3D::DrawAABB()
{
	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);

	for(uint i = 0; i < aabbs.size(); i++)
	{
		DrawContainer(*aabbs[i].container, aabbs[i].color); 
	}	
	aabbs.clear(); 

	glEnd();
	glEnable(GL_LIGHTING);
}

void ModuleRenderer3D::DrawContainerCube(const float3* corners, Color color)
{
	glColor4f(color.r, color.g, color.b, color.a);

	//Between-planes right
	glVertex3fv((GLfloat*)&corners[1]);
	glVertex3fv((GLfloat*)&corners[5]);
	glVertex3fv((GLfloat*)&corners[7]);
	glVertex3fv((GLfloat*)&corners[3]);

	//Between-planes left
	glVertex3fv((GLfloat*)&corners[4]);
	glVertex3fv((GLfloat*)&corners[0]);
	glVertex3fv((GLfloat*)&corners[2]);
	glVertex3fv((GLfloat*)&corners[6]);

	//Far plane horizontal
	glVertex3fv((GLfloat*)&corners[5]);
	glVertex3fv((GLfloat*)&corners[4]);
	glVertex3fv((GLfloat*)&corners[6]);
	glVertex3fv((GLfloat*)&corners[7]);

	//Near plane horizontal
	glVertex3fv((GLfloat*)&corners[0]);
	glVertex3fv((GLfloat*)&corners[1]);
	glVertex3fv((GLfloat*)&corners[3]);
	glVertex3fv((GLfloat*)&corners[2]);

	//Near plane vertical
	glVertex3fv((GLfloat*)&corners[1]);
	glVertex3fv((GLfloat*)&corners[3]);
	glVertex3fv((GLfloat*)&corners[0]);
	glVertex3fv((GLfloat*)&corners[2]);

	//Far plane vertical
	glVertex3fv((GLfloat*)&corners[5]);
	glVertex3fv((GLfloat*)&corners[7]);
	glVertex3fv((GLfloat*)&corners[4]);
	glVertex3fv((GLfloat*)&corners[6]);

}
