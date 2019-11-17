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
	if (GO == parent)
		return;

	if (parent)
		parent->childs.remove(this); 

	parent = GO; 
	if(GO)
		GO->childs.push_back(this); 
}

void GameObject::Update()
{
}

void GameObject::UpdateTransformation(GameObject* GO)
{
	ComponentTransform* transform = GO->transform;
	transform->UpdateTransformInGame(GO->transform->GetGlobalTransform());
}
