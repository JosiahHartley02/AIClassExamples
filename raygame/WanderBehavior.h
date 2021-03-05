#pragma once
#include "SteeringBehavior.h"

class Actor;

class WanderBehavior : public SteeringBehavior
{
public:
	WanderBehavior();
	WanderBehavior(Actor* target, float seekForce = 1);

	Actor* getTarget() { return m_target; }
	void setTarget(Actor* target) { m_target = target; }

	MathLibrary::Vector2 calculateForce(Agent* agent) override;
	void update(Agent* agent, float deltaTime) override;
private:
	//The agent that the behavior is seeking
	Actor* m_target;
	float m_wanderForce;
};

