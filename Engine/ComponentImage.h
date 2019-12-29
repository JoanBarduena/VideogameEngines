#ifndef __COMPONENT_IMAGE_H__
#define __COMPONENT_IMAGE_H__

#include "Component.h"

class ComponentImage : public Component
{
public:

	ComponentImage(GameObject* GO);
	~ComponentImage();

	bool Update();


public:

	GameObject* parent = nullptr; 
};

#endif
