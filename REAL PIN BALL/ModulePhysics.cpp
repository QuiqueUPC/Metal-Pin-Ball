#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"
#include "p2Point.h"
#include "math.h"
#include "ModuleFonts.h"

#ifdef _DEBUG
#pragma comment( lib, "Box2D/libx86/Debug/Box2D.lib" )
#else
#pragma comment( lib, "Box2D/libx86/Release/Box2D.lib" )
#endif

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	map_chain = map_chain_2 = map_chain_3 = map_chain_4 = map_chain_5 = map_chain_6 = NULL;
	world = NULL;
	mouse_joint = NULL;
	debug = false;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");

	world = new b2World(b2Vec2(GRAVITY_X, -GRAVITY_Y));
	world->SetContactListener(this);



	// needed to create joints like mouse joint
	b2BodyDef bd;
	ground = world->CreateBody(&bd);

	//big static circle as "ground" in the middle of the screen
	int x = SCREEN_WIDTH / 2;
	int y = SCREEN_HEIGHT / 1.5f;
	int diameter = SCREEN_WIDTH / 2;


	//-------MAPCHAIN. LAYOUT 1.-----------
	int map_layout[85] = {
		196, 267,
		196, 246,
		28, 195,
		28, 13,
		43, -8,
		68, -12,
		76, -36,
		100, -46,
		28, -269,
		28, -322,
		46, -389,
		85, -447,
		143, -489,
		209, -510,
		270, -509,
		329, -489,
		377, -455,
		420, -404,
		437, -363,
		446, -318,
		446, 246,
		406, 246,
		406, -309,
		398, -358,
		374, -398,
		346, -429,
		318, -448,
		316, -441,
		339, -423,
		367, -396,
		387, -358,
		397, -312,
		397, -272,
		349, -127,
		398, -106,
		398, 146,
		316, 172,
		326, 189,
		399, 168,
		399, 209,
		276, 245,
		276, 276,
		281
		
	};


	map_chain = App->physics->CreateChain(-23, 514, map_layout, 85);

	//-------MAPCHAIN. LAYOUT 2. BOTTOM LEFT-----------
	// Pivot 23, -514
	int map_layout_2[14] = {
		75, 47,
		68, 47,
		68, 165,
		156, 191,
		159, 178,
		164, 174,
		75, 147
	};
	map_chain_2 = App->physics->CreateChain(-23, 514, map_layout_2, 14);

	//-------MAPCHAIN. LAYOUT 3  UP BOTTOM LEFT.-----------

	// Pivot 23, -514
	int map_layout_3[16] = {
		115, 112,
		115, 43,
		119, 42,
		151, 122,
		151, 127,
		146, 128,
		123, 121,
		118, 116
	};
	map_chain_3 = App->physics->CreateChain(-23, 514, map_layout_3, 16);
	//-------MAPCHAIN. LAYOUT 4. UP BOTTOM RIGHT-----------
	// Pivot -434, -514
	int map_layout_4[16] = {
		-98, 112,
		-98, 42,
		-101, 41,
		-135, 124,
		-133, 128,
		-125, 128,
		-106, 121,
		-101, 116
	};
	map_chain_4 = App->physics->CreateChain(434, 514, map_layout_4, 16);
	//-------MAPCHAIN. LAYOUT 5.UP LEFT-----------
	// Pivot -434, -514
	int map_layout_5[50] = {
		-317, -57,
		-312, -62,
		-370, -239,
		-376, -258,
		-380, -273,
		-382, -305,
		-379, -332,
		-371, -359,
		-359, -384,
		-343, -405,
		-331, -419,
		-315, -432,
		-304, -439,
		-308, -444,
		-318, -438,
		-335, -424,
		-349, -410,
		-365, -388,
		-378, -360,
		-386, -333,
		-389, -304,
		-387, -272,
		-383, -255,
		-377, -236,
		-326, -80,
	};

	map_chain_5 = App->physics->CreateChain(434, 514, map_layout_5, 50);
	//-------MAPCHAIN. LAYOUT 6. UP MIDDLE-----------
	// Pivot -434, -514
	int map_layout_6[78] = {
		-105, -261,
		-102, -272,
		-99, -290,
		-99, -314,
		-105, -341,
		-119, -368,
		-136, -388,
		-157, -405,
		-180, -415,
		-203, -421,
		-223, -422,
		-242, -420,
		-259, -416,
		-275, -409,
		-294, -397,
		-307, -386,
		-316, -375,
		-325, -361,
		-334, -342,
		-328, -339,
		-320, -357,
		-312, -370,
		-302, -381,
		-291, -391,
		-272, -403,
		-257, -409,
		-241, -414,
		-223, -415,
		-203, -414,
		-181, -408,
		-160, -399,
		-139, -382,
		-124, -364,
		-111, -338,
		-106, -317,
		-105, -295,
		-106, -287,
		-108, -273,
		-110, -266
	};
	map_chain_6 = App->physics->CreateChain(434, 514, map_layout_6, 78);
	App->physics->CreateRectangle(404, 720, 39, 81);



	//Jpint thing going on HERE//
	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(147), PIXEL_TO_METERS(702));
	//body.angle = 0.1f * b2_pi;


	b2Body* joint_ball = world->CreateBody(&body);

	b2CircleShape shape;
	shape.m_radius = 0.1f;

	b2FixtureDef fixture;
	fixture.shape = &shape;
	//fixture.density = 0.3;
	joint_ball->CreateFixture(&fixture);

	b2Vec2 vertices[6] = {};
	vertices[0].Set(PIXEL_TO_METERS(12.0f), PIXEL_TO_METERS(10.0f));
	vertices[1].Set(PIXEL_TO_METERS(33.0f), PIXEL_TO_METERS(30.0f));
	vertices[2].Set(PIXEL_TO_METERS(56.0f), PIXEL_TO_METERS(57.0f));
	vertices[3].Set(PIXEL_TO_METERS(50.0f), PIXEL_TO_METERS(59.0f));
	vertices[4].Set(PIXEL_TO_METERS(0.0f), PIXEL_TO_METERS(29.0f));
	vertices[5].Set(PIXEL_TO_METERS(5.0f), PIXEL_TO_METERS(10.0f));


	b2BodyDef chain;
	chain.position.Set(PIXEL_TO_METERS(135), PIXEL_TO_METERS(690));
	chain.type = b2_dynamicBody;
	chain_body = world->CreateBody(&chain);

	b2PolygonShape polygonshape;
	polygonshape.Set(vertices, 6);

	b2FixtureDef fixture_chain;
	fixture_chain.shape = &polygonshape;
	fixture_chain.density = 0.5f;

	chain_body->CreateFixture(&fixture_chain);

	jointdef.bodyA = chain_body;
	jointdef.bodyB = joint_ball;
	jointdef.localAnchorA.Set(0.2f, 0.4f);
	//jointdef.localAnchorA.Set(3.0f, 0.0f);
	jointdef.lowerAngle = 0.0f * b2_pi; // -90 degrees
	jointdef.upperAngle = 0.35f * b2_pi; // 45 degrees
	jointdef.enableLimit = true;
	jointdef.enableMotor = false;
	jointdef.maxMotorTorque = 10000.0f;
	jointdef.motorSpeed = 0.0f;
	jointdef.collideConnected = false;

	joint_lever = (b2RevoluteJoint*)world->CreateJoint(&jointdef);

	//-----------------------------2----------------------------------

	b2BodyDef body_1;
	body_1.type = b2_staticBody;
	body_1.position.Set(PIXEL_TO_METERS(284), PIXEL_TO_METERS(702));
	//body.angle = 0.1f * b2_pi;


	b2Body* joint_ball_1 = world->CreateBody(&body_1);

	b2CircleShape shape_1;
	shape_1.m_radius = 0.1f;

	b2FixtureDef fixture_1;
	fixture_1.shape = &shape_1;
	//fixture.density = 0.3;
	joint_ball_1->CreateFixture(&fixture_1);

	b2Vec2 vertices_1[6];
	vertices_1[0].Set(PIXEL_TO_METERS(113.0f), PIXEL_TO_METERS(77.0f));
	vertices_1[1].Set(PIXEL_TO_METERS(115.0f), PIXEL_TO_METERS(96.0f));
	vertices_1[2].Set(PIXEL_TO_METERS(67), PIXEL_TO_METERS(123.0f));
	vertices_1[3].Set(PIXEL_TO_METERS(60.0f), PIXEL_TO_METERS(121.0f));
	vertices_1[4].Set(PIXEL_TO_METERS(78.0f), PIXEL_TO_METERS(100.0f));
	vertices_1[5].Set(PIXEL_TO_METERS(103.0f), PIXEL_TO_METERS(77.0f));


	b2BodyDef chain_1;
	chain_1.position.Set(PIXEL_TO_METERS(177), PIXEL_TO_METERS(615));
	chain_1.type = b2_dynamicBody;
	chain_body_1 = world->CreateBody(&chain_1);

	b2PolygonShape polygonshape_1;
	polygonshape_1.Set(vertices_1, 6);

	b2FixtureDef fixture_chain_1;
	fixture_chain_1.shape = &polygonshape_1;
	fixture_chain_1.density = 0.5f;
	chain_body_1->CreateFixture(&fixture_chain_1);



	jointdef_1.bodyA = chain_body_1;
	jointdef_1.bodyB = joint_ball_1;
	jointdef_1.localAnchorA.Set(2.12f, 1.76f);

	//jointdef_1.localAnchorB.Set(-0.0f, 0.0f);
	jointdef_1.lowerAngle = -0.35f * b2_pi; // -90 degrees
	jointdef_1.upperAngle = -0.01f * b2_pi; // 45 degrees
	jointdef_1.enableLimit = true;
	jointdef_1.enableMotor = false;
	jointdef_1.maxMotorTorque = 10000.0f;
	jointdef_1.motorSpeed = 0.0f;
	jointdef_1.collideConnected = false;

	joint_lever_1 = (b2RevoluteJoint*)world->CreateJoint(&jointdef_1);
	//-------------------3----------------------------------------

	b2BodyDef body_2;
	body_2.type = b2_staticBody;
	body_2.position.Set(PIXEL_TO_METERS(126), PIXEL_TO_METERS(464));
	//body.angle = 0.1f * b2_pi;


	b2Body* joint_ball_2 = world->CreateBody(&body_2);

	b2CircleShape shape_2;
	shape_2.m_radius = 0.07f;

	b2FixtureDef fixture_2;
	fixture_2.shape = &shape_2;
	//fixture.density = 0.3;
	joint_ball_2->CreateFixture(&fixture_2);

	b2Vec2 vertices_2[6];
	vertices_2[0].Set(PIXEL_TO_METERS(-116.0f), PIXEL_TO_METERS(-44.0f));
	vertices_2[1].Set(PIXEL_TO_METERS(-76.0f), PIXEL_TO_METERS(-22.0f));
	vertices_2[2].Set(PIXEL_TO_METERS(-77.0f), PIXEL_TO_METERS(-30.0f));
	vertices_2[3].Set(PIXEL_TO_METERS(-106.0f), PIXEL_TO_METERS(-58.0f));
	vertices_2[4].Set(PIXEL_TO_METERS(-114.0f), PIXEL_TO_METERS(-59.0f));
	vertices_2[5].Set(PIXEL_TO_METERS(-103.0f), PIXEL_TO_METERS(-44.0f));


	b2BodyDef chain_2;
	chain_2.position.Set(PIXEL_TO_METERS(235), PIXEL_TO_METERS(514));
	chain_2.type = b2_dynamicBody;
	chain_body_2 = world->CreateBody(&chain_2);

	b2PolygonShape polygonshape_2;
	polygonshape_2.Set(vertices_2, 6);

	b2FixtureDef fixture_chain_2;
	fixture_chain_2.shape = &polygonshape_2;
	fixture_chain_2.density = 0.2f;
	chain_body_2->CreateFixture(&fixture_chain_2);



	jointdef_2.bodyA = chain_body_2;
	jointdef_2.bodyB = joint_ball_2;
	jointdef_2.localAnchorA.Set(-2.2f, -1.0f);

	//jointdef_1.localAnchorB.Set(-0.0f, 0.0f);
	jointdef_2.lowerAngle = 0.01f * b2_pi; // -90 degrees
	jointdef_2.upperAngle = 0.35f * b2_pi; // 45 degrees
	jointdef_2.enableLimit = true;
	jointdef_2.enableMotor = false;
	jointdef_2.maxMotorTorque = 10000.0f;
	jointdef_2.motorSpeed = 0.0f;
	jointdef_2.collideConnected = false;

	joint_lever_2 = (b2RevoluteJoint*)world->CreateJoint(&jointdef_2);

	//---------------4------------------------------------
	b2BodyDef body_3;
	body_3.type = b2_staticBody;
	body_3.position.Set(PIXEL_TO_METERS(320), PIXEL_TO_METERS(260));
	//body.angle = 0.1f * b2_pi;


	b2Body* joint_ball_3 = world->CreateBody(&body_3);

	b2CircleShape shape_3;
	shape_3.m_radius = 0.07f;

	b2FixtureDef fixture_3;
	fixture_3.shape = &shape_3;
	//fixture.density = 0.3;
	joint_ball_3->CreateFixture(&fixture_3);

	b2Vec2 vertices_3[6];
	vertices_3[0].Set(PIXEL_TO_METERS(-107.0f), PIXEL_TO_METERS(-48.0f));
	vertices_3[1].Set(PIXEL_TO_METERS(-146.0f), PIXEL_TO_METERS(-27.0f));
	vertices_3[2].Set(PIXEL_TO_METERS(-150.0f), PIXEL_TO_METERS(-29.0f));
	vertices_3[3].Set(PIXEL_TO_METERS(-120.0f), PIXEL_TO_METERS(-60.0f));
	vertices_3[4].Set(PIXEL_TO_METERS(-111.0f), PIXEL_TO_METERS(-63.0f));
	vertices_3[5].Set(PIXEL_TO_METERS(-105.0f), PIXEL_TO_METERS(-49.0f));



	b2BodyDef chain_3;
	chain_3.position.Set(PIXEL_TO_METERS(435), PIXEL_TO_METERS(314));
	chain_3.type = b2_dynamicBody;
	chain_body_3 = world->CreateBody(&chain_3);

	b2PolygonShape polygonshape_3;
	polygonshape_3.Set(vertices_3, 6);

	b2FixtureDef fixture_chain_3;
	fixture_chain_3.shape = &polygonshape_3;
	fixture_chain_3.density = 0.2f;
	chain_body_3->CreateFixture(&fixture_chain_3);



	jointdef_3.bodyA = chain_body_3;
	jointdef_3.bodyB = joint_ball_3;
	jointdef_3.localAnchorA.Set(-2.3f, -1.1f);

	//jointdef_1.localAnchorB.Set(-0.0f, 0.0f);
	jointdef_3.lowerAngle = -0.35f * b2_pi; // -90 degrees
	jointdef_3.upperAngle = 0.01f * b2_pi; // 45 degrees
	jointdef_3.enableLimit = true;
	jointdef_3.enableMotor = false;
	jointdef_3.maxMotorTorque = 10000.0f;
	jointdef_3.motorSpeed = 0.0f;
	jointdef_3.collideConnected = false;

	joint_lever_3 = (b2RevoluteJoint*)world->CreateJoint(&jointdef_3);

	//-------------------------------------------------------

	b2BodyDef red_1;
	red_1.type = b2_staticBody;
	red_1.position.Set(PIXEL_TO_METERS(141), PIXEL_TO_METERS(157));
	//body.angle = 0.1f * b2_pi;


	b2Body* red_body = world->CreateBody(&red_1);

	b2CircleShape red_shape;
	red_shape.m_radius = 0.3f;

	b2FixtureDef fixture_red;
	fixture_red.shape = &red_shape;
	//fixture.density = 0.3;
	fixture_red.restitution = 1.0f;
	red_body->CreateFixture(&fixture_red);
	//----------------------------------------------------------------
	b2BodyDef red_2;
	red_2.type = b2_staticBody;
	red_2.position.Set(PIXEL_TO_METERS(288), PIXEL_TO_METERS(157));
	//body.angle = 0.1f * b2_pi;


	b2Body* red_body_2 = world->CreateBody(&red_2);

	b2CircleShape red_shape_2;
	red_shape_2.m_radius = 0.3f;

	b2FixtureDef fixture_red_2;
	fixture_red_2.shape = &red_shape_2;
	//fixture.density = 0.3;
	fixture_red_2.restitution = 1.0f;
	red_body_2->CreateFixture(&fixture_red_2);

	//----------------------------------------------------------------
	b2BodyDef red_3;
	red_3.type = b2_staticBody;
	red_3.position.Set(PIXEL_TO_METERS(219), PIXEL_TO_METERS(120));
	//body.angle = 0.1f * b2_pi;


	b2Body* red_body_3 = world->CreateBody(&red_3);

	b2CircleShape red_shape_3;
	red_shape_3.m_radius = 0.3f;

	b2FixtureDef fixture_red_3;
	fixture_red_3.shape = &red_shape_3;
	//fixture.density = 0.3;
	fixture_red_3.restitution = 0.5f;

	red_body_3->CreateFixture(&fixture_red_3);

	//-----------------------------------------

	b2BodyDef green;
	green.type = b2_staticBody;
	green.position.Set(PIXEL_TO_METERS(221), PIXEL_TO_METERS(241));
	//body.angle = 0.1f * b2_pi;


	b2Body* green_body = world->CreateBody(&green);

	b2CircleShape green_shape;
	green_shape.m_radius = 0.22f;

	b2FixtureDef fixture_green;
	fixture_green.shape = &green_shape;
	//fixture_green.density = 0.3;
	fixture_green.restitution = 0.3f;
	fixture_green.isSensor = true;

	green_body->CreateFixture(&fixture_green);

	//---------------------------------
	b2BodyDef green_2;
	green_2.type = b2_staticBody;
	green_2.position.Set(PIXEL_TO_METERS(123), PIXEL_TO_METERS(333));
	//body.angle = 0.1f * b2_pi;


	b2Body* green_body_2 = world->CreateBody(&green_2);

	b2CircleShape green_shape_2;
	green_shape_2.m_radius = 0.22f;

	b2FixtureDef fixture_green_2;
	fixture_green_2.shape = &green_shape;
	//fixture_green_2.density = 0.3;
	fixture_green_2.restitution = 0.5f;
	fixture_green_2.isSensor = true;

	green_body_2->CreateFixture(&fixture_green_2);

	//---------------------------------
	b2BodyDef green_3;
	green_3.type = b2_staticBody;
	green_3.position.Set(PIXEL_TO_METERS(312), PIXEL_TO_METERS(333));
	//body.angle = 0.1f * b2_pi;


	b2Body* green_body_3 = world->CreateBody(&green_3);

	b2CircleShape green_shape_3;
	green_shape_3.m_radius = 0.22f;

	b2FixtureDef fixture_green_3;
	fixture_green_3.shape = &green_shape_3;
	//fixture_green_3.density = 0.3;
	fixture_green_3.restitution = 0.5f;
	fixture_green_3.isSensor = true;

	green_body_3->CreateFixture(&fixture_green_3);

	//---------------------------------
	b2BodyDef green_4;
	green_4.type = b2_staticBody;
	green_4.position.Set(PIXEL_TO_METERS(221), PIXEL_TO_METERS(424));
	//body.angle = 0.1f * b2_pi;


	b2Body* green_body_4 = world->CreateBody(&green_4);

	b2CircleShape green_shape_4;
	green_shape_4.m_radius = 0.22f;

	b2FixtureDef fixture_green_4;
	fixture_green_4.shape = &green_shape_4;
	//fixture_green_4.density = 0.3;
	fixture_green_4.restitution = 1.0f;
	fixture_green_4.isSensor = true;

	green_body_4->CreateFixture(&fixture_green_4);


	//---------------------------------
	b2BodyDef green_5;
	green_5.type = b2_staticBody;
	green_5.position.Set(PIXEL_TO_METERS(208), PIXEL_TO_METERS(32));
	//body.angle = 0.1f * b2_pi;


	b2Body* green_body_5 = world->CreateBody(&green_5);

	b2CircleShape green_shape_5;
	green_shape_5.m_radius = 0.22f;

	b2FixtureDef fixture_green_5;
	fixture_green_5.shape = &green_shape_5;
	//fixture_5.density = 0.3;
	fixture_green_5.restitution = 1.0f;
	fixture_green_5.isSensor = true;

	green_body_5->CreateFixture(&fixture_green_5);

	//---------------------------------
	b2BodyDef green_6;
	green_6.type = b2_staticBody;
	green_6.position.Set(PIXEL_TO_METERS(262), PIXEL_TO_METERS(40));
	//body.angle = 0.1f * b2_pi;


	b2Body* green_body_6 = world->CreateBody(&green_6);

	b2CircleShape green_shape_6;
	green_shape_6.m_radius = 0.22f;

	b2FixtureDef fixture_green_6;
	fixture_green_6.shape = &green_shape_6;
	//fixture_6.density = 0.3;
	fixture_green_6.restitution = 1.0f;
	fixture_green_6.isSensor = true;

	green_body_6->CreateFixture(&fixture_green_6);

	//---------------------------------
	b2BodyDef green_7;
	green_7.type = b2_staticBody;
	green_7.position.Set(PIXEL_TO_METERS(157), PIXEL_TO_METERS(41));
	//body.angle = 0.1f * b2_pi;


	b2Body* green_body_7 = world->CreateBody(&green_7);

	b2CircleShape green_shape_7;
	green_shape_7.m_radius = 0.22f;

	b2FixtureDef fixture_green_7;
	fixture_green_7.shape = &green_shape_7;
	//fixture_7.density = 0.3;
	fixture_green_7.restitution = 1.0f;
	fixture_green_7.isSensor = true;

	green_body_7->CreateFixture(&fixture_green_7);

	return true;
}


// 
update_status ModulePhysics::PreUpdate()
{
	world->Step(1.0f / 60.0f, 6, 2);

	for(b2Contact* c = world->GetContactList(); c; c = c->GetNext())
	{
		if(c->GetFixtureA()->IsSensor() && c->IsTouching())
		{
			PhysBody* pb1 = (PhysBody*)c->GetFixtureA()->GetBody()->GetUserData();
			PhysBody* pb2 = (PhysBody*)c->GetFixtureB()->GetBody()->GetUserData();
			if(pb1 && pb2 && pb1->listener)
				pb1->listener->OnCollision(pb1, pb2);
		}
	}

	return UPDATE_CONTINUE;
}

PhysBody* ModulePhysics::CreateCircle(int x, int y, int radius, enum b2BodyType e)
{
	b2BodyDef body;
	body.type = e;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));
	

	b2Body* b = world->CreateBody(&body);

	b2CircleShape shape;
	shape.m_radius = PIXEL_TO_METERS(radius);
	
	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = 0.0001f;
	
	

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = radius;

	return pbody;
}

PhysBody* ModulePhysics::CreateRectangle(int x, int y, int width, int height)
{
	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);
	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(width) * 0.5f, PIXEL_TO_METERS(height) * 0.5f);

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = width * 0.5f;
	pbody->height = height * 0.5f;

	return pbody;
}

PhysBody* ModulePhysics::CreateRectangleSensor(int x, int y, int width, int height, float32 an, bool a)
{
	issensor = a;
	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));
	body.angle = an;

	b2Body* b = world->CreateBody(&body);

	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(width) * 0.5f, PIXEL_TO_METERS(height) * 0.5f);

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;
	fixture.isSensor = issensor;
	

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = width;
	pbody->height = height;

	return pbody;
}

PhysBody* ModulePhysics::CreateChain(int x, int y, int* points, int size)
{
	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2ChainShape shape;
	b2Vec2* p = new b2Vec2[size / 2];

	for(uint i = 0; i < size / 2; ++i)
	{
		p[i].x = PIXEL_TO_METERS(points[i * 2 + 0]);
		p[i].y = PIXEL_TO_METERS(points[i * 2 + 1]);
	}

	shape.CreateLoop(p, size / 2);

	b2FixtureDef fixture;
	fixture.shape = &shape;

	b->CreateFixture(&fixture);

	delete p;

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = 0;

	return pbody;
}

// 
update_status ModulePhysics::PostUpdate()
{
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(!debug)
		return UPDATE_CONTINUE;

	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	for(b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		for(b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch(f->GetType())
			{
				// Draw circles ------------------------------------------------
				case b2Shape::e_circle:
				{
					b2CircleShape* shape = (b2CircleShape*)f->GetShape();
					b2Vec2 pos = f->GetBody()->GetPosition();
					App->renderer->DrawCircle(METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), METERS_TO_PIXELS(shape->m_radius), 255, 255, 255);
				}
				break;

				// Draw polygons ------------------------------------------------
				case b2Shape::e_polygon:
				{
					b2PolygonShape* polygonShape = (b2PolygonShape*)f->GetShape();
					int32 count = polygonShape->GetVertexCount();
					b2Vec2 prev, v;

					for(int32 i = 0; i < count; ++i)
					{
						v = b->GetWorldPoint(polygonShape->GetVertex(i));
						if(i > 0)
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);

						prev = v;
					}

					v = b->GetWorldPoint(polygonShape->GetVertex(0));
					App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);
				}
				break;

				// Draw chains contour -------------------------------------------
				case b2Shape::e_chain:
				{
					b2ChainShape* shape = (b2ChainShape*)f->GetShape();
					b2Vec2 prev, v;

					for(int32 i = 0; i < shape->m_count; ++i)
					{
						v = b->GetWorldPoint(shape->m_vertices[i]);
						if(i > 0)
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
						prev = v;
					}

					v = b->GetWorldPoint(shape->m_vertices[0]);
					App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
				}
				break;

				// Draw a single segment(edge) ----------------------------------
				case b2Shape::e_edge:
				{
					b2EdgeShape* shape = (b2EdgeShape*)f->GetShape();
					b2Vec2 v1, v2;

					v1 = b->GetWorldPoint(shape->m_vertex0);
					v1 = b->GetWorldPoint(shape->m_vertex1);
					App->renderer->DrawLine(METERS_TO_PIXELS(v1.x), METERS_TO_PIXELS(v1.y), METERS_TO_PIXELS(v2.x), METERS_TO_PIXELS(v2.y), 100, 100, 255);
				}
				break;
			}

			// TODO 1: If mouse button 1 is pressed ...
			// App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN
			// test if the current body contains mouse position
		}
	}

	// If a body was selected we will attach a mouse joint to it
	// so we can pull it around
	// TODO 2: If a body was selected, create a mouse joint
	// using mouse_joint class property


	// TODO 3: If the player keeps pressing the mouse button, update
	// target position and draw a red line between both anchor points

	// TODO 4: If the player releases the mouse button, destroy the joint

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	// Delete the whole physics world!
	delete world;
	
	return true;
}

void PhysBody::GetPosition(int& x, int &y) const
{
	b2Vec2 pos = body->GetPosition();
	x = METERS_TO_PIXELS(pos.x) - (width);
	y = METERS_TO_PIXELS(pos.y) - (height);
}

float PhysBody::GetRotation() const
{
	return RADTODEG * body->GetAngle();
}

bool PhysBody::Contains(int x, int y) const
{
	b2Vec2 p(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	const b2Fixture* fixture = body->GetFixtureList();

	while(fixture != NULL)
	{
		if(fixture->GetShape()->TestPoint(body->GetTransform(), p) == true)
			return true;
		fixture = fixture->GetNext();
	}

	return false;
}

int PhysBody::RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const
{
	int ret = -1;

	b2RayCastInput input;
	b2RayCastOutput output;

	input.p1.Set(PIXEL_TO_METERS(x1), PIXEL_TO_METERS(y1));
	input.p2.Set(PIXEL_TO_METERS(x2), PIXEL_TO_METERS(y2));
	input.maxFraction = 1.0f;

	const b2Fixture* fixture = body->GetFixtureList();

	while(fixture != NULL)
	{
		if(fixture->GetShape()->RayCast(&output, input, body->GetTransform(), 0) == true)
		{
			// do we want the normal ?

			float fx = x2 - x1;
			float fy = y2 - y1;
			float dist = sqrtf((fx*fx) + (fy*fy));

			normal_x = output.normal.x;
			normal_y = output.normal.y;

			return output.fraction * dist;
		}
		fixture = fixture->GetNext();
	}

	return ret;
}

void ModulePhysics::BeginContact(b2Contact* contact)
{
	PhysBody* physA = (PhysBody*)contact->GetFixtureA()->GetBody()->GetUserData();
	PhysBody* physB = (PhysBody*)contact->GetFixtureB()->GetBody()->GetUserData();

	if(physA && physA->listener != NULL)
		physA->listener->OnCollision(physA, physB);

	if(physB && physB->listener != NULL)
		physB->listener->OnCollision(physB, physA);
}