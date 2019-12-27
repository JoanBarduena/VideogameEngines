#ifndef __COMPONENT_IMAGE_H__
#define __COMPONENT_IMAGE_H__

#include "ComponentUI.h"

class ComponentImage : public ComponentUI
{
public:

	ComponentImage(GameObject* GO, uint h, uint w, const char* path);
	~ComponentImage();

	bool Update();

	void SceneDraw();

public:

	uint height = 0, width = 0;
};

#endif
