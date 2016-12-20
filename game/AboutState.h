#pragma once
#include "State.h"
#include "MenuButton.h"

class AboutState :
	public State
{
	unsigned font;
	int cursor, clickedCursor;
	int W, H;
	MenuButton backButton;
public:
	AboutState(int inW = 600, int inH = 600);
	AboutState(int inFont, int inCursor, int inClickedCursor, int inW = 600, int inH = 600);
	~AboutState();
	void play();
	void draw();
	void tick();

	EState next();
};

