#include "SpaceshipController.h"
#include <math.h>
#include "sfwdraw.h"

using namespace sfw;



SpaceshipController::SpaceshipController(unsigned aCTR_LEFT, unsigned aCTR_RIGHT, unsigned aCTR_UP, unsigned aCTR_DOWN, unsigned aCTR_BREAK, unsigned aCTR_SPRINT)
{
	CTR_LEFT = aCTR_LEFT;
	CTR_RIGHT = aCTR_RIGHT;
	CTR_UP = aCTR_UP;
	CTR_DOWN = aCTR_DOWN;
	CTR_BREAK = aCTR_BREAK;
	CTR_SPRINT = aCTR_SPRINT;
}


SpaceshipController::~SpaceshipController()
{
}

void SpaceshipController::update(Spaceship & ship, float turnAngle, float currentAngle)
{
	float hInput = 0;
	
	if (fabsf(fmodf(currentAngle + 90, 360) < 180))	
	{
		hInput += getKey(CTR_LEFT);
		hInput -= getKey(CTR_RIGHT);
	}
	else
	{
		hInput -= getKey(CTR_LEFT);
		hInput += getKey(CTR_RIGHT);
	}
	

	float vInput = 0;
	vInput += getKey(CTR_UP);
	vInput -= getKey(CTR_DOWN);

	float bInput = getKey(CTR_BREAK);

	if (getKey(CTR_SPRINT))
	{
		ship.maxSpeed = ship.sprintSpeed;
		vInput *= 3;	
	}
		

	ship.doHoriz(hInput);
	ship.doVert(vInput);
	ship.doTurn(turnAngle);
	ship.doStop(bInput);
}
