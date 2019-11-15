#include "GameObject.h"

GameObject::GameObject(string name_)
{
	this->name = name_; 
	mesh = (ComponentMesh*)CreateComponent(Type::Mesh); 
	texture = (ComponentTexture*)CreateComponent(Type::Texture);
	transform = (ComponentTransform*)CreateComponent(Type::Transform);
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
	case Type::Texture:
		comp = new ComponentTexture(this); 
		break; 
	case Type::Transform:
		comp = new ComponentTransform(this); 
		break; 
	}

	components.push_back(comp); 

	return comp; 
}

void GameObject::Update()
{
}
