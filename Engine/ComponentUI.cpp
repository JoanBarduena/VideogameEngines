#include "ComponentUI.h"

ComponentUI::ComponentUI(GameObject* GO, TypeUI UI_type, uint h, uint w):Component(GO, Component::Type::Canvas)
{
	this->type = type; 
	height = h; 
	width = w; 
}

ComponentUI::~ComponentUI()
{
};
