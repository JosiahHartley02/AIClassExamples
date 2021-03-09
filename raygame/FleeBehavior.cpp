#include "FleeBehavior.h"
#include "Agent.h"
#include "Actor.h"

FleeBehavior::FleeBehavior()
{
	m_target = nullptr;
	m_socialDistance = 0;
}

FleeBehavior::FleeBehavior(Actor* target, float fleeForce)
{
	m_target = target;
	setForceScale(fleeForce);
	m_socialDistance = 0;
}

FleeBehavior::FleeBehavior(Actor* target, float fleeForce, float socialDistancing)
{
	m_target = target;
	setForceScale(fleeForce);
	m_socialDistance = socialDistancing;
}

MathLibrary::Vector2 FleeBehavior::calculateForce(Agent* agent)
{
	//Find the direction to move in
	MathLibrary::Vector2 direction = MathLibrary::Vector2::normalize(agent->getWorldPosition() - m_target->getWorldPosition());
	//Scale the direction vector by the seekForce
	MathLibrary::Vector2 desiredVelocity = direction * getForceScale();
	//Subtract current velocity from desired velocity to find steering force
	MathLibrary::Vector2 steeringForce = desiredVelocity - agent->getVelocity();
	return  steeringForce;
}

void FleeBehavior::update(Agent* agent, float deltaTime)
{
	if (agent && m_target)
	{
		MathLibrary::Vector2 distance = (MathLibrary::Vector2(m_target->getWorldPosition() - agent->getWorldPosition()));
		if (distance.getMagnitude() < m_socialDistance)
			agent->addForce(calculateForce(agent));
	}
}