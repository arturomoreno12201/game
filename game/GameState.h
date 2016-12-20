#pragma once
#include "State.h"
#include "PlayerShip.h"
#include "Camera.h"
#include "Asteroid.h"
#include "PlayerBall.h"
#include "CaptureBall.h"
#include "Boundary.h"
#include "GameInstance.h"


#include <string>
#include <vector>

#include <Windows.h>

using namespace std;


class GameState : public State
{
	
	void baseInit(int W_a, int H_a, int xBound_a, int yBound_a);

	float timeLimit, currentTime;
	int points;

public:
	GameState(std::string inTitle, unsigned inFont, int W_a = 600, int H_a = 600);
	~GameState();
	
	PlayerShip			player;
	Camera				camera;
	PlayerBall			ball;
	vector<CaptureBall>	cap;
	Boundary			bounds[4];

	
	bool cursorLock;
	bool isWin;
	float lockTimer;	
	int W, H;
	
	int xBound, yBound;
	string title;		
	GameInstance instance;

	HWND hwnd;
	POINT cursorPos[1];
	bool releaseCursor;
	float releaseTimer;


	void play();
	void play(GameInstance inInstance);
	void tick();
	void tick(float deltaTime, vec2 &cam);
	void draw();

	EState next();
};

