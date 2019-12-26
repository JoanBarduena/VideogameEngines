#pragma once

#include "Globals.h"

#include "Component.h"
#include "ComponentMesh.h"
#include "ComponentTexture.h"
#include "ComponentTransform.h"

#include "ComponentUI.h"
#include "ComponentCanvas.h"

class GameObject
{
public: 

	GameObject(string name);
	~GameObject();
	void CleanUp();

	Component* CreateComponent(Component::Type type);
	ComponentUI* CreateComponentUI(ComponentUI::TypeUI typeUI);

	void DefineChilds(GameObject* GO);

	void Update(float dt);
	void UpdateTransformation(GameObject* GO);

	void DeleteGO(GameObject* GO, bool original);
	void RemoveChild(GameObject* go);

	ComponentTransform* GetComponentTransform(); 
	ComponentMesh* GetComponentMesh();
	ComponentTexture* GetComponentTexture();
public:

	string name; 
	string unactive_name; 
	bool active; 
	uint id; 
	bool go_static = false; 

	//Values to reset initial pos, scale and rotation
	float3 reset_pos = float3::zero; 
	float3 reset_scale = float3::one; 
	Quat reset_rotation = Quat::identity; 

	std::vector<Component*> components; 
	std::vector<ComponentUI*> componentsUI;

	GameObject* parent = nullptr; 
	std::vector<GameObject*> childs; 
};


