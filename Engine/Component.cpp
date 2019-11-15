#include "Component.h"

Component::Component(GameObject * my_GO, Component::Type type_)
{
	this->my_go = my_GO; 
	this->type = type_; 
}

Component::~Component()
{
}

bool Component::Enable()
{
	return true;
}

bool Component::Update()
{
	return true;
}

bool Component::Disable()
{
	return true;
}
