#pragma once
#include "Transform.h"
class Camera
{
public:
	Camera(int W = 600, int H = 600);
	~Camera();

	Transform	transform;
	mat3		proj;	

	mat3 getCameraMatrix() const; 
	void update(float deltaTime, const vec2 &movement, class GameState &gs);
};

