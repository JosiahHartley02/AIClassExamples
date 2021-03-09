#include "ArrivalBehavior.h"
#include "Agent.h"
#include "Actor.h"
#include "raylib.h"

ArrivalBehavior::ArrivalBehavior()
{
	m_target = nullptr;
	setForceScale(1);
}

ArrivalBehavior::ArrivalBehavior(Actor* target, float arrivalForce, float radius)
{
	m_target = target;
	setForceScale(arrivalForce);
	m_radius = radius;
}

MathLibrary::Vector2 ArrivalBehavior::calculateForce(Agent* agent)
{
	//Find the direction to move in
	MathLibrary::Vector2 direction = MathLibrary::Vector2::normalize(m_target->getWorldPosition() - agent->getWorldPosition());
	float distance = MathLibrary::Vector2(m_target->getWorldPosition() - agent->getWorldPosition()).getMagnitude();
	//Scale the direction vector by the seekForce
	MathLibrary::Vector2 desiredVelocity = direction * getForceScale();
	//apply the arrival behavior
	if (m_radius > distance)
		desiredVelocity = desiredVelocity * (distance / m_radius);
	//Subtract current velocity from desired velocity to find steering force
	MathLibrary::Vector2 steeringForce = desiredVelocity - agent->getVelocity();
	return steeringForce;
}

void ArrivalBehavior::update(Agent* agent, float deltaTime)
{
	if (agent)
			agent->addForce(calculateForce(agent));
}
