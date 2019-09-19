#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleTextures.h"
#include "Box2D/Box2D/Box2D.h"
#include <string>
#include "Animation.h"

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	//Functions
	bool Start();
	update_status Update();
	bool CleanUp();
	void Ball(); 
	void Teleported_Ball(); 
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB); 
	void LoadKickers(); 
	void Launcher(); 

public:
	//Textures
	SDL_Texture* kickers_tx;
	SDL_Texture* ball_tx; 
	SDL_Texture* launcher_tx; 
	SDL_Texture* ball_lost_tx; 

	//Player attributes
	uint tries = 5;

	//Kicker right
	PhysBody* kicker_left;
	PhysBody* pivot_left;
	b2RevoluteJoint* joint_left;

	//Kicker left 
	PhysBody* kicker_right;
	PhysBody* pivot_right;
	b2RevoluteJoint* joint_right;

	//Sensors
	PhysBody* dead_sensor; 
	PhysBody* lock_sensor;
	PhysBody* teleport_sensor;
	
	//bools
	bool is_dead = false; 
	bool is_teleported = false; 

private:

	//Animations 
	Animation launcher_animation_static;
	Animation launching_animation;
	Animation* current_animation = nullptr;

	Animation ball_lost_anim;  
	Animation ball_lost_idle; 
	Animation* ball_animation = nullptr; 
	int ball_counter = 0; 

	PhysBody* ball; 

	PhysBody* launcher;
	PhysBody* launcher_pivot;
	b2PrismaticJoint* jointLauncher;

	//sfx
	uint kicker_fx;
	uint combo_fx;

};