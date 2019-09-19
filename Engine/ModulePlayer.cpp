#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleWindow.h"
#include "ModuleSceneIntro.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	ball_tx = kickers_tx = launcher_tx = NULL;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	//Load textures
	kickers_tx = App->textures->Load("Images/kicker.png");
	ball_tx = App->textures->Load("Images/redball.png");
	launcher_tx = App->textures->Load("Images/LauncherAnimation.png"); 
	ball_lost_tx = App->textures->Load("Images/BallLost.png"); 

	//Load audio
	kicker_fx = App->audio->LoadFx("Audio/kicker.wav"); 
	combo_fx = App->audio->LoadFx("Audio/Combo.wav");

	//Load sensor
	dead_sensor = App->physics->CreateRectangleSensor(243, 550, 80, 20, b2_staticBody); 
	lock_sensor = App->physics->CreateRectangleSensor(390, 255, 25, 25, b2_staticBody); 
	teleport_sensor = App->physics->CreateRectangleSensor(242, 325, 36, 8, b2_staticBody);

	//Ball Lost Pushback
	ball_lost_anim.PushBack({ 0,9,58,8 });
	ball_lost_anim.loop = false;
	ball_lost_anim.speed = 1.0f;

	ball_lost_idle.PushBack({ 0,0,58,8 });
	ball_lost_idle.loop = false;
	ball_lost_idle.speed = 1.0f;

	ball_animation = &ball_lost_idle; 

	//Load functions
	LoadKickers(); 
	Launcher(); 
	Ball(); 
	
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");
	App->textures->Unload(kickers_tx);
	App->textures->Unload(ball_tx); 
	App->textures->Unload(launcher_tx); 
	App->textures->Unload(ball_lost_tx); 

	return true;
}

void ModulePlayer::Ball()
{
	if (tries > 0)
	{
		ball = App->physics->CreateCircle(455, 350, 9, b2_dynamicBody);
		ball->listener = this;
	}
}

void ModulePlayer::Teleported_Ball()
{
	ball = App->physics->CreateCircle(235, 85, 9, b2_dynamicBody);
	ball->listener = this;
	ball_counter = 0; 
}

void ModulePlayer::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	if (bodyB == dead_sensor && bodyA==ball )
	{
		ball_animation = &ball_lost_anim;
		ball_counter = 0; 
		is_dead = true; 
		tries -= 1; 
		App->scene_intro->combo = 1;		//Reset the combo
	}

	else {
		App->scene_intro->IncreaseScore(1);

		if (bodyA == App->scene_intro->football_1 ||
			bodyA == App->scene_intro->football_2 ||
			bodyA == App->scene_intro->football_3 ||
			bodyB == App->scene_intro->football_1 ||
			bodyB == App->scene_intro->football_2 ||
			bodyB == App->scene_intro->football_3) {

			App->scene_intro->combo += 10;
			App->audio->PlayFx(combo_fx);
		}

	}
	
	if (bodyB == lock_sensor)
	{
		ball->body->SetAwake(false); 
	}

	if (bodyB == teleport_sensor)
	{
		is_teleported = true; 
	}
}

// Update: draw background
update_status ModulePlayer::Update()
{
	// KICKERS INPUTS
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
	{
		joint_left->EnableMotor(true);
		App->audio->PlayFx(kicker_fx); 
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
	{
		joint_left->EnableMotor(false);
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		joint_right->EnableMotor(true);
		App->audio->PlayFx(kicker_fx);

	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
	{
		joint_right->EnableMotor(false);
	}

	//RESET GAME
	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
	{
		LOG("Reset lives");
		if (tries > 0) App->physics->world->DestroyBody(ball->body);

		tries = 5;
		Ball();

		App->scene_intro->score = 0;
	}


	int x, y;

	//LEFT KICKER
	kicker_left->GetPosition(x, y);
	App->renderer->Blit(kickers_tx, x, y, NULL, 1.0f, kicker_left->GetRotation());

	//RIGHT KICKER
	kicker_right->GetPosition(x, y);
	App->renderer->Blit(kickers_tx, x, y, NULL, 1.0f, kicker_right->GetRotation() + 180);

	//-------------------------------------------------------------------------------------

	//LAUNCHER INPUTS 
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN)
	{
		jointLauncher->EnableMotor(true);
		current_animation = &launching_animation;
		App->audio->PlayFx(kicker_fx);
	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
	{
		jointLauncher->EnableMotor(false);
		current_animation = &launcher_animation_static; 
		
	}
	App->renderer->Blit(launcher_tx, 417, 433, &(current_animation->GetCurrentFrame()));

	// Ball texture setting
	ball->GetPosition(x, y);
	App->renderer->Blit(ball_tx, x, y, NULL, 1.0f, ball->GetRotation());

	//Ball LOST animation idle
	ball_counter++; 
	if (ball_counter > 100) ball_animation = &ball_lost_idle; 

	//Lock timer
	if (ball_counter > 400)  ball->body->SetAwake(true); 

	//Destroy ball
	if (is_dead)
	{
		App->physics->world->DestroyBody(ball->body);
		Ball();
		is_dead = false;
	}

	if (is_teleported)
	{
		App->physics->world->DestroyBody(ball->body);
		Teleported_Ball(); 
		is_teleported = false; 
	}

	//Ball LOST blit
	App->renderer->Blit(ball_lost_tx, 215, 555, &(ball_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}

void ModulePlayer::LoadKickers()
{
	// LEFT KICKER	
	b2RevoluteJointDef revoluteJointDef;

	kicker_left = App->physics->CreateRectangle(174, 492, 58, 13, 20 * DEGTORAD, b2_dynamicBody);
	pivot_left = App->physics->CreateCircle(174, 492, 6, b2_staticBody);
	kicker_left->body->SetGravityScale(30.0f);

	revoluteJointDef.bodyA = kicker_left->body;
	revoluteJointDef.bodyB = pivot_left->body;

	revoluteJointDef.localAnchorA.Set(PIXEL_TO_METERS(-30), 0);		// PIVOT POINT OF THE RECTANGLE ON THE CENTER OF THE CIRCLE
	revoluteJointDef.localAnchorB.Set(0, 0);						// PIVOT POINT OF THE CIRCLE ON ITS CENTER
	revoluteJointDef.collideConnected = false;

	//ANGLE LIMITS
	revoluteJointDef.upperAngle = 32 * DEGTORAD;		
	revoluteJointDef.lowerAngle = -32 * DEGTORAD;
	revoluteJointDef.enableLimit = true;

	//MOTOR SPEED AND TORQUE 
	revoluteJointDef.motorSpeed = 600.0f * DEGTORAD;		
	revoluteJointDef.maxMotorTorque = 600;
	revoluteJointDef.enableMotor = false;

	joint_left = (b2RevoluteJoint*)App->physics->world->CreateJoint(&revoluteJointDef);

	// RIGHT KICKER
	kicker_right = App->physics->CreateRectangle(308, 492, 58, 13, -20 * DEGTORAD, b2_dynamicBody); //RECTANGLE COORDENATES
	pivot_right = App->physics->CreateCircle(308, 492, 6, b2_staticBody); //CIRCLE COORDENATES
	kicker_right->body->SetGravityScale(30.0f);

	revoluteJointDef.bodyA = kicker_right->body;
	revoluteJointDef.bodyB = pivot_right->body;

	revoluteJointDef.localAnchorA.Set(PIXEL_TO_METERS(30), 0);		// PIVOT POINT OF THE RECTANGLE ON THE CENTER OF THE CIRCLE
	revoluteJointDef.localAnchorB.Set(0, 0);						// PIVOT POINT OF THE CIRCLE ON ITS CENTER
	revoluteJointDef.collideConnected = false;
	revoluteJointDef.referenceAngle = 0;

	//ANGLE LIMITS
	revoluteJointDef.upperAngle = 32 * DEGTORAD;		
	revoluteJointDef.lowerAngle = -32 * DEGTORAD;
	revoluteJointDef.enableLimit = true;

	//MOTOR SPEED AND TORQUE
	revoluteJointDef.motorSpeed = -600.0f * DEGTORAD;
	revoluteJointDef.maxMotorTorque = 600;
	revoluteJointDef.enableMotor = false;

	joint_right = (b2RevoluteJoint*)App->physics->world->CreateJoint(&revoluteJointDef);
}


void ModulePlayer::Launcher()
{
	b2RevoluteJointDef revoluteJointDef;

	//LAUNCHER POSITIONS OF PUSHING RECTANGLE AND STATIC RECTANGLE
	launcher = App->physics->CreateRectangle(429, 508, 15, 80, 0, b2_dynamicBody);
	launcher_pivot = App->physics->CreateRectangle(429, 508, 15, 20, 0, b2_staticBody);

	b2PrismaticJointDef prismaticJointDef;

	prismaticJointDef.bodyA = launcher->body;
	prismaticJointDef.bodyB = launcher_pivot->body;

	prismaticJointDef.localAnchorA.Set(0, 0);
	prismaticJointDef.localAnchorB.Set(0, 0);
	prismaticJointDef.collideConnected = false;

	prismaticJointDef.localAxisA.Set(0, 1);

	prismaticJointDef.enableLimit = true;
	prismaticJointDef.lowerTranslation = 0;
	prismaticJointDef.upperTranslation = PIXEL_TO_METERS(50);

	prismaticJointDef.enableMotor = false;
	prismaticJointDef.maxMotorForce = 400;
	prismaticJointDef.motorSpeed = 200.0f;

	jointLauncher = (b2PrismaticJoint*)App->physics->world->CreateJoint(&prismaticJointDef);

	//ANIMATIONS
	launcher_animation_static.PushBack({ 166, 0, 58, 124 });
	launcher_animation_static.loop = false;
	launcher_animation_static.speed = 1.0f;

	launching_animation.PushBack({ 77, 0, 49, 118 });
	launching_animation.PushBack({ 0, 0, 57, 113 });
	launching_animation.loop = false;
	launching_animation.speed = 1.0f;

	current_animation = &launcher_animation_static;
}



