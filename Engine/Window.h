#pragma once

#include "Globals.h"

class Window
{
public:

	Window(); 
	virtual ~Window(); 

	virtual bool Start(); 
	virtual bool Draw(); 
	virtual bool CleanUp(); 
};
