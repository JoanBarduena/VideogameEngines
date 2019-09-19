#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
#include "Animation.h"
#include "ModuleAudio.h"

class PhysBody;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();
	//void OnCollision(PhysBody* bodyA, PhysBody* bodyB);
	void DrawColliders();
	void DrawLights();
	void IncreaseScore(int points);

public:

	p2List<PhysBody*> circles;
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> ricks;

	//Collider Bodies
	PhysBody* map_;
	PhysBody* top_left_1; 
	PhysBody* top_left_2;
	PhysBody* top_left_3; 
	PhysBody* middle_top_1; 
	PhysBody* middle_top_2; 
	PhysBody* middle_;
	PhysBody* top_right_1;
	PhysBody* bottom_right_1; 
	PhysBody* bottom_right_2; 
	PhysBody* bottom_left_1; 
	PhysBody* bottom_left_2; 
	PhysBody* football_1; 
	PhysBody* football_2; 
	PhysBody* football_3; 
	PhysBody* football_4; 
	PhysBody* ball_corridor_1; 
	PhysBody* ball_corridor_2; 

	SDL_Texture* ball;
	SDL_Texture* box;
	SDL_Texture* rick;
	SDL_Texture* map; 
	uint bonus_fx;

	//Score system
	int score;				//score
	int font_score=-1;		//Load the score here
	char score_text[13];
	int combo;				//This will multiply the points income

	//Light Animations
	SDL_Texture* lights_texture;
	Animation middle_lights;
	Animation left_lights;
	Animation top_left_lights;
	Animation right_lights;
	Animation top_right_lights;

	//Music
	Mix_Music* music;

private:
	bool debug = false;

};
