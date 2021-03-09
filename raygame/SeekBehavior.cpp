#include "SeekBehavior.h"
#include "Agent.h"
#include "Actor.h"

SeekBehavior::SeekBehavior()
{
	m_target = nullptr;
	setForce(1);
	m_socialDistance = 0;
}

SeekBehavior::SeekBehavior(Actor* target,float seekForce)
{
	m_target = target;
	setForce(seekForce);
	m_socialDistance = 0;
}

SeekBehavior::SeekBehavior(Actor* target, float seekForce, float socialDistancing)
{
	m_target = target;
	setForce(seekForce);
	m_socialDistance = socialDistancing;
}

MathLibrary::Vector2 SeekBehavior::calculateForce(Agent* agent)
{
	//Find the direction to move in
	MathLibrary::Vector2 direction = MathLibrary::Vector2::normalize(m_target->getWorldPosition() - agent->getWorldPosition());
	//Scale the direction vector by the seekForce
	MathLibrary::Vector2 desiredVelocity = direction * getForce();
	//Subtract current velocity from desired velocity to find steering force
	MathLibrary::Vector2 steeringForce = desiredVelocity - agent->getVelocity();
	return steeringForce;
}

void SeekBehavior::update(Agent* agent, float deltaTime)
{
	if (agent && m_target)
	{
		MathLibrary::Vector2 distance = (MathLibrary::Vector2(m_target->getWorldPosition() - agent->getWorldPosition()));
		if (distance.getMagnitude() > m_socialDistance)
			agent->addForce(calculateForce(agent));		
	}
}
