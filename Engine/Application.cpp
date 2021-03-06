#include "Application.h"
#include "mmgr/mmgr.h"

Application::Application()
{
	window =		new ModuleWindow(this);
	input =			new ModuleInput(this);
	scene_intro =	new ModuleSceneIntro(this);
	renderer3D =	new ModuleRenderer3D(this);
	camera =		new ModuleCamera3D(this);
	gui =			new ModuleGui(this); 
	geometry =		new ModuleGeometry(this);
	Mtexture =		new ModuleTexture(this);
	filesystem =	new ModuleFileSystem(this, ASSETS_FOLDER);
	viewport  =		new ModuleViewport(this);

	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(camera);
	AddModule(input);

	// Geometry and textures
	AddModule(geometry);
	AddModule(Mtexture);

	// FileSystem
	AddModule(filesystem);
	AddModule(viewport);

	// Scenes
	AddModule(scene_intro);

	// Gui
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

	Console_Log("GRINGO ENGINE. Copyright (c) 2019 Lidux");

	// Call Init() in all modules
	Console_Log("-------------- Application Init --------------");
	for (list<Module*>::iterator item = list_modules.begin(); item != list_modules.end() && ret == true; item++)
	{
		ret = (*item)->Init();
	}
	
	// After all Init calls we call Start() in all modules
	Console_Log("-------------- Application Start --------------");
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
	fps.push_back(1.0f / dt);
	if (fps.size() > FPS_LOG_SIZE)
	{
		fps.erase(fps.begin());
	}
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
		RELEASE(*item); 
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
	sprintf_s(tmp_string2, 4096, "\n%s", tmp_string);
	OutputDebugString(tmp_string2);

	//Implementation
	const char* log_str = tmp_string2;
	vector_log.push_back(log_str);
}

const std::string Application::GetNameFromPath(std::string path)
{
	std::string name = path;

	uint num = name.find_last_of("/\\");
	name = name.substr(num + 1, name.size());

	uint dot = name.find_last_of(".");
	name = name.substr(0, dot);

	return name;
}

const std::string Application::GetDirectoryFromPath(std::string path)
{
	std::string directory;
	size_t found = path.find_last_of("/\\");
		directory = path.substr(0, found);

	return directory;
}



