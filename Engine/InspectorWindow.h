#pragma once
#include "Module.h"
#include "Window.h"

class InspectorWindow : public Window
{
public:

	InspectorWindow(); 
	~InspectorWindow(); 

	bool Start(); 
	bool Draw(); 
	bool CleanUp(); 

	//GameObject* GO_Inspector = nullptr;
};
