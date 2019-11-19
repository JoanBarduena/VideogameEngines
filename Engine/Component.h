#pragma once
class GameObject; 



class Component
{
public:

	enum class Type
	{
		NONE = -1,
		Transform,
		Mesh,
		Texture
	};

	Component(GameObject* my_GO, Component::Type type_); 
	~Component(); 

	virtual bool Enable(); 
	virtual bool Update(); 
	virtual bool Disable(); 

public: 

	Component::Type type;
	bool active;
	GameObject* my_go; 
};
