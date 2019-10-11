#pragma once


#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleSceneIntro.h"
#include "ModuleGui.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModuleGeometry.h"

#include <list>
#include <vector>
#include <string>

using namespace std;

class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleSceneIntro* scene_intro;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera; 
	ModuleGui* gui; 
	ModuleGeometry* geometry;

private:

	Timer	ms_timer;
	float	dt;
	list<Module*> list_modules;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

	void RequestBrowser(const char* URL); 

	void Console_Log(const char * format, ...);
	std::vector<std::string> vector_log; 

private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
};

