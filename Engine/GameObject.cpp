#include "GameObject.h"

GameObject::GameObject(string name_)
{
	this->name = name_; 
	mesh = (ComponentMesh*)CreateComponent(Component::Type::Mesh); 
	texture = (ComponentTexture*)CreateComponent(Component::Type::Texture);
	transform = (ComponentTransform*)CreateComponent(Component::Type::Transform);
}

GameObject::~GameObject()
{
}

Component* GameObject::CreateComponent(Component::Type type)
{
	Component* comp = nullptr; 

	switch (type)
	{
	case Component::Type::Mesh:
		comp = new ComponentMesh(this); 
		break; 
	case Component::Type::Texture:
		comp = new ComponentTexture(this); 
		break; 
	case Component::Type::Transform:
		comp = new ComponentTransform(this); 
		break; 
	}

	components.push_back(comp); 

	return comp; 
}

void GameObject::Update()
{
}
