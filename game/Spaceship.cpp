#include "Spaceship.h"
#include "sfwdraw.h"
#include <iostream>

using namespace sfw;


Spaceship::Spaceship()
{
	vertThrust = 0;
	horizThrust = 0;
	breakPower = 10.0f;
	stopAction = 0.0f;
	
	speed = 500;
	maxSpeed = 1000;
	sprintSpeed = 3000;

	turnSpeed = .2f;	
}


Spaceship::~Spaceship()
{
}

void Spaceship::doVert(float val)
{
	vertThrust = val;
}

void Spaceship::doHoriz(float val)
{
	horizThrust += val;
}

void Spaceship::doTurn(float val)
{
	turnThrust = val;
}

void Spaceship::doStop(float val)
{
	stopAction += val;
}


void Spaceship::update(Transform &trans, RigidBody & rigid)
{

	
	if(abs(rigid.velocity.x + rigid.velocity.y) < maxSpeed && abs(rigid.velocity.x) < maxSpeed && abs(rigid.velocity.y) < maxSpeed)
	{ 
		rigid.addForce(trans.getUp() * speed * vertThrust);
		rigid.addForce(-perp(trans.getUp()) * speed * horizThrust);
	}
		

	
	trans.rotAngle += turnThrust * turnSpeed;

	
	rigid.addForce(-rigid.velocity * breakPower * stopAction);

	

	horizThrust = vertThrust = stopAction = 0;
}
