#include "WanderBehavior.h"
#include "Agent.h"
#include "Actor.h"

WanderBehavior::WanderBehavior()
{
	m_target = nullptr;
	m_wanderForce = 1;
}

WanderBehavior::WanderBehavior(Actor* target, float wanderForce)
{
	m_target = target;
	m_wanderForce = wanderForce;
}

MathLibrary::Vector2 WanderBehavior::calculateForce(Agent* agent)
{
	//Find the direction to move in
	MathLibrary::Vector2 direction = MathLibrary::Vector2::normalize(m_target->getWorldPosition() - agent->getWorldPosition());
	//Scale the direction vector by the seekForce
	MathLibrary::Vector2 desiredVelocity = direction * m_wanderForce;
	//Subtract current velocity from desired velocity to find steering force
	MathLibrary::Vector2 steeringForce = desiredVelocity - agent->getVelocity();
	return steeringForce;
}

void WanderBehavior::update(Agent* agent, float deltaTime)
{
	if (agent)
		agent->addForce(calculateForce(agent));
}
