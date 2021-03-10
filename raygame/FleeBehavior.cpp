#include "FleeBehavior.h"
#include "Agent.h"
#include "Actor.h"

FleeBehavior::FleeBehavior()
{
	m_target = nullptr;
	setForce(1);
	m_socialDistance = 0;
}

FleeBehavior::FleeBehavior(Actor* target, float seekForce)
{
	m_target = target;
	setForce(seekForce);
	m_socialDistance = 0;
}

FleeBehavior::FleeBehavior(Actor* target, float fleeForce, float socialDistancing)
{
	m_target = target;
	setForce(fleeForce);
	m_socialDistance = socialDistancing;
}

MathLibrary::Vector2 FleeBehavior::calculateForce(Agent* agent)
{
	//Find the direction to move in
	MathLibrary::Vector2 direction = MathLibrary::Vector2::normalize(agent->getWorldPosition() - m_target->getWorldPosition());
	//Scale the direction vector by the seekForce
	MathLibrary::Vector2 desiredVelocity = direction * getForce();
	//Subtract current velocity from desired velocity to find steering force
	m_steeringForce = desiredVelocity - agent->getVelocity();
	return  m_steeringForce;
}

void FleeBehavior::update(Agent* agent, float deltaTime)
{
	if(agent)
		agent->addForce(calculateForce(agent));	
}

void FleeBehavior::draw(Agent* agent)
{
	//Draw the steering force
	DrawLine(agent->getWorldPosition().x * 32,
		agent->getWorldPosition().y * 32,
		agent->getWorldPosition().x * 32 + (m_steeringForce.x * 32),
		agent->getWorldPosition().y * 32 + (m_steeringForce.y * 32),
		GREEN);
	DrawLine(agent->getWorldPosition().x * 32,
		agent->getWorldPosition().y * 32,
		m_target->getWorldPosition().x * 32,
		m_target->getWorldPosition().y * 32,
		RED);
}
