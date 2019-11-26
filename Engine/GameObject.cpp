#include "GameObject.h"
#include "Application.h"

#include "mmgr/mmgr.h"

GameObject::GameObject(string name_)
{
	this->name = name_; 
	this->active = true; 
	transform = (ComponentTransform*)CreateComponent(Component::Type::Transform);
	mesh = (ComponentMesh*)CreateComponent(Component::Type::Mesh); 
	Ctexture = (ComponentTexture*)CreateComponent(Component::Type::Texture);
	this->go_static = true; 
}

GameObject::~GameObject()
{
}

void GameObject::CleanUp()
{
	if (this->mesh != nullptr)
	{
		this->mesh->CleanUp(); 
	}

	//Clear GameObjects
	for (std::vector<Component*>::iterator it = components.begin(); it != components.end(); it++)
	{
		delete(*it); 
	}
	components.clear(); 

	for (std::vector<GameObject*>::iterator it = childs.begin(); it != childs.end(); it++)
	{
		(*it)->CleanUp();
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
			{
				GO->parent->childs.erase(it);
				break;
			}
				
		}
	}

	GO->parent = this;
	childs.push_back(GO);
}

void GameObject::Update(float dt)
{
	if (this->transform->is_transformed)
		UpdateTransformation(this);

	for (std::vector<GameObject*>::iterator it = childs.begin(); it != childs.end(); it++)
	{
		if ((*it)->active)
			(*it)->Update(dt);
	}
}

void GameObject::UpdateTransformation(GameObject* GO)
{
	GO->transform->UpdateTransformInGame(GO->parent->transform->GetGlobalTransform());

	for (std::vector<GameObject*>::iterator it = GO->childs.begin(); it != GO->childs.end(); ++it)
	{
		UpdateTransformation(*it);
	}
}

void GameObject::DeleteGO(GameObject* go, bool original)
{
	if (go->childs.size() > 0)
	{
		for (std::vector<GameObject*>::iterator it = go->childs.begin(); it != go->childs.end(); ++it)
		{
			DeleteGO(*it, false);
		}

		go->childs.clear();
	}

	if (go->parent != nullptr && original == true)
		go->parent->RemoveChild(go);

	go->CleanUp();
	delete go;
}

void GameObject::RemoveChild(GameObject* go)
{
	for (std::vector<GameObject*>::iterator it = childs.begin(); it != childs.end(); it++)
	{
		if ((*it)->id == go->id)
		{
			childs.erase(it);
			break;
		}
	}
}