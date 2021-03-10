#pragma once
#include "Actor.h"
#include "Agent.h"
#include "Character.h"

class Player : public Character
{
public:
	Player() : Character() {}
	Player(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed = 1,float maxForce = 1);
	void update(float deltatime) override;
	void draw() override;
	void debug() override;
};

