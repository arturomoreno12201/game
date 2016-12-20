#pragma once
#include "sfwdraw.h"
using namespace sfw;


struct GameInstance
{
	
	int ballNum = 4;
	
	unsigned color1 = CYAN, color2 = WHITE;
	
	bool isTimed = true;
	
	int timeLimit = -1;
	
	int width = 500, height = 500;

	unsigned font = loadTextureMap("./res/fontmap.png", 16, 16);
	unsigned cursor = loadTextureMap("./res/ball.png");
	unsigned clickedCursor = loadTextureMap("./res/ball_clicked.png");
};