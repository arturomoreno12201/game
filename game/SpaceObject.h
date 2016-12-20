#pragma once
#include "PlanetRender.h"
#include "PlanetMotor.h"


struct SpaceObject
{
	Transform trans;
	RigidBody body;
	PlanetMotor motor;
	PlanetRender render;

	
	bool isOrigin;

	void init(vec2 transPos, vec2 transScl = vec2{ 0,0 }, float motorSpeed = 20.f, unsigned aColor = 0xffffffff, int aSize = 10, Transform* aParent = nullptr, bool aIsOrigin = false);

	void update(float deltaTime);
	void draw(const mat3 &t);
	
	void updateDraw(float deltaTime, const mat3 &t);
};