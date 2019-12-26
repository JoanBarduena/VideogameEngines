#include "ComponentUI.h"

ComponentUI::ComponentUI(GameObject* GO, TypeUI typeUI, uint h, uint w)
{
	go_ui = GO; 
	this->type_UI = typeUI; 
}

ComponentUI::~ComponentUI()
{
};