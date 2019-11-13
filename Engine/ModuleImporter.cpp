#include "Globals.h"
#include "Application.h"
#include "ModuleImporter.h"

// DevIL library ----------------------------
#include "DevIL/IL/il.h"
#include "DevIL/IL/ilu.h"
#include "DevIL/IL/ilut.h"

#pragma comment (lib, "DevIL/libx86/DevIL.lib")
#pragma comment (lib, "DevIL/libx86/ILU.lib")
#pragma comment (lib, "DevIL/libx86/ILUT.lib")

//#include "glew/include/GL/glew.h"

ModuleImporter::ModuleImporter(bool start_enabled):Module(start_enabled) {}

ModuleImporter::~ModuleImporter() {}

bool ModuleImporter::Init()
{
	bool ret = true; 
	// Checking current version
	if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION || iluGetInteger(ILU_VERSION_NUM) < ILU_VERSION || ilutGetInteger(ILUT_VERSION_NUM) < ILUT_VERSION)
	{
		App->Console_Log("DevIL version is different...exiting!\n");
		ret = false;
	}
	else
	{
		App->Console_Log("Initializing DevIL");

		ilInit();
		iluInit();
		ilutInit();

		// Initialize DevIL's OpenGL access
		ilutRenderer(ILUT_OPENGL);
	}

	return ret; 
}

update_status ModuleImporter::Update(float dt)
{
	return UPDATE_CONTINUE;
}

bool ModuleImporter::CleanUp()
{
	return true;
}

bool ModuleImporter::Import()
{
	return true;
}
