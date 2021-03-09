#include "ArrivalBehavior.h"
#include "Agent.h"
#include "Actor.h"
#include "raylib.h"

ArrivalBehavior::ArrivalBehavior()
{
	m_target = nullptr;
	setForce(1);
}

ArrivalBehavior::ArrivalBehavior(Actor* target, float arrivalForce, float radius)
{
	m_target = target;
	setForce(arrivalForce);
	m_radius = radius;
}

MathLibrary::Vector2 ArrivalBehavior::calculateForce(Agent* agent)
{
	//Find the direction to move in
	MathLibrary::Vector2 direction = MathLibrary::Vector2::normalize(m_target->getWorldPosition() - agent->getWorldPosition());
	float distance = MathLibrary::Vector2(m_target->getWorldPosition() - agent->getWorldPosition()).getMagnitude();
	//apply the arrival behavior
	if (m_radius > distance)
		direction = (direction * (distance / m_radius )) * getForce();
	//Subtract current velocity from desired velocity to find steering force
	MathLibrary::Vector2 steeringForce = direction - agent->getVelocity();
	return steeringForce;
}

void ArrivalBehavior::update(Agent* agent, float deltaTime)
{
	if (agent)
			agent->addForce(calculateForce(agent));
}

void ArrivalBehavior::draw(Agent* agent)
{
	float distance = MathLibrary::Vector2(m_target->getWorldPosition() - agent->getWorldPosition()).getMagnitude();
	//Draw radius of this behavior
	DrawCircle(agent->getWorldPosition().x * 32,
		agent->getWorldPosition().y * 32,
		m_radius * 32,
		WHITE);
	DrawCircle(agent->getWorldPosition().x * 32,
		agent->getWorldPosition().y * 32,
		m_radius * 32 - 2,
		BLACK);

	//Illustrate The power of the force
	if (distance <= m_radius && distance !=0)
		DrawCircle(agent->getWorldPosition().x * 32,
			agent->getWorldPosition().y * 32,
			(m_radius - distance) * 32,
			GREEN);
	//Draw Line Between this actor and the target	
	DrawLine(agent->getWorldPosition().x * 32,
		agent->getWorldPosition().y * 32,
		getTarget()->getWorldPosition().x * 32,
		getTarget()->getWorldPosition().y * 32,
		GREEN);
}
