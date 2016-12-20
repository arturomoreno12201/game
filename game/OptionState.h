#pragma once
#include "State.h"
#include "MenuButton.h"
#include "OptionNum.h"
#include "GameInstance.h"
class OptionState :
	public State
{
	unsigned font;
	int cursor, clickedCursor;
	int W, H;

	OptionNum ballOpt;
	OptionNum widthOpt, heightOpt;
	OptionNum timerOpt;

	MenuButton confirmButton;
	MenuButton cancelButton;
	MenuButton defaultButton;	

	GameInstance instance;

public:
	OptionState(GameInstance inInstance, int inFont, int inCursor, int inClickedCursor, int W_a, int H_a);
	~OptionState();

	
	void play();
	void play(GameInstance inInstance);

	
	void draw();
	void tick();
	void tick(float deltaTime);

	void apply();
	GameInstance getInstance();

	EState next();
};

