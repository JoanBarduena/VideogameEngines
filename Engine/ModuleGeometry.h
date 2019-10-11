#ifndef __MODULEGEOMETRY_H__
#define __MODULEGEOMETRY_H__

#include "Module.h"
#include <vector>

struct mesh_data
{
	uint id_index = 0; // index in VRAM
	uint num_index = 0;
	uint* index = nullptr;

	uint id_vertex = 0; // unique vertex in VRAM
	uint num_vertex = 0;
	float* vertex = nullptr;
};

class ModuleGeometry : public Module
{
public:
	ModuleGeometry(Application* app, bool start_enabled = true);
	~ModuleGeometry();

	//bool Init();
	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void LoadGeometry(const char* full_path);

	void VertexBuffer(uint &id, uint &size, const float * vertices);
	void IndexBuffer(uint &id, uint &size, const uint * indices);

	std::vector<mesh_data*> meshes; 
};


#endif
