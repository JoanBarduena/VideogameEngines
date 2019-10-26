#pragma once
#include "Window.h"

class ConfigurationWindow : public Window
{
public: 

	ConfigurationWindow(); 
	~ConfigurationWindow(); 

	bool Start(); 
	bool CleanUp(); 
};
