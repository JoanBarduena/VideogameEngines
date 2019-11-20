#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "Globals.h"

#include "imGui/imgui.h"
#include "imGui/imgui_impl_sdl.h"
#include "imGui/imgui_impl_opengl3.h"

class Window
{
public:

	Window();
	virtual ~Window();

	virtual bool Start();
	virtual bool Draw();
	virtual bool CleanUp(); 
};

#endif // !__WINDOW_H__