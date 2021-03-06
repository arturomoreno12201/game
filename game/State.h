#pragma once
#include "StateEnum.h"


class State
{
public:
	State();
	State(unsigned inFont);
	~State();

	unsigned font;
	EState nextState;	
	virtual void play() = 0;

	virtual void draw() = 0;
	virtual void tick() = 0;

	EState next();
};

