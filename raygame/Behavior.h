#pragma once
#include "raylib.h"

class Agent;

//Abstract class for all behaviors
class Behavior
{
public:
	virtual void update(Agent* agent, float deltaTime) = 0;
	virtual void draw(Agent* agent) {};
	float m_forceValue;
	void setForce(float value) { m_forceValue = value; }
	float getForce() { return m_forceValue; }
};