#pragma once

#include "Component.h"
#include "ModuleTexture.h"

class ComponentTexture : public Component
{
public:

	ComponentTexture(GameObject* GObj);
	~ComponentTexture(); 

	TextureStruct* texture; 
};