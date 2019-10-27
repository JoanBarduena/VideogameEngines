#pragma once
class GameObject; 

enum Type 
{
	Transform, 
	Mesh, 
	Texture
};

class Component
{
public:

	Component(GameObject* my_GO, Type type_); 
	~Component(); 

	virtual bool Enable(); 
	virtual bool Update(); 
	virtual bool Disable(); 

public: 

	Type type;
	bool active;
	GameObject* my_go; 
};
