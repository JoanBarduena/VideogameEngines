#pragma once
#include "Module.h"

class SceneImporter
{
public: 

	SceneImporter();
	~SceneImporter();

	bool Init();

	bool ImportMesh(const char* file, const char* path, std::string& output_file, GameObject* go);
	bool ExportMesh(const char* file, const char* path, std::string& output_file, GameObject* go);
};