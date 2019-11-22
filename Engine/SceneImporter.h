#pragma once
#include "Module.h"

class SceneImporter
{
public: 

	SceneImporter();
	~SceneImporter();

	bool Init();

	bool ImportMesh(const char* path, GameObject* go);
	bool ExportMesh(const char* name, const char* path, std::string& output_file, GameObject* go);
};