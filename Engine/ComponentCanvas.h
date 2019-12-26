#ifndef __COMPONENT_CANVAS_H__
#define __COMPONENT_CANVAS_H__

#include "ComponentUI.h"

class ComponentCanvas : public ComponentUI
{
public: 

	ComponentCanvas(GameObject* GO, TypeUI UI_type, uint h, uint w);
	~ComponentCanvas();

	void SceneDraw(); 

protected: 
	
	uint height = 0, width = 0; 
};



#endif
