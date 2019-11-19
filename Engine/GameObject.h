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
	void RemoveGameObject(); 

	void Update(float dt);
	void UpdateTransformation(GameObject* GO);

public:

	string name; 
	string unactive_name; 
	bool active; 
	uint id; 

	vector<Component*> components; 

	ComponentMesh* mesh = nullptr; 
	ComponentTexture* texture = nullptr;
	ComponentTransform* c_transform = nullptr;

	GameObject* parent = nullptr; 
	std::vector<GameObject*> childs; 
};


