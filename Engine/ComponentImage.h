#ifndef __COMPONENT_IMAGE_H__
#define __COMPONENT_IMAGE_H__

#include "ComponentUI.h"

class ComponentImage : public Component
{
public:

	ComponentImage(GameObject* GO);
	~ComponentImage();

	bool Update();

	void SceneDraw();

public:

	GameObject* parent = nullptr; 
};

#endif
