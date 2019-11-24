#pragma once

#include "Globals.h"
#include "Component.h"
#include "ComponentMesh.h"
#include "ComponentTexture.h"
#include "ComponentTransform.h"

class GameObject
{
public: 

	GameObject(string name);
	~GameObject();
	void CleanUp();

	Component* CreateComponent(Component::Type type);

	void DefineChilds(GameObject* GO);

	void Update(float dt);
	void UpdateTransformation(GameObject* GO);

	void DeleteGO(GameObject* GO, bool original);
	void RemoveChild(GameObject* go);

	ComponentMesh* DeleteMesh();

public:

	string name; 
	string unactive_name; 
	bool active; 
	uint id; 
	bool go_static; 

	//Values to reset initial pos, scale and rotation
	float3 reset_pos = float3::zero; 
	float3 reset_scale = float3::one; 
	Quat reset_rotation = Quat::identity; 

	std::vector<Component*> components; 

	ComponentMesh* mesh = nullptr; 
	ComponentTexture* Ctexture = nullptr;
	ComponentTransform* transform = nullptr;

	GameObject* parent = nullptr; 
	std::vector<GameObject*> childs; 
};


