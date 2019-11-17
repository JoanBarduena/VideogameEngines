#include "ComponentTexture.h"
#include "Application.h"

ComponentTexture::ComponentTexture(GameObject * GObj) : Component(GObj, Type::Texture)
{
	//this->texture = App->texture->DefaultTexture; 
}

ComponentTexture::~ComponentTexture()
{
}
