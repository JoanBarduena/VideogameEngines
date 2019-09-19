#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModuleFonts.h"
#include "ModulePlayer.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	map = ball = box = rick = NULL;

	//Animations
	//Pushbacks
	/*In order to have some coordination between some animations,
	i've added a few of extra pusbacks to some of them in which the light will be off,*/
	for (int i = 0; i < 9; ++i) {
		middle_lights.PushBack({32*i,0,32,181});		
	}

	for (int i = 0; i < 4; ++i) {						//lights off
		top_right_lights.PushBack({ 213,274,71,41 });
		top_left_lights.PushBack({271, 240, 57, 34 });
	}

	for (int i = 0; i < 3; ++i) {
		left_lights.PushBack({ 54 * i,181,54,59 });
		top_left_lights.PushBack({57*i, 240, 57, 34});
		top_right_lights.PushBack({71*i,274,71,41});
		right_lights.PushBack({37*i,315,37,54});
	}

	for (int i = 0; i < 4; ++i) {						//lights off
		right_lights.PushBack({ 111,315,37,54 });
	}

	//Loops
	middle_lights.loop = true;
	top_left_lights.loop = true;
	top_right_lights.loop = true;
	right_lights.loop = true;
	left_lights.loop = true;

	//Animation velocity
	middle_lights.speed = 0.17f;
	left_lights.speed =0.10f;
	top_right_lights.speed = right_lights.speed = top_left_lights.speed = 0.11f;
	
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->audio->PlayMusic("Audio/Pinball_Music.ogg");							//Play music

	App->renderer->camera.x = App->renderer->camera.y = 0;

	ball = App->textures->Load("Images/redball.png"); 
	bonus_fx = App->audio->LoadFx("Audio/bonus.wav");
	map = App->textures->Load("Images/Pinball2.0.png"); 

	DrawColliders();

	font_score = App->fonts->Load("Images/7UP_SCORE_FONT.png", "0123456789", 1);//Load Font texture

	lights_texture = App->textures->Load("Images/Lights Texture.png");			//Load lights texture

	

	combo = 1;
	score = 0;
	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	App->renderer->Blit(map, 0, 0, NULL); 
	DrawLights();

	


	// Prepare for raycast ------------------------------------------------------
	
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();

	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* c = circles.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(ball, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	

	//SCORE
	sprintf_s(score_text, 13, "%12d", score);
	App->fonts->BlitText(110, 34, font_score, score_text);


	if (debug) {

		if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
		{
			circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 9, b2_dynamicBody));
			circles.getLast()->data->listener = App->player;
		}

		if (App->input->GetKey(SDL_SCANCODE_M) == KEY_REPEAT)
			IncreaseScore(10);

		if (App->input->GetKey(SDL_SCANCODE_N) == KEY_DOWN)
			combo *= 10;

		if (App->input->GetKey(SDL_SCANCODE_B) == KEY_REPEAT)
			score += 100000000;

		if (App->input->GetKey(SDL_SCANCODE_V) == KEY_REPEAT)
			score = 0;
	}
	

	

	return UPDATE_CONTINUE;
}


void ModuleSceneIntro::DrawLights() {

	App->renderer->Blit(lights_texture, 140, 105, &top_left_lights.GetCurrentFrame());	//Top left lights
	App->renderer->Blit(lights_texture, 58, 218, &left_lights.GetCurrentFrame());		//Left lights
	App->renderer->Blit(lights_texture, 285, 102, &top_right_lights.GetCurrentFrame());	//Top right lights
	App->renderer->Blit(lights_texture, 351, 192, &right_lights.GetCurrentFrame());		//Right lights
	App->renderer->Blit(lights_texture, 226, 328, &middle_lights.GetCurrentFrame());	//Middle lights
}

void ModuleSceneIntro::IncreaseScore(int points) {
	score += points * combo;
}

void ModuleSceneIntro::DrawColliders()
{
	int Map[230] = {
		443, 266,
		444, 234,
		450, 225,
		482, 189,
		494, 173,
		500, 156,
		503, 138,
		503, 123,
		497, 105,
		482, 86,
		466, 77,
		450, 72,
		433, 73,
		418, 78,
		402, 89,
		389, 106,
		385, 114,
		371, 114,
		353, 105,
		321, 98,
		287, 93,
		281, 81,
		205, 81,
		198, 94,
		180, 96,
		158, 105,
		141, 115,
		126, 127,
		116, 121,
		106, 117,
		95, 115,
		84, 115,
		70, 119,
		59, 124,
		48, 133,
		40, 144,
		35, 157,
		34, 168,
		34, 182,
		38, 195,
		47, 210,
		57, 224,
		68, 240,
		91, 273,
		102, 292,
		109, 313,
		114, 335,
		115, 355,
		114, 376,
		111, 396,
		109, 414,
		109, 427,
		113, 452,
		122, 476,
		135, 495,
		155, 517,
		179, 534,
		196, 541,
		201, 542,
		201, 570,
		286, 570,
		286, 543,
		303, 536,
		326, 522,
		345, 503,
		362, 478,
		368, 463,
		373, 445,
		375, 427,
		375, 406,
		372, 387,
		368, 369,
		368, 336,
		370, 325,
		374, 310,
		381, 295,
		390, 281,
		400, 270,
		402, 264,
		401, 256,
		397, 250,
		391, 248,
		385, 248,
		380, 252,
		375, 257,
		372, 261,
		369, 265,
		364, 267,
		362, 265,
		365, 253,
		377, 227,
		390, 201,
		400, 180,
		406, 167,
		408, 157,
		407, 148,
		405, 140,
		405, 130,
		413, 115,
		428, 101,
		443, 98,
		456, 101,
		468, 110,
		476, 123,
		478, 137,
		477, 149,
		473, 160,
		468, 168,
		458, 180,
		446, 192,
		433, 206,
		425, 215,
		421, 231,
		418, 245,
		418, 265
	};
	map_ = App->physics->CreateChain(0, 0, Map, 230); 

	int top_left1[30] = {
	91, 229,
	98, 241,
	103, 249,
	109, 257,
	114, 262,
	118, 266,
	123, 267,
	124, 262,
	121, 253,
	117, 244,
	113, 235,
	109, 227,
	100, 228,
	91, 229,
	90, 229
	};
	top_left_1 = App->physics->CreateChain(0, 0, top_left1, 30); 

	int top_left2[22] = {
	127, 216,
	133, 211,
	138, 203,
	141, 211,
	144, 220,
	147, 228,
	148, 234,
	147, 238,
	141, 237,
	134, 229,
	127, 216
	};
	top_left_2 = App->physics->CreateChain(0, 0, top_left2, 22);

	int top_left3[24] = {
	142, 147,
	146, 156,
	147, 163,
	147, 171,
	165, 165,
	178, 160,
	185, 155,
	188, 146,
	184, 136,
	175, 132,
	162, 134,
	141, 147
	};
	top_left_3 = App->physics->CreateChain(0, 0, top_left3, 24); 

	int top_right[52] = {
		311, 131,
		305, 133,
		301, 136,
		299, 140,
		297, 145,
		297, 150,
		300, 156,
		303, 159,
		345, 174,
		345, 193,
		341, 211,
		338, 224,
		336, 231,
		336, 236,
		338, 238,
		341, 239,
		344, 236,
		348, 228,
		352, 220,
		357, 200,
		361, 179,
		361, 163,
		360, 158,
		356, 154,
		318, 132,
		313, 131
	};
	top_right_1 = App->physics->CreateChain(0, 0, top_right, 52); 

	int middle_top1[18] = {
	222, 121,
	227, 121,
	230, 124,
	230, 148,
	226, 152,
	222, 152,
	219, 148,
	219, 125,
	221, 121
	};
	middle_top_1 = App->physics->CreateChain(0, 0, middle_top1, 18); 

	int middle_top2[18] = {
	259, 121,
	264, 121,
	267, 124,
	267, 148,
	264, 152,
	260, 152,
	256, 148,
	256, 125,
	258, 121
	};
	middle_top_2 = App->physics->CreateChain(0, 0, middle_top2, 18); 

	int middle[36] = {
	205, 295,
	206, 287,
	213, 284,
	226, 282,
	243, 281,
	262, 282,
	275, 284,
	282, 289,
	281, 299,
	276, 310,
	269, 318,
	259, 324,
	259, 327,
	225, 327,
	225, 323,
	217, 318,
	208, 308,
	204, 295
	};
	middle_ = App->physics->CreateChain(0, 0, middle, 36); 

	int bottom_right1[28] = {
	290, 459,
	295, 448,
	302, 432,
	309, 419,
	312, 415,
	317, 415,
	320, 419,
	319, 429,
	316, 440,
	310, 452,
	301, 463,
	296, 466,
	291, 464,
	291, 459
	};
	bottom_right_1 = App->physics->CreateChain(0, 0, bottom_right1, 28); 

	int bottom_right2[52] = {
		347, 410,
		344, 415,
		343, 423,
		341, 431,
		339, 440,
		335, 450,
		330, 459,
		324, 467,
		314, 478,
		306, 483,
		304, 489,
		313, 484,
		318, 489,
		313, 499,
		318, 498,
		325, 492,
		332, 483,
		338, 475,
		344, 464,
		347, 455,
		350, 444,
		352, 431,
		353, 420,
		353, 415,
		352, 411,
		348, 410
	};
	bottom_right_2 = App->physics->CreateChain(0, 0, bottom_right2, 52); 

	int bottom_left1[48] = {
		133, 410,
		131, 414,
		131, 419,
		132, 434,
		137, 460,
		144, 475,
		152, 486,
		159, 493,
		164, 497,
		170, 498,
		163, 488,
		167, 484,
		178, 486,
		175, 482,
		166, 475,
		159, 467,
		152, 457,
		147, 447,
		143, 437,
		141, 429,
		139, 420,
		139, 413,
		137, 410,
		135, 410
	};
	bottom_left_1 = App->physics->CreateChain(0, 0, bottom_left1, 48); 

	int bottom_left2[24] = {
	166, 418,
	169, 415,
	173, 415,
	194, 455,
	195, 462,
	193, 466,
	187, 466,
	180, 459,
	173, 449,
	168, 440,
	166, 430,
	165, 418
	};
	bottom_left_2 = App->physics->CreateChain(0, 0, bottom_left2, 24); 

	int ball_corridor1[18] = {
	450, 345,
	447, 342,
	443, 342,
	439, 345,
	439, 437,
	442, 441,
	447, 441,
	450, 437,
	451, 345
	};
	ball_corridor_1 = App->physics->CreateChain(0, 0, ball_corridor1, 18); 

	int ball_corridor2[30] = {
		417, 272,
		417, 304,
		418, 570,
		440, 570,
		440, 467,
		460, 466,
		466, 463,
		470, 458,
		471, 453,
		471, 347,
		468, 343,
		463, 340,
		456, 339,
		443, 339,
		442, 276,
	};
	ball_corridor_2 = App->physics->CreateChain(0, 0, ball_corridor2, 30);

	int football1[30] = {
	190, 237,
	190, 229,
	193, 225,
	195, 223,
	198, 222,
	201, 222,
	204, 223,
	208, 225,
	210, 229,
	210, 236,
	208, 239,
	204, 243,
	198, 243,
	193, 241,
	189, 238
	};
	football_1 = App->physics->CreateChain(0, 0, football1, 30, 1.0f); 

	int football2[30] = {
	233, 195,
	233, 201,
	235, 204,
	239, 207,
	247, 207,
	250, 205,
	252, 201,
	252, 195,
	250, 191,
	248, 189,
	245, 188,
	241, 188,
	238, 189,
	235, 191,
	232, 194
	};
	football_2 = App->physics->CreateChain(0, 0, football2, 30, 1.0f); 

	int football3[30] = {
	277, 226,
	275, 230,
	275, 236,
	277, 240,
	282, 242,
	288, 242,
	292, 240,
	294, 236,
	294, 229,
	292, 225,
	289, 223,
	286, 222,
	282, 222,
	279, 224,
	276, 226
	};
	football_3 = App->physics->CreateChain(0, 0, football3, 30, 1.0f); 

	int football4[32] = {
		86, 161,
		90, 161,
		95, 162,
		98, 165,
		100, 169,
		100, 174,
		99, 179,
		95, 182,
		91, 183,
		86, 183,
		81, 181,
		79, 177,
		78, 173,
		78, 167,
		81, 162,
		85, 161
	};
	football_4 = App->physics->CreateChain(0, 0, football4, 32, 3.0f); 
}

