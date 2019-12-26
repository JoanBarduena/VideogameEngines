#pragma once
#include "Module.h"

class SceneImporter
{
public: 

	SceneImporter();
	~SceneImporter();

	bool Init();

	bool ImportMesh(const char* path, ComponentMesh* mesh);
	bool ExportMesh(const char* name, const char* path, std::string& output_file, ComponentMesh* mesh);
};