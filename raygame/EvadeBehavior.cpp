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
	//Scale the direction vector by the evadeForce
	MathLibrary::Vector2 desiredVelocity = direction * getForce();
	//Subtract current velocity from desired velocity to find steering force
	setSteeringForce(desiredVelocity - agent->getVelocity());
	return  getSteeringForce();
}

void EvadeBehavior::update(Agent* agent, float deltaTime)
{
	if (agent)
			agent->addForce(calculateForce(agent));
}

void EvadeBehavior::draw(Agent* agent)
{
	//Draw a line between this agent and its target
	DrawLine(agent->getWorldPosition().x * 32,
		agent->getWorldPosition().y * 32,
		getTarget()->getWorldPosition().x * 32,
		getTarget()->getWorldPosition().y * 32,
		RED);
	//Draw the direction this agent wants to head
	DrawLine(agent->getWorldPosition().x * 32,
		agent->getWorldPosition().y * 32,
		agent->getWorldPosition().x * 32 + (getSteeringForce().x * 32),
		agent->getWorldPosition().y * 32 + (getSteeringForce().y * 32),
		GREEN);
}
