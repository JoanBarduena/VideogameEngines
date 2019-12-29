#include "GameObject.h"
#include "Application.h"

#include "mmgr/mmgr.h"

GameObject::GameObject(string name_)
{
	this->active = true; 
	this->name = name_; 
	CreateComponent(Component::Type::TRANSFORM);
	this->go_static = false; 
}

GameObject::~GameObject()
{
}

bool GameObject::CleanUp()
{
	//Clear GameObjects
	for (std::vector<Component*>::iterator it = components.begin(); it != components.end(); it++)
	{
		(*it)->CleanUp(); 
		delete(*it); 
		(*it) = nullptr; 
	}
	
	for (std::vector<GameObject*>::iterator it = childs.begin(); it != childs.end(); it++)
	{
		(*it)->CleanUp();
		delete(*it); 
		(*it) = nullptr;
	}

	components.clear(); 

	return true; 
}

Component* GameObject::CreateComponent(Component::Type type)
{
	Component* comp = nullptr; 

	switch (type)
	{
	case Component::Type::MESH:
		comp = new ComponentMesh(this); 
		break; 
	case Component::Type::TEXTURE:
		comp = new ComponentTexture(this); 
		break; 
	case Component::Type::TRANSFORM:
		comp = new ComponentTransform(this); 
		break; 
	case Component::Type::CANVAS:
		comp = new ComponentCanvas(this, 30, 60); 
		break; 
	case Component::Type::IMAGE:
		comp = new ComponentImage(this); 
		break; 
	case Component::Type::BUTTON:
		comp = new ComponentButton(this, "Assets/ButtonUI.png"); 
	}
	if(comp != nullptr)
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

bool GameObject::HasChildren() const
{
	if (childs.empty())
		return false;
	else
		return true;
}

bool GameObject::Update(float dt)
{
	if (this->GetComponentTransform()->is_transformed)
		UpdateTransformation(this);

	for (std::vector<GameObject*>::iterator it = childs.begin(); it != childs.end(); it++)
	{
		if ((*it)->active)
			(*it)->Update(dt);
	}

	for (std::vector<Component*>::iterator it = components.begin(); it != components.end(); it++)
	{
		if ((*it)->active)
			(*it)->Update();
	}

	return true; 
}

void GameObject::UpdateTransformation(GameObject* GO)
{
	ComponentTransform* transform = GO->GetComponentTransform(); 

	transform->UpdateTransformInGame(GO->parent->GetComponentTransform()->GetGlobalTransform());

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
	go = nullptr; 
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

// --------------------- GETTERS() -----------------------------

ComponentTransform* GameObject::GetComponentTransform()
{
	for (std::vector<Component*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		if ((*it)->type == Component::Type::TRANSFORM)
			return (ComponentTransform*)(*it); 
	}

	return nullptr; 
}

ComponentMesh* GameObject::GetComponentMesh()
{
	for (std::vector<Component*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		if ((*it)->type == Component::Type::MESH)
			return (ComponentMesh*)(*it);
	}

	return nullptr; 
}

ComponentTexture* GameObject::GetComponentTexture()
{
	for (std::vector<Component*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		if ((*it)->type == Component::Type::TEXTURE)
			return (ComponentTexture*)(*it);
	}

	return nullptr;
}

ComponentCanvas* GameObject::GetComponentCanvas()
{
	for (std::vector<Component*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		if ((*it)->type == Component::Type::CANVAS)
			return (ComponentCanvas*)(*it);
	}

	return nullptr;
}

ComponentImage* GameObject::GetComponentImage()
{
	for (std::vector<Component*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		if ((*it)->type == Component::Type::IMAGE)
			return (ComponentImage*)(*it);
	}

	return nullptr;
}

ComponentButton* GameObject::GetComponentButton()
{
	for (std::vector<Component*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		if ((*it)->type == Component::Type::BUTTON)
			return (ComponentButton*)(*it);
	}

	return nullptr;
}
