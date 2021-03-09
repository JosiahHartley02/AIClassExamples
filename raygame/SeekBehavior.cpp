#include "SeekBehavior.h"
#include "Agent.h"
#include "Actor.h"

SeekBehavior::SeekBehavior()
{
	m_target = nullptr;
	m_socialDistance = 0;
}

SeekBehavior::SeekBehavior(Actor* target,float seekForce)
{
	m_target = target; setForceScale(1);
	m_socialDistance = 0;
}

SeekBehavior::SeekBehavior(Actor* target, float seekForce, float socialDistancing)
{
	m_target = target;
	setForceScale(seekForce);
	m_socialDistance = socialDistancing;
}

MathLibrary::Vector2 SeekBehavior::calculateForce(Agent* agent)
{
	//Find the direction to move in
	MathLibrary::Vector2 direction = MathLibrary::Vector2::normalize(m_target->getWorldPosition() - agent->getWorldPosition());
	//Scale the direction vector by the seekForce
	m_desiredVelocity = direction * getForceScale();
	//Subtract current velocity from desired velocity to find steering force
	MathLibrary::Vector2 steeringForce = m_desiredVelocity - agent->getVelocity();
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

void SeekBehavior::draw(Agent* agent)
{
	//Draw Line between this and target
	DrawLine(agent->getWorldPosition().x * 32,
		agent->getWorldPosition().y * 32,
		m_target->getWorldPosition().x * 32,
		m_target->getWorldPosition().y * 32,
		PINK);
	//Draw The Desired Velocity
	DrawLine((agent->getWorldPosition().x * 32),
		(agent->getWorldPosition().y * 32), 
		(agent->getWorldPosition().x * 32) + (m_desiredVelocity.x * 32),
		(agent->getWorldPosition().y * 32) + (m_desiredVelocity.x * 32),		
		PINK);
}
