#ifndef __COMPONENT_BUTTON_H__
#define __COMPONENT_BUTTON_H__

#include "Component.h"

class ComponentButton : public Component
{
public:

	ComponentButton(GameObject* GO, const char* path);
	~ComponentButton();

	bool Update();

public:

	GameObject* parent = nullptr;
};

#endif
