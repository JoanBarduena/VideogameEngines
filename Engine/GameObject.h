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
	Component * CreateComponent(Type type);

	void Update(); 

public:

	string name; 
	bool active; 
	uint id; 

	vector<Component*> components; 

	ComponentMesh* mesh; 
	ComponentTexture* texture; 
	ComponentTransform* transform; 
};


