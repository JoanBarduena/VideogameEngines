#pragma once
#include "Module.h"

class ModuleImporter : public Module
{
public: 

	ModuleImporter(bool start_enabled = true);
	~ModuleImporter();

	bool Init();
	update_status Update(float dt);
	bool CleanUp(); 

	bool Import(); 
};