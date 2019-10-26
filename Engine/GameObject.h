#pragma once

#include "Globals.h"

struct Position {
	float x, y, z; 
};

class GameObject
{
public: 

	std::string name; 
	Position position;
	uint Texture; 

	//std::vector<GameObject*> game_objects; 
};


