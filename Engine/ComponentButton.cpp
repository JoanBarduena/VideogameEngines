#include "ComponentButton.h"
#include "Application.h"

ComponentButton::ComponentButton(GameObject* GO, const char* path) : Component(GO, Type::BUTTON)
{
	my_go->GetComponentTexture()->texture = App->Mtexture->LoadTexturePath(path);
}

ComponentButton::~ComponentButton()
{
}

bool ComponentButton::Update()
{
	return false;
}