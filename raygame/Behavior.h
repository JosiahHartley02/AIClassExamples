#pragma once
#include "raylib.h"
#include <Vector2.h>

class Agent;

//Abstract class for all behaviors
class Behavior
{
public:
	virtual void update(Agent* agent, float deltaTime) = 0;
	virtual void draw(Agent* agent) {};
	void setForce(float value) { m_forceValue = value; }
	float getForce() { return m_forceValue; }
	void setSteeringForce(MathLibrary::Vector2 vector) { m_steeringForce = vector; }
	MathLibrary::Vector2 getSteeringForce() { return m_steeringForce; }
	bool getEnabled() { return m_enable; }
	void setEnabled(bool enable) { m_enable = enable; }
private:
	float m_forceValue;
	MathLibrary::Vector2 m_steeringForce;
	bool m_enable = true;
};