#include "ComponentUI.h"

ComponentUI::ComponentUI(GameObject* GO, Type comp_type, uint h, uint w):Component(GO, comp_type)
{
	this->type = type; 
	height = h; 
	width = w; 
}

ComponentUI::~ComponentUI()
{

};
