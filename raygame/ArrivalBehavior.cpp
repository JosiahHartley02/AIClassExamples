#include "ArrivalBehavior.h"
#include "Agent.h"
#include "Actor.h"

ArrivalBehavior::ArrivalBehavior()
{
	m_target = nullptr;
	m_arrivalForce = 1;
}

ArrivalBehavior::ArrivalBehavior(Actor* target, float arrivalForce, float radius)
{
	m_target = target;
	m_arrivalForce = arrivalForce;
	m_radius = radius;
}

MathLibrary::Vector2 ArrivalBehavior::calculateForce(Agent* agent)
{
	//Find the direction to move in
	MathLibrary::Vector2 distance = MathLibrary::Vector2(m_target->getWorldPosition() - agent->getWorldPosition());
	//Scale the direction vector by the seekForce
	MathLibrary::Vector2 desiredVelocity = MathLibrary::Vector2::normalize(distance / m_radius) * m_arrivalForce;
	//Subtract current velocity from desired velocity to find steering force
	MathLibrary::Vector2 steeringForce = desiredVelocity - agent->getVelocity();
	return steeringForce;
}

void ArrivalBehavior::update(Agent* agent, float deltaTime)
{
	if (agent)
			agent->addForce(calculateForce(agent));
}
