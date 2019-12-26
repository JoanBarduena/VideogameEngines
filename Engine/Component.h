#pragma once
#include "Globals.h"

class GameObject;

class Component
{
public:
	ALIGN_CLASS_TO_16

	enum class Type
	{
		NONE = -1,
		Transform,
		Mesh,
		Texture, 
		UI
	};

	Component(GameObject* my_GO, Component::Type comp_type); 
	~Component(); 

	virtual bool Enable(); 
	virtual bool Update(); 
	virtual bool Disable(); 

public: 

	Component::Type type;
	bool active;
	GameObject* my_go = nullptr; 
};
