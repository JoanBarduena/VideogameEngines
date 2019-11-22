#ifndef __MODULEGEOMETRY_H__
#define __MODULEGEOMETRY_H__

#include "Module.h"
#include "ModuleSceneIntro.h"

#include "MathGeoLib/include/MathBuildConfig.h"
#include "MathGeoLib/include/MathGeoLib.h"
#include "Assimp/include/cimport.h"

#include "par/parshapes.h"
 
class aiNode; 
class aiScene; 
class aiMesh; 
class SceneImporter; 

class ModuleGeometry : public Module
{
public:
	ModuleGeometry(bool start_enabled = true);
	~ModuleGeometry();

	//bool Init();
	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void LoadFileFromPath(const char* full_path);
	void LoadNodeFromParent(const aiScene* file, aiNode* node, GameObject* parent, const char* full_path, SceneImporter exporter, std::string output_file);
	void LoadParShapes(par_shapes_mesh* par_mesh, Position pos);

	void VertexBuffer(uint &id, uint &size, float3 * vertices);
	void IndexBuffer(uint &id, uint &size, const uint * indices);
	void TextureBuffer(uint & id, uint & num_texture, float * texture_pos);

	void DefineTextureType(const aiScene* file, const aiMesh* new_mesh, GameObject* obj, const char* full_path);
};


#endif
