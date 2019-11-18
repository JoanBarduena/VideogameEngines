#include "GameObject.h"

GameObject::GameObject(string name_)
{
	this->name = name_; 
	this->active = true; 
	mesh = (ComponentMesh*)CreateComponent(Component::Type::Mesh); 
	texture = (ComponentTexture*)CreateComponent(Component::Type::Texture);
	transform = (ComponentTransform*)CreateComponent(Component::Type::Transform);

}

GameObject::~GameObject()
{
	//Clean components
	for (vector<Component*>::iterator i = components.begin(); i != components.end(); ++i)
	{
		RELEASE(*i); 
	}
	components.clear(); 

	//Clean childs
	for (list<GameObject*>::iterator i = childs.begin(); i != childs.end(); ++i)
	{
		RELEASE(*i);
	}
	childs.clear(); 
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

void GameObject::DefineChilds(GameObject* GO)
{
	if (GO->parent != nullptr)
		GO->parent->childs.remove(GO); 

	GO->parent = this;
	childs.push_back(GO);
}

void GameObject::Update(float dt)
{
	if (this->transform->is_transformed)
		UpdateTransformation(this);

	for (std::list<GameObject*>::iterator it = childs.begin(); it != childs.end(); it++)
	{
		if ((*it)->active)
			(*it)->Update(dt);
	}
}

void GameObject::UpdateTransformation(GameObject* GO)
{
	ComponentTransform* transform = GO->transform;
	transform->UpdateTransformInGame(GO->parent->transform->GetGlobalTransform());

	for (std::list<GameObject*>::iterator it = GO->childs.begin(); it != GO->childs.end(); ++it)
	{
		UpdateTransformation(*it);
	}
}
