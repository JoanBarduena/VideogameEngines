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
	vector<Component*> components; 

	ComponentMesh* Comp_Mesh; 
	ComponentTexture* Comp_Texture; 
	ComponentTransform* Comp_Transform; 
};


