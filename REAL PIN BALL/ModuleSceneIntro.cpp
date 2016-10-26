#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModuleFonts.h"

#include <stdio.h>

//
//ModuleSceneIntro::ModuleSceneIntro()
//{
//
//
//
//
//}
ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{

	//-------------LEVER_1-------------
	//bottom_lever_left.x = 0;
	//bottom_lever_left.y = 209;
	//bottom_lever_left.w = 56;
	//bottom_lever_left.h = 51;
	




	green_button.PushBack({ 32, 35, 27, 25 });
	green_button.PushBack({ 0, 0, 0, 0 });
	green_button.speed = 0.04f;


	green_button_2.PushBack({ 0, 33, 29, 29 });
	green_button_2.PushBack({ 0, 0, 0, 0 });
	green_button_2.speed = 0.04f;

	red_button.PushBack({ 0, 69, 36, 35 });
	red_button.PushBack({ 0, 0, 0, 0 });
	red_button.speed = 0.11f;

	red_button_2.PushBack({ 40, 70, 33, 31 });
	red_button_2.PushBack({ 0, 0, 0, 0 });
	red_button_2.speed = 0.055f;

	coins.PushBack({ 70, 0, 25, 28 });
	coins.PushBack({ 94, 0, 25, 28 });
	coins.PushBack({ 124, 0, 27, 28 });
	coins.PushBack({ 94, 0, 25, 28 });
	coins.PushBack({ 70, 0, 25, 28 });
	coins.PushBack({ 53, 0, 20, 28 });
	coins.PushBack({ 30, 0, 25, 28 });
	coins.PushBack({ 0, 0, 25, 28 });
	coins.PushBack({ 30, 0, 25, 28 });
	coins.PushBack({ 53, 0, 20, 28 });
	coins.speed = 0.08f;

	pin_ball_ball = box = rick = map_layout = sprite = texture_lever = texture_lever_2 = texture_lever_3 = texture_lever_4 = NULL;
	stick = score_txt = balls_left = NULL;
	sensor_ball_down = sensor = ball = NULL;
	
	balls = 1;
	score = 0;
	
	
	//see = true;
	grav = true;
	force = true;
	ray_on = false;
	sensed = false;
	check = true;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	world = new b2World(b2Vec2(GRAVITY_X, -GRAVITY_Y));
	world->SetContactListener(this);

	
	

	App->renderer->camera.x = App->renderer->camera.y = 0;

	
	box = App->textures->Load("pinball/crate.png");
	rick = App->textures->Load("pinball/rick_head.png");
	map_layout = App->textures->Load("pinball/map_layout.png");
	pin_ball_ball = App->textures->Load("pinball/pin_ball_ball.png");
	sprite = App->textures->Load("pinball/Sprite_sheet.png");
	texture_lever = App->textures->Load("pinball/leverito_1.png");
	texture_lever_2 = App->textures->Load("pinball/leverito_2.png");
	texture_lever_3 = App->textures->Load("pinball/leverito_3.png");
	texture_lever_4 = App->textures->Load("pinball/leverito_4.png");
	stick = App->textures->Load("pinball/stick.png");
	font_score = App->fonts->Load("pinball/black_alphabet.png", "abcdefghijklmnopqrstuvwxyz1234567890", 1);
	font_balls_left = App->fonts->Load("pinball/white.png", "abcdefghijklmnopqrstuvwxyz1234567890", 1);
	score_txt = App->textures->Load("pinball/score.png");
	balls_left = App->textures->Load("pinball/balls_left.png");
	finish = App->textures->Load("pinball/finish.png");
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");


	ball = App->physics->CreateCircle(403, 669, 10, b2_dynamicBody);
	sensor = App->physics->CreateRectangleSensor(295, 54, 43, 7, -0.95f, true);
	sensor_ball_down = App->physics->CreateRectangleSensor(212, 758, 70, 1, 0.0f, true);
	App->scene_intro->sensor_ball_down->listener = this;
	/*App->scene_intro->sensor->listener_2;*/

	//sensor->listener_2->OnCollision(sensor, ball);

	
	//sensor->listener->OnCollision(sensor, ball);
	/*circles.getLast()->data->listener = this;*/

	
	/*App->scene_intro->sensor->listener;*/
	
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
	see = true;
	

	App->renderer->Blit(map_layout, 0, 0, NULL);

	sprintf_s(balls_text, 10, "%d", App->scene_intro->balls);
	App->fonts->Blit(199, 575, font_balls_left, balls_text);

	sprintf_s(score_text, 10, "%d", App->scene_intro->score);
	App->fonts->Blit(199, 525, 0, score_text);

	


	App->renderer->Blit(sprite, 63, 231, &(coins.GetCurrentFrame()));
	App->renderer->Blit(sprite, 336, 151, &(coins.GetCurrentFrame()));

	App->renderer->Blit(sprite, 109, 320, &(green_button.GetCurrentFrame()));
	App->renderer->Blit(sprite, 143, 28, &(green_button.GetCurrentFrame()));
	App->renderer->Blit(sprite, 208, 410, &(green_button.GetCurrentFrame()));
	App->renderer->Blit(sprite, 247, 24, &(green_button_2.GetCurrentFrame()));
	App->renderer->Blit(sprite, 193, 17, &(green_button_2.GetCurrentFrame()));
	App->renderer->Blit(sprite, 207, 226, &(green_button_2.GetCurrentFrame()));
	App->renderer->Blit(sprite, 298, 318, &(green_button_2.GetCurrentFrame()));
	App->renderer->Blit(sprite, 124, 140, &(red_button.GetCurrentFrame()));
	App->renderer->Blit(sprite, 203, 103, &(red_button_2.GetCurrentFrame()));
	App->renderer->Blit(sprite, 272, 141, &(red_button_2.GetCurrentFrame()));

	App->renderer->Blit(texture_lever, 89 , 650, NULL, 0.0f, RADTODEG * App->physics->chain_body->GetAngle());
	App->renderer->Blit(texture_lever_2, 227, 650, NULL, 0.0f, RADTODEG * App->physics->chain_body_1->GetAngle());
	App->renderer->Blit(texture_lever_3, 68, 413, NULL, 0.0f, RADTODEG * App->physics->chain_body_2->GetAngle());
	App->renderer->Blit(texture_lever_4, 263, 208, NULL, 0.0f, RADTODEG * App->physics->chain_body_3->GetAngle());
	App->renderer->Blit(score_txt, 173, 500, NULL);
	App->renderer->Blit(balls_left, 169, 555, NULL);
	

	//if (score > high_score) high_score = score;
	//sprintf_s(high_score_text, 10, "%d", App->scene_intro->high_score);
	//App->fonts->Blit(0, 0, 100, high_score_text);
	//if (App->audio->PlayFx(bonus_fx)) {
	//	App->renderer->Blit(stick, 287, 28, NULL);
	//		}
		
	



	int x, y;
	App->scene_intro->ball->GetPosition(x, y);
	App->renderer->Blit(pin_ball_ball, x, y, NULL, 0.0f, App->scene_intro->ball->GetRotation());
	


	if (grav) {
		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN) {
			ball->body->ApplyForce(b2Vec2(0, 0.04f), ball->body->GetWorldCenter(), force);
			force = !force;
			grav = !grav;
			
		}
	}


	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
	{
		App->physics->joint_lever->EnableMotor(true);
		App->physics->joint_lever->SetMotorSpeed(15.6f);

		App->physics->joint_lever_2->EnableMotor(true);
		App->physics->joint_lever_2->SetMotorSpeed(10.6f);
	}
	else if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
	{
		App->physics->joint_lever->EnableMotor(false);
		App->physics->joint_lever_2->EnableMotor(false);
	}


	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		App->physics->joint_lever_1->EnableMotor(true);
		App->physics->joint_lever_1->SetMotorSpeed(-15.6f);

		App->physics->joint_lever_3->EnableMotor(true);
		App->physics->joint_lever_3->SetMotorSpeed(-10.6f);
	}
	else if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
	{
		App->physics->joint_lever_1->EnableMotor(false);
		App->physics->joint_lever_3->EnableMotor(false);
	}


	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		ray_on = !ray_on;
		ray.x = App->input->GetMouseX();
		ray.y = App->input->GetMouseY();
	}

	//if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	//{
	////	circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 10, b2_dynamicBody));
	////	circles.getLast()->data->listener = this;
	//	App->scene_intro->score += 1000;
	//}

	/*if(App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		boxes.add(App->physics->CreateRectangle(App->input->GetMouseX(), App->input->GetMouseY(), 100, 50));
	}*/

	if(App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		// Pivot 0, 0
		int rick_head[64] = {
			14, 36,
			42, 40,
			40, 0,
			75, 30,
			88, 4,
			94, 39,
			111, 36,
			104, 58,
			107, 62,
			117, 67,
			109, 73,
			110, 85,
			106, 91,
			109, 99,
			103, 104,
			100, 115,
			106, 121,
			103, 125,
			98, 126,
			95, 137,
			83, 147,
			67, 147,
			53, 140,
			46, 132,
			34, 136,
			38, 126,
			23, 123,
			30, 114,
			10, 102,
			29, 90,
			0, 75,
			30, 62
		};

		//ricks.add(App->physics->CreateChain(App->input->GetMouseX(), App->input->GetMouseY(), rick_head, 64));
	}

	//-----------MAP LAYOUT CHAIN------------------------------------------------
	// Pivot 23, -514

	

	// Prepare for raycast ------------------------------------------------------
	
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();
	int ray_hit = ray.DistanceTo(mouse);

	fVector normal(0.0f, 0.0f);

	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* c = boxes.getFirst();

	//while(c != NULL)
	//{
	//	int x, y;
	//	c->data->GetPosition(x, y);
	//	App->renderer->Blit(pin_ball_ball, x, y, NULL, 1.0f, c->data->GetRotation());
	//	c = c->next;
	//}
	//
	//c = boxes.getFirst();
	
	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(box, x, y, NULL, 1.0f, c->data->GetRotation());
		if(ray_on)
		{
			int hit = c->data->RayCast(ray.x, ray.y, mouse.x, mouse.y, normal.x, normal.y);
			if(hit >= 0)
				ray_hit = hit;
		}
		c = c->next;
	}

	c = ricks.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(rick, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	// ray -----------------
	if(ray_on == true)
	{
		fVector destination(mouse.x-ray.x, mouse.y-ray.y);
		destination.Normalize();
		destination *= ray_hit;

		App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);

		if(normal.x != 0.0f)
			App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
	}

	
		if (balls == 0) {
			see = App->renderer->Blit(finish, 15, 300, NULL);
		
			//App->textures->Unload(pin_ball_ball);
			if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) {
				//App->textures->Unload(finish);
				see = false;
				ball =  App->physics->CreateCircle(403, 669, 10, b2_dynamicBody);
				App->renderer->Blit(pin_ball_ball, x, y, NULL, 0.0f, App->scene_intro->ball->GetRotation());
				grav = true;
				force = true;
				balls = 1;
				help = true;
			}
		}
		
		
			if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN) {
				if (x >= 382 && y >= 579) {
					ball->body->ApplyForce(b2Vec2(0, 0.04f), ball->body->GetWorldCenter(), force);
				}
				
			}
		
			
	
	


	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

	balls = 0;

	int x, y;
	//
	//App->physics->issensor = false;
	//App->textures->Unload(pin_ball_ball);
	//App->audio->PlayFx(bonus_fx);

	//for (b2Contact* d = world->GetContactList(); d; d = d->GetNext())
	//{
	//	if (d->GetFixtureB()->IsSensor() && d->IsTouching()) {
	//		ball = (PhysBody*)d->GetFixtureA()->GetBody()->GetUserData();
	//		sensor_ball_down = (PhysBody*)d->GetFixtureB()->GetBody();
	//		if (sensor_ball_down && ball && sensor_ball_down->listener_2) {

	//		
	//		}
	//	}
		//}
		//
		//

	/*	if(bodyA->listener){
			score = score + 500;
		}*/

		//if (bodyA->listener->OnCollision) {
		//	
		//	
		//	//App->audio->PlayFx(bonus_fx);
		}

	


