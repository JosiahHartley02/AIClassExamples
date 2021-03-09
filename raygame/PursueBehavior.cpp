#include "PursueBehavior.h"
#include "Agent.h"
#include "Actor.h"

PursueBehavior::PursueBehavior()
{
	m_target = nullptr;
	setForceScale(1);
}

PursueBehavior::PursueBehavior(Actor* target, float pursueForce)
{
	m_target = target;
	setForceScale(pursueForce);
}

MathLibrary::Vector2 PursueBehavior::calculateForce(Agent* agent)
{
	//Find the direction to move in
	MathLibrary::Vector2 direction = MathLibrary::Vector2::normalize(m_target->getWorldPosition() + m_target->getVelocity() - agent->getWorldPosition());
	//Scale the direction vector by the seekForce
	MathLibrary::Vector2 desiredVelocity = direction * getForceScale();
	//Subtract current velocity from desired velocity to find steering force
	MathLibrary::Vector2 steeringForce = desiredVelocity - agent->getVelocity();
	return steeringForce;
}

void PursueBehavior::update(Agent* agent, float deltaTime)
{
	if (agent)	
			agent->addForce(calculateForce(agent));
}
