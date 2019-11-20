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

	void TreeNodeHierarchy(GameObject* go);

	bool starts_clicked = true;

	uint node_clicked = -1;
};