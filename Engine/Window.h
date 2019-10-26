#ifndef __WINDOW_H__
#define __WINDOW_H__

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

#endif // !__WINDOW_H__