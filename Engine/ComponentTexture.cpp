#include "ComponentTexture.h"
#include "Application.h"

#include "mmgr/mmgr.h"

ComponentTexture::ComponentTexture(GameObject * GObj) : Component(GObj, Type::Texture)
{
	this->texture = App->texture->DefaultTexture; 
}

ComponentTexture::~ComponentTexture()
{
}

void ComponentTexture::CleanUp()
{
	if (texture != nullptr)
	{
		RELEASE(texture); 
	}
}
