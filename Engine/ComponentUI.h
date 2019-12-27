#ifndef __COMPONENTUI_H__
#define __COMPONENTUI_H__

#include "Globals.h"

class GameObject;

class ComponentUI 
{
public:
	enum class TypeUI
	{
		UI_Canvas,
		UI_Image,
		UI_Button,
		UI_Label,
		UI_Checkbox,
		UI_InputText
	};


	ComponentUI(GameObject* GO, TypeUI typeUI, uint h, uint w);
	~ComponentUI();

	virtual void SceneDraw() {};
	virtual void DebugDraw() {}; 

	virtual bool Update() { return true; };

	virtual void RotateV4() {};

	bool active;

protected: 

	ComponentUI::TypeUI type_UI;
	uint height = 0, width = 0; 
	GameObject* go_ui = nullptr; 
	
};


#endif // !__COMPONENTUI_H__