#pragma once
#include "Window.h"
#include "Console.h"

class ConsoleWindow : public Window
{
public:

	ConsoleWindow(); 
	~ConsoleWindow(); 

	bool Start(); 
	bool Draw(); 
	bool CleanUp(); 

	Console gui_console;

};
