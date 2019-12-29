#ifndef __COMPONENT_CANVAS_H__
#define __COMPONENT_CANVAS_H__

#include "Component.h"
#include "MathGeoLib/include/MathGeoLib.h"

class ComponentCanvas : public Component
{
public: 

	ComponentCanvas(GameObject* GO, uint h, uint w);
	~ComponentCanvas();

	bool Update(); 

	void SceneDraw(); 

public:

	float3 pos; 
};

#endif
