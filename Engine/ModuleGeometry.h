#ifndef __MODULEGEOMETRY_H__
#define __MODULEGEOMETRY_H__

#include "Module.h"

#include "MathGeoLib/include/MathBuildConfig.h"
#include "MathGeoLib/include/MathGeoLib.h"

struct mesh_data
{
	uint id_index = 0; // index in VRAM
	uint num_index = 0;
	uint* index = nullptr;

	uint id_vertex = 0; // unique vertex in VRAM
	uint num_vertex = 0;
	float3* vertex = nullptr;

	uint id_texture = 0; 
	uint num_texture = 0; 
	float* texture_pos = nullptr; 

	uint texture = 0; 

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

	void VertexBuffer(uint &id, uint &size, float3 * vertices);
	void IndexBuffer(uint &id, uint &size, const uint * indices);
	void TextureBuffer(uint & id, uint & num_texture, float * texture_pos);

	std::vector<mesh_data*> meshes; 
};


#endif
