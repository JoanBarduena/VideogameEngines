#pragma once

// Warning disabled ---
#pragma warning( disable : 4577 ) // Warning that exceptions are disabled
#pragma warning( disable : 4530 )

#include <windows.h>
#include <stdio.h>
#include <vector>
#include <list>
#include <string>

using namespace std; 

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);
void log(const char file[], int line, const char* format, ...);
#define CAP(n) ((n <= 0.0f) ? n=0.0f : (n >= 1.0f) ? n=1.0f : n=n);

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#define HAVE_M_PI

// Deletes a buffer
#define RELEASE( x ) \
    {                        \
    if( x != NULL )        \
	    {                      \
      delete x;            \
	  x = NULL;              \
	    }                      \
    }

// Deletes an array of buffers
#define RELEASE_ARRAY( x ) \
    {                              \
    if( x != NULL )              \
	    {                            \
      delete[] x;                \
	  x = NULL;                    \
	    }                            \
                              \
    }

typedef unsigned int uint;

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

// Configuration -----------
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 1024
#define SCREEN_SIZE 1
#define WIN_FULLSCREEN false
#define WIN_RESIZABLE false
#define WIN_BORDERLESS false
#define WIN_FULLSCREEN_DESKTOP true
#define VSYNC true
#define TITLE "Videogame Engine"
#define ORGANIZATION "UPC"
#define MEMORY_LOG_SIZE 100
#define FPS_LOG_SIZE 100

// Checkers Texture --------
#define CHECKERS_HEIGHT 128
#define CHECKERS_WIDTH 128

// Folders -----------------
#define ASSETS_FOLDER "/Assets/"
#define SETTINGS_FOLDER "/Settings/"
#define LIBRARY_FOLDER "/Library/"
#define LIBRARY_AUDIO_FOLDER "/Library/Audio/"
#define LIBRARY_TEXTURES_FOLDER "/Library/Textures/"
#define LIBRARY_MESH_FOLDER "/Library/Meshes/"
#define LIBRARY_ANIMATION_FOLDER "/Library/Animations/"
#define LIBRARY_SCENE_FOLDER "/Library/Scenes/"
#define LIBRARY_MODEL_FOLDER "/Library/Models/"
#define LIBRARY_MATERIAL_FOLDER "/Library/Materials/"
#define LIBRARY_STATE_MACHINE_FOLDER "/Library/StateMachines/"

