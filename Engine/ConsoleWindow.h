#pragma once
#include "Window.h"
//#include "Console.h"

class ConsoleWindow : public Window
{
public:

	ConsoleWindow(); 
	~ConsoleWindow(); 

	bool Start(); 
	bool Draw(); 
	bool CleanUp(); 

	bool AutoScroll;
	bool ScrollToBottom;

	//Console gui_console;

};
