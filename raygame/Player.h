#pragma once
#include "Actor.h"
#include "Agent.h"


class Player : public Agent
{
public:
	Player() : Agent() {}
	Player(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed = 1,float maxForce = 1);
	void update(float deltatime) override;
	void debug() override;
};
