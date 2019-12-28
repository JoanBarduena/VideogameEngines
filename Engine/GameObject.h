#pragma once

#include "Globals.h"

#include "Component.h"
#include "ComponentMesh.h"
#include "ComponentTexture.h"
#include "ComponentTransform.h"

#include "ComponentUI.h"
#include "ComponentCanvas.h"
#include "ComponentImage.h"

class GameObject
{
public: 

	GameObject(string name);
	~GameObject();
	bool CleanUp();

	Component* CreateComponent(Component::Type type);

	void DefineChilds(GameObject* GO);

	bool HasChildren() const;

	void Update(float dt);
	void UpdateTransformation(GameObject* GO);

	void DeleteGO(GameObject* GO, bool original);
	void RemoveChild(GameObject* go);

	ComponentTransform* GetComponentTransform(); 
	ComponentMesh* GetComponentMesh();
	ComponentTexture* GetComponentTexture();

	ComponentCanvas* GetComponentCanvas();
	ComponentImage* GetComponentImage();
public:

	string name; 
	string unactive_name; 
	bool active = true; 
	bool was_unactive = false; 
	int id = -1; 
	bool go_static = false; 

	//Values to reset initial pos, scale and rotation
	float3 reset_pos = float3::zero; 
	float3 reset_scale = float3::one; 
	Quat reset_rotation = Quat::identity; 

	std::vector<Component*> components; 

	GameObject* parent = nullptr; 
	std::vector<GameObject*> childs; 
};


