#include "GameObject.h"
#include "ComponentMesh.h"

GameObject::GameObject(string name_)
{
	this->name = name_; 
	Mesh = (ComponentMesh*)CreateComponent(Type::Mesh); 
}

GameObject::~GameObject()
{
}

Component* GameObject::CreateComponent(Type type)
{
	Component* comp = nullptr; 

	switch (type)
	{
	case Type::Mesh:
		comp = new ComponentMesh(this); 
		break; 
	}

	components.push_back(comp); 

	return comp; 
}

void GameObject::Update()
{
}
