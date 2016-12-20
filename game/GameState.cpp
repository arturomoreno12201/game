#include "GameState.h"
#include "ObjectCollision.h"
#include "shapedraw.h"
#include "sfwdraw.h"

#include <cstdlib>
#include <ctime>
#include <math.h>
#include <string>
using namespace sfw;
using namespace std;

void GameState::baseInit(int W_a, int H_a, int xBound_a, int yBound_a)
{
	srand(time(0));
	
	W = W_a;
	H = H_a;

	vec2 b1[] = { { xBound, yBound },{ -xBound, yBound } };
	bounds[0] = Boundary(b1, true);	

	vec2 b2[] = { { xBound, -yBound },{ -xBound, -yBound } };
	bounds[1] = Boundary(b2, false);	

	vec2 b3[] = { { xBound, yBound },{ xBound, -yBound } };
	bounds[2] = Boundary(b3, true);

	vec2 b4[] = { { -xBound, yBound },{ -xBound, -yBound } };
	bounds[3] = Boundary(b4, false);	
	releaseCursor = false;
	releaseTimer = -1.f;

	timeLimit = -2;
	currentTime = 0;
}

GameState::GameState(std::string inTitle, unsigned inFont, int W_a, int H_a)
{
	xBound = yBound = 600;
	baseInit(W_a, H_a, xBound, yBound);

	camera = Camera(W / 2, H / 2);
	nextState = EState::GAME;
	font = inFont;
	title = inTitle;
}


GameState::~GameState()
{
}

void GameState::play()
{
	printf("ERROR: INVALID PLAY FUNCTION");
}

void GameState::play(GameInstance inInstance)
{
	SetCursorPos(player.transform.pos.x, player.transform.pos.y);
	GetCursorPos(cursorPos);

	instance = inInstance;

	xBound = instance.width;
	yBound = instance.height;

	baseInit(W, H, xBound, yBound);

	nextState = EState::GAME;

	isWin = false;
	cursorLock = false;
	lockTimer = 0.f;
	releaseTimer = 0.f;
	points = 0;
	currentTime = timeLimit = instance.timeLimit * 60;
	
	player.team.color = instance.color1;
	player.team.teamNum = 1;
	player.transform.pos = vec2{ 0,0 };
	player.transform.rotAngle = 0;
	player.rigidbody.velocity = vec2{ 0,0 };

	ball.transform.pos = player.transform.pos - vec2{ 0, 100 };
	ball.rigidbody.velocity = vec2{ 0,0 };
	ball.team = player.team;

	cap.clear();
	for (int i = 0; i < instance.ballNum; i++)
	{
		CaptureBall temp;
		temp.team;
		cap.push_back(temp);
	}

	
	for (int i = 0; i < instance.ballNum; i++)
	{
		float x = rand() % (xBound * 2) - xBound;
		float y = rand() % (yBound * 2) - yBound;

		cap[i].transform.pos = vec2{ x,y };
		cap[i].transform.rotAngle = rand();		
	}
}

void GameState::tick()
{
}

void GameState::tick(float deltaTime, vec2 &cam)
{
	
	if (timeLimit > 0 && currentTime <= 0)
	{
		isWin = false;
		return;
	}
	currentTime -= deltaTime;


	for (int i = 0; i < instance.ballNum; i++)
	{
		if (cap[i].team.teamNum != player.team.teamNum)
		{
			isWin = false;
			break;
		}
		isWin = true;
	}
	
	if (isWin) 
		return;



	RECT rect;

	hwnd = FindWindow(0, "ColorBall");
	GetWindowRect(hwnd, &rect);

	float midX = rect.left + (W / 2);
	float midY = rect.top + (H / 2);

	GetCursorPos(cursorPos);
	float turnAngle = 0;

	if ((cursorPos[0].x != midX || cursorPos[0].y != midY) && !releaseCursor)
	{
		
		vec2 mousePos = { cursorPos[0].x, cursorPos[0].y };
		vec2 mid = { midX, midY };

		if (mousePos.x > mid.x)
			turnAngle = -dist(mid, mousePos);
		else if (mousePos.x < mid.x)
			turnAngle = dist(mid, mousePos);

		SetCursorPos(midX, midY);	
	}
	

	
	if (getKey('R') && releaseTimer <= 0)
	{
	
		releaseCursor = releaseCursor ? false : true;
		SetCursorPos(midX, midY);
		releaseTimer = .5f;
	}
	if (releaseTimer >= 0)
		releaseTimer -= deltaTime;

	if (getKey('Q'))
	{
		nextState = ENTER_MENU;
	}

	
	if (getKey('P'))
	{
		player.transform.pos = vec2{ 0,0 };
		player.rigidbody.velocity = vec2{ 0,0 };
		cam = vec2{ 0,0 };
	}

	
	points = 0;

	PlayerBallCollision(player, ball);

	for (int i = 0; i < instance.ballNum; i++)
	{
		cap[i].update(deltaTime, *this);
		BallPointCollision(ball, cap[i]);

		if (cap[i].team.teamNum == player.team.teamNum)
			points += 1;
	}

	for (int i = 0; i < 4; i++)
	{
		BoundCollision(player, bounds[i], .6);
		BoundCollision(ball, bounds[i], .8);

		for (int j = 0; j < instance.ballNum; j++)
			BoundCollision(cap[j], bounds[i], .8);
	}	
	
	

	for (int i = 0; i < 4; i++)
		cap[i].update(deltaTime, *this);

	ball.update(deltaTime, *this);
	cam = player.transform.pos;
	player.update(deltaTime, turnAngle, player.transform.rotAngle);
	camera.update(deltaTime, cam, *this);
}

void GameState::draw()
{
	if (isWin)
		return;	

	mat3 cam = camera.getCameraMatrix();
	player.draw(cam);
	
	
	for (int i = 0; i < instance.ballNum; i++)
		cap[i].draw(cam);
		
	

	releaseCursor ? drawString(font, "OPEN", (W / 2) - 32, H - 5, 16, 16, 0, '\0', GREEN) : drawString(font, "LOCKED", (W / 2) - 48, H - 5, 16, 16, 0, '\0', RED);

	
	drawString(font, "Time Left: ", 25, H - 5, 14, 14);

	string timer_print = to_string(currentTime);
	timeLimit > 0 ?
		drawString(font, timer_print.c_str(), 180, H - 5, 16, 16) :
		drawString(font, "\354", 180, H - 5, 14, 14);



}

EState GameState::next()
{
	if((timeLimit >= 0 && currentTime <= 0) || isWin)
		nextState = EState::ENTER_END;
	return nextState;
}
