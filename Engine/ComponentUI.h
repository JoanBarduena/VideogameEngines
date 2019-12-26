#ifndef __COMPONENTUI_H__
#define __COMPONENTUI_H__

#include "Component.h"

class ComponentUI : public Component
{
	enum class TypeUI
	{
		UI_Canvas,
		UI_Image,
		UI_Button,
		UI_Label,
		UI_Checkbox,
		UI_InputText
	};

public:
	ComponentUI(GameObject* GO, Type comp_type, uint h, uint w);
	~ComponentUI();

	virtual void SceneDraw() {};
	virtual void DebugDraw() {}; 

private: 

	uint height = 0, width = 0; 

};


#endif // !__COMPONENTUI_H__