#include "Component.h"
#include "mmgr/mmgr.h"

Component::Component(GameObject * my_GO, Component::Type comp_type)
{
	my_go = my_GO; 
	this->type = comp_type;
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

bool Component::CleanUp()
{
	return true;
}

