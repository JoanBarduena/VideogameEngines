#include "Application.h"

Application::Application()
{
	window =		new ModuleWindow(this);
	input =			new ModuleInput(this);
	scene_intro =	new ModuleSceneIntro(this);
	renderer3D =	new ModuleRenderer3D(this);
	camera =		new ModuleCamera3D(this);
	gui =			new ModuleGui(this);
	geometry =		new ModuleGeometry(this);
	texture =		new ModuleTexture(this);

	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(camera);
	AddModule(input);

	//Geometry and textures
	AddModule(geometry);
	AddModule(texture);

	// Scenes
	AddModule(scene_intro);
	AddModule(gui);

	// Renderer last!
	AddModule(renderer3D);
}

Application::~Application()
{
	list_modules.clear();
}

bool Application::Init()
{
	bool ret = true;

	// Call Init() in all modules
	Console_Log("Application Init --------------");
	for (list<Module*>::iterator item = list_modules.begin(); item != list_modules.end() && ret == true; item++)
	{
		ret = (*item)->Init();
	}
	
	// After all Init calls we call Start() in all modules
	Console_Log("Application Start --------------");
	for (list<Module*>::iterator item = list_modules.begin(); item != list_modules.end() && ret == true; item++)
	{
		ret = (*item)->Start();
	}



	ms_timer.Start();
	return ret;
}

// ---------------------------------------------
void Application::PrepareUpdate()
{
	dt = (float)ms_timer.Read() / 1000.0f;
	ms_timer.Start();
}

// ---------------------------------------------
void Application::FinishUpdate()
{
}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	PrepareUpdate();

	for (list<Module*>::iterator item = list_modules.begin(); item != list_modules.end() && ret == UPDATE_CONTINUE; item++)
	{
		ret = (*item)->PreUpdate(dt);
	}

	for (list<Module*>::iterator item = list_modules.begin(); item != list_modules.end() && ret == UPDATE_CONTINUE; item++)
	{
		ret = (*item)->Update(dt);
	}

	for (list<Module*>::iterator item = list_modules.begin(); item != list_modules.end() && ret == UPDATE_CONTINUE; item++)
	{
		ret = (*item)->PostUpdate(dt);
	}

	FinishUpdate();
	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (list<Module*>::reverse_iterator item = list_modules.rbegin(); item != list_modules.rend() && ret == true; item++)
	{
		ret = (*item)->CleanUp();
	}

	return ret;
}

void Application::AddModule(Module* mod)
{
	list_modules.push_back(mod);
}

void Application::RequestBrowser(const char* URL)
{
	ShellExecuteA(NULL, "open", URL, NULL, NULL, SW_SHOWNORMAL);
}

void Application::Console_Log(const char* format, ...)
{
	static char tmp_string[4096];
	static char tmp_string2[4096];
	static va_list  ap;

	// Construct the string from variable arguments
	va_start(ap, format);
	vsprintf_s(tmp_string, 4096, format, ap);
	va_end(ap);
	sprintf_s(tmp_string2, 4096, "\n%s(%d) : %s", tmp_string);
	OutputDebugString(tmp_string2);

	//Implementation
	const char* log_str = tmp_string2;
	vector_log.push_back(log_str);
}


