#include "Globals.h"
#include "Application.h"
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

	// Initialize root 
	root = CreateGameObject();
	root->name = "ROOT";

	App->geometry->LoadFileFromPath("Assets/Street/Street environment_V01.fbx");

	// ------ DEMO UI -------
	canvas = CreateCanvas();
	image = CreateImage(canvas);
	button = CreateButton(canvas); 
	image->GetComponentTexture()->texture = App->Mtexture->LoadTexturePath("Assets/ImageDemo.png");
	// ----------------------

	fbo_scene = new FBO(); 
	fbo_scene->Start(App->gui->scene_w->w_Size.x, App->gui->scene_w->w_Size.y);

	//fbo_game = new FBO(); 
	//fbo_game->Start(App->gui->game_w->w_Size.x, App->gui->game_w->w_Size.y); 
	
	return ret;
}

update_status ModuleViewport::PreUpdate(float dt)
{
	if (App->gui->scene_w->OnResize())
	{
		fbo_scene->Start(App->gui->scene_w->w_Size.x, App->gui->scene_w->w_Size.y);
		App->renderer3D->OnResize(App->gui->scene_w->w_Size.x, App->gui->scene_w->w_Size.y);
	}

	//if (App->gui->game_w->OnResize())
	//{
	//	fbo_scene->Start(App->gui->game_w->w_Size.x, App->gui->game_w->w_Size.y);
	//	App->renderer3D->OnResize(App->gui->game_w->w_Size.x, App->gui->game_w->w_Size.y);
	//}

	fbo_scene->Draw();
	//fbo_game->Draw();

	if (render_grid)
	{
		glLineWidth(2.0f);
		// Grid plane made with GL_Lines
		glBegin(GL_LINES);
		glColor3ub(255, 255, 255);
		for (float i = -50; i <= 50; ++i)
		{
			glVertex3f(i, 0.f, 0.f);
			glVertex3f(i, 0, 50.0f);

			glVertex3f(0.f, 0.f, i);
			glVertex3f(50.f, 0, i);

			glVertex3f(i, 0.f, 0.f);
			glVertex3f(i, 0, -50.f);

			glVertex3f(0.f, 0.f, i);
			glVertex3f(-50.f, 0, i);
		}
		glEnd();
	}

	return UPDATE_CONTINUE;
}

update_status ModuleViewport::Update(float dt)
{
	root->Update(dt);

	return UPDATE_CONTINUE;
}

update_status ModuleViewport::PostUpdate(float dt)
{
	DrawRecursively(root);
	fbo_scene->Undraw(); 
	//fbo_game->Undraw(); 

	return UPDATE_CONTINUE;
}

bool ModuleViewport::CleanUp()
{
	bool ret = true;

	RELEASE(fbo_scene); 
	//RELEASE(fbo_game); 

	root->DeleteGO(root, true);

	return ret;
}

void ModuleViewport::DrawRecursively(GameObject* GO)
{
	// Not the root and GO is active
	if (GO->id != 0 && GO->active == true)
	{
		glPushMatrix();
		glMultMatrixf((GLfloat*)&GO->GetComponentTransform()->GetGlobalTransform().Transposed());
		App->renderer3D->DrawMesh(GO);
		glPopMatrix();
	}

	if (GO->childs.size() > 0)
	{
		for (std::vector<GameObject*>::iterator it = GO->childs.begin(); it != GO->childs.end(); ++it)
		{
			DrawRecursively(*it);
		}
	}
}

void ModuleViewport::SetGameObjectStatic(GameObject* go)
{
	if (go->go_static == true)
	{
		static_meshes.push_back(go->GetComponentMesh());
	}
	else
	{
		for (std::vector<ComponentMesh*>::iterator i = static_meshes.begin(); i != static_meshes.end(); ++i)
		{
			if ((*i)->my_go->id == go->id)
			{
				static_meshes.erase(i);
				break;
			}
		}
	}
}

GameObject* ModuleViewport::CreateGameObject()
{
	std::string GOname = "GameObject ";
	GOname.append(std::to_string(game_objects.size()));

	GameObject* object = nullptr;
	object = new GameObject(GOname);
	object->id = game_objects.size();

	if (object->id != 0)
		root->DefineChilds(object);

	game_objects.push_back(object);

	return object;
}

GameObject* ModuleViewport::CreateCanvas()
{
	std::string CanvasName = "Canvas ";
	CanvasName.append(std::to_string(num_canvas));

	GameObject* canvas = nullptr;
	canvas = new GameObject(CanvasName);
	canvas->unactive_name = CanvasName.append(" [not active]");
	canvas->id = game_objects.size();

	canvas->CreateComponent(Component::Type::CANVAS);

	root->DefineChilds(canvas);

	App->Console_Log("[CREATING UI OBJECT]: Canvas");
	num_canvas++;
	game_objects.push_back(canvas);

	return canvas;
}

GameObject* ModuleViewport::CreateImage(GameObject* parent)
{
	GameObject* image = nullptr;

	if (parent != nullptr)
	{
		std::string ImageName = "Image ";
		ImageName.append(std::to_string(num_image));

		image = new GameObject(ImageName);
		image->unactive_name = ImageName.append(" [not active]");
		image->id = game_objects.size();

		App->geometry->LoadImageFBX("Assets/ImageUI.fbx", image);

		parent->DefineChilds(image);

		image->CreateComponent(Component::Type::IMAGE);

		// Centered on the canvas
		ComponentTransform* transform_ = parent->GetComponentTransform();

		if (parent->GetComponentCanvas() != nullptr)
		{
			float3 pos_;
			pos_.x = transform_->GetPosition().x + (parent->GetComponentCanvas()->width / 2);
			pos_.y = transform_->GetPosition().y + (parent->GetComponentCanvas()->height / 2);
			pos_.z = transform_->GetPosition().z;

			// Scale
			float3 scale_;
			scale_.x = 8;
			scale_.y = 8;
			scale_.z = 1;

			//Initial position on the canvas square
			image->GetComponentTransform()->SetPosition(pos_);

			image->GetComponentTransform()->SetScale(scale_);
		}

		App->Console_Log("[CREATING UI OBJECT]: Image");
		num_image++;
		game_objects.push_back(image);
	}

	return image;
}

GameObject* ModuleViewport::CreateButton(GameObject* parent)
{
	GameObject* button = nullptr;

	if (parent != nullptr)
	{
		std::string ButtonName = "Button ";
		ButtonName.append(std::to_string(num_button));

		button = new GameObject(ButtonName);
		button->unactive_name = ButtonName.append(" [not active]");
		button->id = game_objects.size();

		App->geometry->LoadImageFBX("Assets/ImageUI.fbx", button);

		parent->DefineChilds(button);

		button->CreateComponent(Component::Type::BUTTON);

		// Centered on the canvas
		ComponentTransform* transform_ = parent->GetComponentTransform();

		if (parent->GetComponentCanvas() != nullptr)
		{
			float3 pos_;

			pos_.x = transform_->GetPosition().x + (parent->GetComponentCanvas()->width / 2) - 10;
			pos_.y = transform_->GetPosition().y + (parent->GetComponentCanvas()->height / 2);
			pos_.z = transform_->GetPosition().z;

			// Scale
			float3 scale_;
			scale_.x = 6;
			scale_.y = 2;
			scale_.z = 1;

			//Initial position on the canvas square
			button->GetComponentTransform()->SetPosition(pos_);

			button->GetComponentTransform()->SetScale(scale_);
		}
		App->Console_Log("[CREATING UI OBJECT]: Button");
		num_button++;
		game_objects.push_back(button);
	}

	return image;
}

