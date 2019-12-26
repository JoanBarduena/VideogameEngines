#ifndef __COMPONENT_CANVAS_H__
#define __COMPONENT_CANVAS_H__

#include "ComponentUI.h"

class ComponentCanvas : public ComponentUI
{
public: 

	ComponentCanvas(GameObject* GO, uint h, uint w);
	~ComponentCanvas();

	bool Update(); 

	void SceneDraw(); 

protected: 
	
	uint height = 0, width = 0; 
};



#endif
