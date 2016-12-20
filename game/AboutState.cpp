#include "AboutState.h"
#include "sfwdraw.h"
using namespace sfw;

AboutState::AboutState(int inW, int inH)
{
	W = inW;
	H = inH;
}

AboutState::AboutState(int inFont, int inCursor, int inClickedCursor, int inW, int inH)
{
	font = inFont;
	cursor = inCursor;
	clickedCursor = inClickedCursor;
	backButton = MenuButton(font, 75, 100, 200, 50, WHITE, "Back", EState::ENTER_MENU);

	W = inW;
	H = inH;
}

AboutState::~AboutState()
{
}

void AboutState::play()
{
	//nothing here
}

void AboutState::draw()
{
	drawString(font, "Colorball", 75, H - 50, 30, 30, 0, '\0');

	drawString(font, "Controls: WASD to move.  Use mouse to turn.", 75, H - 100, 15, 15, 0, '\0');

	backButton.draw();

	cursorDraw(cursor, clickedCursor);
}

void AboutState::tick()
{
	backButton.tick();
}

EState AboutState::next()
{
	if (backButton.isClicked) {
		backButton.isClicked = false;
		return backButton.next();
	}
	return ABOUT;
}
