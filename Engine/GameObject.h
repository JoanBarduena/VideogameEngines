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
	void DeleteGameObjects(); 

	void Update(float dt);
	void UpdateTransformation(GameObject* GO);


public:

	string name; 
	string unactive_name; 
	bool active; 
	uint id; 

	std::vector<Component*> components; 

	ComponentMesh* mesh = nullptr; 
	ComponentTexture* Ctexture = nullptr;
	ComponentTransform* transform = nullptr;

	GameObject* parent = nullptr; 
	std::vector<GameObject*> childs; 
};


