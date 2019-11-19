#include "GameObject.h"
#include "Application.h"

#include "mmgr/mmgr.h"

GameObject::GameObject(string name_)
{
	this->name = name_; 
	this->active = true; 
	c_transform = (ComponentTransform*)CreateComponent(Component::Type::Transform);
	mesh = (ComponentMesh*)CreateComponent(Component::Type::Mesh); 
	texture = (ComponentTexture*)CreateComponent(Component::Type::Texture);
}

GameObject::~GameObject()
{
}

void GameObject::CleanUp()
{
	//Clean components
	if (this->mesh != nullptr)
	{
		this->mesh->CleanUp();
	}

	for (vector<Component*>::iterator i = components.begin(); i != components.end(); i++)
	{
		if ((*i) != nullptr)
		{
			delete(*i);
			//(*i) = nullptr;
		}
	}
	components.clear();

	if (childs.size() > 0)
	{
		for (vector<GameObject*>::iterator i = childs.begin(); i != childs.end(); i++)
		{
			(*i)->CleanUp();

		}
	}


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
	if(comp != nullptr )
		components.push_back(comp); 

	return comp; 
}

void GameObject::DefineChilds(GameObject* GO)
{
	if (GO->parent != nullptr)
	{
		for (std::vector<GameObject*>::iterator it = GO->parent->childs.begin(); it != GO->parent->childs.end(); it++)
		{
			if ((*it)->id == GO->id)
				GO->parent->childs.erase(it); 
		}
	}

	GO->parent = this;
	childs.push_back(GO);
}

void GameObject::RemoveGameObject()
{
	for (std::vector<GameObject*>::iterator it = App->scene_intro->game_objects.begin(); it != App->scene_intro->game_objects.end(); it++)
	{
		delete(*it); 
		(*it) = nullptr; 
	}
}

void GameObject::Update(float dt)
{
	if (this->c_transform->is_transformed)
		UpdateTransformation(this);

	for (std::vector<GameObject*>::iterator it = childs.begin(); it != childs.end(); it++)
	{
		if ((*it)->active)
			(*it)->Update(dt);
	}
}

void GameObject::UpdateTransformation(GameObject* GO)
{
	ComponentTransform* transform = GO->c_transform;
	transform->UpdateTransformInGame(GO->parent->c_transform->GetGlobalTransform());

	for (std::vector<GameObject*>::iterator it = GO->childs.begin(); it != GO->childs.end(); ++it)
	{
		UpdateTransformation(*it);
	}
}
