#pragma once

#include "Globals.h"
#include "Component.h"
#include "ComponentMesh.h"

class GameObject
{
public: 

	GameObject(string name); 
	~GameObject();
	Component * CreateComponent(Type type);

	void Update(); 

public:

	string name; 
	bool active; 
	vector<Component*> components; 

	ComponentMesh* Mesh; 
};


