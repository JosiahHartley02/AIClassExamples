#include "PursueBehavior.h"
#include "Agent.h"
#include "Actor.h"

PursueBehavior::PursueBehavior()
{
	m_target = nullptr;
	setForce(1);
}

PursueBehavior::PursueBehavior(Actor* target, float pursueForce)
{
	m_target = target;
	setForce(pursueForce);
}

MathLibrary::Vector2 PursueBehavior::calculateForce(Agent* agent)
{
	//Find the direction to move in
	MathLibrary::Vector2 direction = MathLibrary::Vector2::normalize((m_target->getWorldPosition() + m_target->getVelocity()) - agent->getWorldPosition());
	//Scale the direction vector by the seekForce
	MathLibrary::Vector2 desiredVelocity = direction * getForce();
	//Subtract current velocity from desired velocity to find steering force
	m_steeringForce = desiredVelocity - agent->getVelocity();
	return m_steeringForce;
}

void PursueBehavior::update(Agent* agent, float deltaTime)
{
	if (agent)	
			agent->addForce(calculateForce(agent));
}

void PursueBehavior::draw(Agent* agent)
{
	//draw circle to illustrate targets velocity
	DrawCircle(m_target->getWorldPosition().x * 32 + (m_target->getVelocity().x * 32),
		m_target->getWorldPosition().y * 32 + (m_target->getVelocity().y * 32),
		4,
		RED);
	DrawCircle(m_target->getWorldPosition().x * 32 + (m_target->getVelocity().x * 32),
		m_target->getWorldPosition().y * 32 + (m_target->getVelocity().y * 32),
		3,
		BLACK);
	//draw line connecting this agent to the targets velocity
	DrawLine(agent->getWorldPosition().x * 32,
		agent->getWorldPosition().y * 32,
		m_target->getWorldPosition().x * 32 + (m_target->getVelocity().x * 32),
		m_target->getWorldPosition().y * 32 + (m_target->getVelocity().y * 32),
		RED);
	//draw line to represent the steering force applied
	DrawLine(agent->getWorldPosition().x * 32,
		agent->getWorldPosition().y * 32,
		(agent->getWorldPosition().x * 32) + (m_steeringForce.x * 32),
		(agent->getWorldPosition().y * 32) + (m_steeringForce.y * 32),
		BLUE);
}
