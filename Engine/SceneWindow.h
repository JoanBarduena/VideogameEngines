#pragma once
#include "Window.h"

class SceneWindow : public Window
{
public:
	SceneWindow();
	~SceneWindow();

	bool Start();
	bool Draw();
	bool CleanUp();
};

