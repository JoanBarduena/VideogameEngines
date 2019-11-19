#include "Component.h"
#include "mmgr/mmgr.h"

Component::Component(GameObject * my_GO, Component::Type type_)
{
	my_go = my_GO; 
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

