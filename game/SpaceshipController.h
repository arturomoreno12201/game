#pragma once
#include "Spaceship.h"

class SpaceshipController
{
public:

	SpaceshipController(unsigned aCTR_LEFT = 'A', unsigned aCTR_RIGHT = 'D'
		, unsigned aCTR_UP = 'W', unsigned aCTR_DOWN = 'S', unsigned aCTR_BREAK = ' ', unsigned aCTR_SPRINT = 'F');
	~SpaceshipController();

	unsigned CTR_LEFT, CTR_RIGHT, CTR_UP, CTR_DOWN, CTR_BREAK, CTR_SPRINT;

	void update(Spaceship &ship, float turnAngle, float currentAngle);
};

