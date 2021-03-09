#include "EvadeBehavior.h"
#include "Agent.h"
#include "Actor.h"

EvadeBehavior::EvadeBehavior()
{
	m_target = nullptr;
	setForce(1);
}

EvadeBehavior::EvadeBehavior(Actor* target, float seekForce)
{
	m_target = target;
	setForce(seekForce);
}
MathLibrary::Vector2 EvadeBehavior::calculateForce(Agent* agent)
{
	//Find the direction to move in
	MathLibrary::Vector2 direction = MathLibrary::Vector2::normalize((agent->getWorldPosition() + agent->getVelocity()) - m_target->getWorldPosition());
	//Scale the direction vector by the seekForce
	MathLibrary::Vector2 desiredVelocity = direction * getForce();
	//Subtract current velocity from desired velocity to find steering force
	MathLibrary::Vector2 steeringForce = desiredVelocity - agent->getVelocity();
	return  steeringForce;
}

void EvadeBehavior::update(Agent* agent, float deltaTime)
{
	if (agent)
			agent->addForce(calculateForce(agent));
}