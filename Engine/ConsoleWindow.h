#pragma once
#include "Window.h"

class ConsoleWindow : public Window
{
public:

	ConsoleWindow(); 
	~ConsoleWindow(); 

	bool Start(); 
	bool Draw(); 
	bool CleanUp(); 

};
