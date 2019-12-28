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
		TRANSFORM,
		MESH,
		TEXTURE, 
		CANVAS, 
		IMAGE
	};

	Component(GameObject* my_GO, Component::Type comp_type); 
	~Component(); 

	virtual bool Enable(); 
	virtual bool Update(); 
	virtual bool Disable(); 
	virtual bool CleanUp(); 

public: 

	Component::Type type;
	bool active;
	GameObject* my_go = nullptr; 
	uint height = 0, width = 0; 
};
