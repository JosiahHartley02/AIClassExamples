#pragma once
#include "SteeringBehavior.h"

class Actor;

class WanderBehavior : public SteeringBehavior
{
public:
	WanderBehavior();
	WanderBehavior(MathLibrary::Vector2 target, float wanderForce = 1, float radius = 1, float jitter = 1);

	MathLibrary::Vector2 calculateForce(Agent* agent) override;
	void update(Agent* agent, float deltaTime) override;
private:
	//The agent that the behavior is seeking
	MathLibrary::Vector2 m_target;
	float m_wanderForce;
	float m_radius;
	float m_jitter;
};