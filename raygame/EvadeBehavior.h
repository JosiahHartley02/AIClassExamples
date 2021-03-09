#pragma once
#include "SteeringBehavior.h"

class Actor;

class EvadeBehavior : public SteeringBehavior
{
public:
	EvadeBehavior();
	EvadeBehavior(Actor* target, float evadeForce = 1);

	Actor* getTarget() { return m_target; }
	void setTarget(Actor* target) { m_target = target; }

	MathLibrary::Vector2 calculateForce(Agent* agent) override;
	void update(Agent* agent, float deltaTime) override;
	void draw(Agent* agent) override;
private:
	//The agent that the behavior is seeking
	Actor* m_target;
	MathLibrary::Vector2 m_desiredVelocity;
};

