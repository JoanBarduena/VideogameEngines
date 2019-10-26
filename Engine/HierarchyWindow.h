#pragma once
#include "Module.h"
#include "Window.h"

class HierarchyWindow : public Window
{
public:

	HierarchyWindow(); 
	~HierarchyWindow(); 

	bool Start(); 
	bool Draw(); 
	bool CleanUp(); 
};