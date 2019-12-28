#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"

#include "mmgr/mmgr.h"

#define MAX_KEYS 300

ModuleInput::ModuleInput(bool start_enabled) : Module(start_enabled)
{
	keyboard = new KEY_STATE[MAX_KEYS];
	memset(keyboard, KEY_IDLE, sizeof(KEY_STATE) * MAX_KEYS);
	memset(mouse_buttons, KEY_IDLE, sizeof(KEY_STATE) * MAX_MOUSE_BUTTONS);
}

// Destructor
ModuleInput::~ModuleInput()
{
}

// Called before render is available
bool ModuleInput::Init()
{
	App->Console_Log("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		App->Console_Log("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate(float dt)
{
	SDL_PumpEvents();

	const Uint8* keys = SDL_GetKeyboardState(NULL);
	
	for(int i = 0; i < MAX_KEYS; ++i)
	{
		if(keys[i] == 1)
		{
			if(keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if(keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	Uint32 buttons = SDL_GetMouseState(&mouse_x, &mouse_y);

	mouse_x /= SCREEN_SIZE;
	mouse_y /= SCREEN_SIZE;
	mouse_z = 0;

	for(int i = 0; i < 5; ++i)
	{
		if(buttons & SDL_BUTTON(i))
		{
			if(mouse_buttons[i] == KEY_IDLE)
				mouse_buttons[i] = KEY_DOWN;
			else
				mouse_buttons[i] = KEY_REPEAT;
		}
		else
		{
			if(mouse_buttons[i] == KEY_REPEAT || mouse_buttons[i] == KEY_DOWN)
				mouse_buttons[i] = KEY_UP;
			else
				mouse_buttons[i] = KEY_IDLE;
		}
	}

	mouse_x_motion = mouse_y_motion = 0;

	bool quit = false;
	SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		switch(e.type)
		{
			case SDL_MOUSEWHEEL:
			mouse_z = e.wheel.y;
			break;

			case SDL_MOUSEMOTION:
			mouse_x = e.motion.x / SCREEN_SIZE;
			mouse_y = e.motion.y / SCREEN_SIZE;

			mouse_x_motion = e.motion.xrel / SCREEN_SIZE;
			mouse_y_motion = e.motion.yrel / SCREEN_SIZE;
			break;

			case SDL_DROPFILE: 
			dropped_filedir = e.drop.file;

			if (GetFileExtension(dropped_filedir) == "fbx" || GetFileExtension(dropped_filedir) == "FBX")
			{
				App->geometry->LoadFileFromPath(dropped_filedir);
				App->Console_Log("File .FBX dropped with root: %s", dropped_filedir);
			}	
			else if (GetFileExtension(dropped_filedir) == "png" || GetFileExtension(dropped_filedir) == "dds" || 
				GetFileExtension(dropped_filedir) == "tga" || GetFileExtension(dropped_filedir) == "TGA" || 
				GetFileExtension(dropped_filedir) == "PNG")
			{
				if (App->gui->inspector_w->selected_go != nullptr)
				{
					if (App->gui->inspector_w->selected_go->GetComponentTexture() != nullptr)
					{
						App->gui->inspector_w->selected_go->GetComponentTexture()->texture = App->Mtexture->LoadTexturePath(dropped_filedir);
						App->Console_Log("Texture dropped with root: %s", dropped_filedir);
					}
					else
					{
						App->Console_Log("[WARNING]: Select a GameObject with a ComponentTexture."); 
					}
				}
				else
					App->Console_Log("[WARNING]: A Game Object must be selected before dropping a file.");
			}
			else
				App->Console_Log("[WARNING]: File format not accepted. Use formats: .fbx, .png, .dds");

			SDL_free(dropped_filedir);
			break;

			case SDL_QUIT:
			quit = true;
			break;

			case SDL_WINDOWEVENT:
			{
				if(e.window.event == SDL_WINDOWEVENT_RESIZED)
					App->renderer3D->OnResize(e.window.data1, e.window.data2);
			}
		}		
		ImGui_ImplSDL2_ProcessEvent(&e);	
	}

	if(quit == true || keyboard[SDL_SCANCODE_ESCAPE] == KEY_UP)
		return UPDATE_STOP;

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	App->Console_Log("Quitting SDL input event subsystem");
	delete[] keyboard;
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}

std::string ModuleInput::GetFileExtension(const std::string& FileName)
{
	if (FileName.find_last_of(".") != std::string::npos)
		return FileName.substr(FileName.find_last_of(".") + 1);
	else 
		return "";
}