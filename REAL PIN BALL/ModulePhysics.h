#pragma once
#include "Module.h"
#include "Globals.h"
#include "Box2D/Box2D/Box2D.h"

#define GRAVITY_X 0.0f
#define GRAVITY_Y -7.0f

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)

// Small class to return to other modules to track position and rotation of physics bodies
class PhysBody
{
public:
	PhysBody() : listener(NULL), body(NULL)
	{}

	void GetPosition(int& x, int &y) const;
	float GetRotation() const;
	bool Contains(int x, int y) const;
	int RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const;

public:
	int width, height;
	b2Body* body;
	Module* listener;
	Module* listener_2;
};

// Module --------------------------------------
class ModulePhysics : public Module, public b2ContactListener // TODO
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();
	bool issensor = true;
	PhysBody* CreateCircle(int x, int y, int radius, enum b2BodyType e);
	PhysBody* CreateRectangle(int x, int y, int width, int height);
	PhysBody* CreateRectangleSensor(int x, int y, int width, int height, float32 an, bool issensor);
	PhysBody* CreateChain(int x, int y, int* points, int size);


	PhysBody* map_chain;
	PhysBody* map_chain_2;
	PhysBody* map_chain_3;
	PhysBody* map_chain_4;
	PhysBody* map_chain_5;
	PhysBody* map_chain_6;

	// b2ContactListener ---
	void BeginContact(b2Contact* contact);

	//lever1--------------
	b2Body* chain_body = nullptr;
	b2RevoluteJointDef jointdef;
	b2RevoluteJoint* joint_lever;

	//lever2-------------
	b2Body* chain_body_1;
	b2RevoluteJointDef jointdef_1;
	b2RevoluteJoint* joint_lever_1;

	//lever3-------------
	b2Body* chain_body_2 = nullptr;
	b2RevoluteJointDef jointdef_2;
	b2RevoluteJoint* joint_lever_2;


	//lever4-------------
	b2Body* chain_body_3 = nullptr;
	b2RevoluteJointDef jointdef_3;
	b2RevoluteJoint* joint_lever_3;
	
public:

	int font_score = -1;
	char score_text[10];
	char high_score_text[10];
	uint score = 0;
	uint high_score = 0;

private:

	bool debug;
	b2World* world;
	b2MouseJoint* mouse_joint;
	b2Body* ground;


	SDL_Rect bottom_lever_left;
	SDL_Texture* texture_lever;

};