#include "ComponentTexture.h"
#include "Application.h"

#include "mmgr/mmgr.h"

ComponentTexture::ComponentTexture(GameObject * GObj) : Component(GObj, Type::TEXTURE)
{
	this->texture = App->Mtexture->DefaultTexture;
}

ComponentTexture::~ComponentTexture()
{
}

void ComponentTexture::CleanUp()
{
}
