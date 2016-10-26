#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
#include "Animation.h"
#include"ModulePhysics.h"

class PhysBody;

class ModuleSceneIntro : public Module, public b2ContactListener
{
public:

	/*ModuleSceneIntro();*/

	ModuleSceneIntro(Application* app, bool start_enabled = true);

	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:
	PhysBody* ball;
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> ricks;

	PhysBody* sensor;
	PhysBody* sensor_ball_down;
	bool sensed;

	uint bonus_fx;
	p2Point<int> ray;
	bool ray_on;
	bool grav;
	bool force;
	b2World* world;
	bool check;

public:
	SDL_Texture* box;
	SDL_Texture* rick;
	SDL_Texture* map_layout;
	SDL_Texture* pin_ball_ball;

	SDL_Texture* sprite;
	
	
	SDL_Texture* texture_lever;
	SDL_Texture* texture_lever_2;
	SDL_Texture* texture_lever_3;
	SDL_Texture* texture_lever_4;
	SDL_Texture* stick;
	SDL_Texture* score_txt;
	SDL_Texture* balls_left;
	SDL_Texture* finish;

	Animation coins;
	Animation green_button;
	Animation green_button_2;
	Animation red_button;
	Animation red_button_2;


public:
	int font_score = -1;
	char score_text[10];
	uint score = 0;

	int font_balls_left = -1;
	char balls_text[10];
	uint balls;
	bool see;
	bool help = true;

	/*char high_score_text[10];*/
	
	/*uint high_score = 0;*/

};
