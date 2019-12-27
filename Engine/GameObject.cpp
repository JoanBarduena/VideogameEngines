#include "GameObject.h"
#include "Application.h"

#include "mmgr/mmgr.h"

GameObject::GameObject(string name_)
{
	this->active = true; 
	this->name = name_; 
	CreateComponent(Component::Type::Transform);
	this->go_static = false; 
}

GameObject::~GameObject()
{
}

void GameObject::CleanUp()
{
	if (this->GetComponentMesh() != nullptr)
	{
		this->GetComponentMesh()->CleanUp(); 
	}

	//Clear GameObjects
	for (std::vector<Component*>::iterator it = components.begin(); it != components.end(); it++)
	{
		delete(*it); 
	}
	
	for (std::vector<GameObject*>::iterator it = childs.begin(); it != childs.end(); it++)
	{
		(*it)->CleanUp();
	}

	components.clear();

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

ComponentUI* GameObject::CreateComponentUI(ComponentUI::TypeUI typeUI)
{
	ComponentUI* comp_UI = nullptr; 

	switch (typeUI)
	{
	case ComponentUI::TypeUI::UI_Canvas:
		comp_UI = new ComponentCanvas(this, 50, 40); 
		break; 
	}
	if (comp_UI != nullptr)
	{
		componentsUI.push_back(comp_UI); 
	}

	return comp_UI; 
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

void GameObject::Update(float dt)
{
	if (this->GetComponentTransform()->is_transformed)
		UpdateTransformation(this);

	for (std::vector<GameObject*>::iterator it = childs.begin(); it != childs.end(); it++)
	{
		if ((*it)->active)
			(*it)->Update(dt);
	}

	for (std::vector<ComponentUI*>::iterator it = componentsUI.begin(); it != componentsUI.end(); it++)
	{
		if ((*it)->active)
			(*it)->Update();
	}
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
		if ((*it)->type == Component::Type::Transform)
			return (ComponentTransform*)(*it); 
	}

	return nullptr; 
}

ComponentMesh* GameObject::GetComponentMesh()
{
	for (std::vector<Component*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		if ((*it)->type == Component::Type::Mesh)
			return (ComponentMesh*)(*it);
	}

	return nullptr; 
}

ComponentTexture* GameObject::GetComponentTexture()
{
	for (std::vector<Component*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		if ((*it)->type == Component::Type::Texture)
			return (ComponentTexture*)(*it);
	}

	return nullptr;
}
