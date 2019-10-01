#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "Module.h"
#include "SDL/include/SDL.h"

class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow(Application* app, bool start_enabled = true);

	// Destructor
	virtual ~ModuleWindow();

	bool Init();
	bool CleanUp();

	void SetTitle(const char* title);
	
	void SetFullscreen(bool fs); 
	void SetBorderless(bool bl); 
	void SetFullscreenDesktop(bool fsd); 
	void SetResizable(bool rz);
	void SetBrightness(float b); 

	void SetWindowSize(int w, int h);

	bool fullscreen = false; 
	bool borderless = false; 
	bool fullscreendesktop = false; 
	bool resizable = false; 

	float brightness = 1.0f; 
	int width = SCREEN_WIDTH;
	int height = SCREEN_HEIGHT;

public:
	//The window we'll be rendering to
	SDL_Window* window;

	//The surface contained by the window
	SDL_Surface* screen_surface;
};

#endif // __ModuleWindow_H__