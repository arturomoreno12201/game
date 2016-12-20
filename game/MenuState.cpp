#include "MenuState.h"





MenuState::MenuState()
{
}

MenuState::MenuState(const GameInstance &instance, int W_a, int H_a)
{
	font = instance.font;
	cursor = instance.cursor;
	clickedCursor = instance.clickedCursor;

	W = W_a;
	H = H_a;
	nextState = EState::MENU;

	playButton = MenuButton(font, W / 2 - 100, H - 250, 200, 50, CYAN, "start", EState::ENTER_GAME);
	
	quitButton = MenuButton(font, W / 2 - 100, H -310, 200, 50, RED, "exit", EState::TERMINATE);
}

MenuState::~MenuState()
{
}

void MenuState::play()
{
	nextState = EState::MENU;
}

void MenuState::tick()
{
	playButton.tick();
	aboutButton.tick();
	optionButton.tick();
	quitButton.tick();
}

void MenuState::draw()
{

	playButton.draw();
	aboutButton.draw();
	optionButton.draw();
	quitButton.draw();

	cursorDraw(cursor, clickedCursor);
}

EState MenuState::next()
{
	if (playButton.isClicked)
	{
		playButton.isClicked = false;
		nextState = playButton.next();
	}
	else if (aboutButton.isClicked)
	{
		aboutButton.isClicked = false;
		nextState = aboutButton.next();
	}
	else if (optionButton.isClicked)
	{
		optionButton.isClicked = false;
		nextState = optionButton.next();
	}
	else if (quitButton.isClicked)
	{
		quitButton.isClicked = false;
		nextState = quitButton.next();
	}

	return nextState;
}
