#include "WanderBehavior.h"
#include "Agent.h"
#include "Actor.h"

WanderBehavior::WanderBehavior()
{
	m_target = MathLibrary::Vector2(NULL,NULL);
	setForceScale(1);
	m_jitter = 1;
}

WanderBehavior::WanderBehavior(float wanderForce, float radius, float jitter)
{
	m_target = MathLibrary::Vector2(0,0);
	setForceScale(wanderForce);
	m_radius = radius;
	m_jitter = jitter;
}

MathLibrary::Vector2 WanderBehavior::calculateForce(Agent* agent)
{
	//create a random degree between 0 and 360 then converts it to radians
	float theta = (rand() / (RAND_MAX / 360)) * (3.14159265359/180);	
	//Start with Random Target somewhere congruent with the radius of this agent
	m_randPerPos = MathLibrary::Vector2((cos(theta) * m_radius), (sin(theta) * m_radius));
	//Add a random vector to the the Random Target with a magnitude specified by a jitter amount
	theta = (rand() / (RAND_MAX / 360)) * (3.14159265359 / 180);
	m_randVectorPos = MathLibrary::Vector2(m_randPerPos.x + cos(theta) * m_jitter, m_randPerPos.y + sin(theta) * m_jitter);
	//Bring the Random Target to be congruent with the perimeter of the radius by normalizing and scaling by radius
	m_randPerPosNew = (m_randVectorPos / m_randVectorPos.getMagnitude()) * m_radius;
	//Add the agents current vector multiplied by a random distance to the random target
	m_randDist = rand() / (RAND_MAX / 11);
	m_randDistPos = m_randPerPosNew + (agent->getForward() * m_randDist);
	//Return the random target
	return m_randDistPos;
}

void WanderBehavior::update(Agent* agent, float deltaTime)
{
	if (agent)
		agent->addForce(calculateForce(agent));
}

void WanderBehavior::draw(Agent* agent)
{
	//Draw White Circle to display radius
	DrawCircle(agent->getWorldPosition().x * 32,
		agent->getWorldPosition().y * 32,
		m_radius * 32,
		WHITE);
	//Draw Black Circle To Give White Circle Perimeter look
	DrawCircle(agent->getWorldPosition().x * 32,
		agent->getWorldPosition().y * 32,
		(m_radius * 32) - 2,
		BLACK);
	//Draw the circle of potential places for the new target to be in
	DrawCircle((agent->getWorldPosition().x * 32) + (agent->getForward().x * m_randDist * 32),
		(agent->getWorldPosition().y * 32) + (agent->getForward().y * m_randDist * 32),
		m_radius * 32,
		WHITE);
	//Draw the circle of potential places for the new target to be in
	DrawCircle((agent->getWorldPosition().x * 32) + (agent->getForward().x * m_randDist * 32),
		(agent->getWorldPosition().y * 32) + (agent->getForward().y * m_randDist * 32),
		(m_radius * 32) - 2,
		BLACK);
	//Draw The Random Position on the Perimeter of the Agents Radius
	DrawCircle((agent->getWorldPosition().x * 32) + (m_randPerPos.x * 32),
		(agent->getWorldPosition().y * 32) + (m_randPerPos.y * 32),
		3,
		RED);
	//Draw The Random Vector Applied to the Random Position
	DrawLine((agent->getWorldPosition().x * 32) + (m_randPerPos.x * 32),
		(agent->getWorldPosition().y * 32) + (m_randPerPos.y * 32),
		(agent->getWorldPosition().x * 32) + (m_randPerPos.x * 32) + (m_randVectorPos.x * 32),
		(agent->getWorldPosition().y * 32) + (m_randPerPos.y * 32) + (m_randVectorPos.y * 32),
		ORANGE);
	//Draw The New Target Result
	DrawCircle((agent->getWorldPosition().x * 32) + (m_randPerPos.x * 32) + (m_randVectorPos.x * 32),
		(agent->getWorldPosition().y * 32) + (m_randPerPos.y * 32) + (m_randVectorPos.y * 32),
		3,
		ORANGE);
	//Draw a vector to show the move to the new target to the perimeter
	DrawLine(((agent->getWorldPosition().x * 32) + (m_randPerPos.x * 32) + (m_randVectorPos.x * 32)),
		((agent->getWorldPosition().y * 32) + (m_randPerPos.y * 32) + (m_randVectorPos.y * 32)),
		((agent->getWorldPosition().x * 32) + (m_randPerPosNew.x * 32)),
		((agent->getWorldPosition().y * 32) + (m_randPerPosNew.y * 32)),
		YELLOW);
	//Draw the New Target to be on the perimeter
	DrawCircle((agent->getWorldPosition().x * 32) + (m_randPerPosNew.x * 32),
		(agent->getWorldPosition().y * 32) + (m_randPerPosNew.y * 32),
		3,
		YELLOW);
	//Draw a vector to show the new target multiplied by a random distance
	DrawLine((agent->getWorldPosition().x * 32) + (m_randPerPosNew.x * 32),
		(agent->getWorldPosition().y * 32) + (m_randPerPosNew.y * 32),
		(agent->getWorldPosition().x * 32) + (m_randDistPos.x * 32),
		(agent->getWorldPosition().y * 32) + (m_randDistPos.y * 32),
		GREEN);
	//Draw the New Target multiplied by the random distance
	DrawCircle((agent->getWorldPosition().x * 32) + (m_randDistPos.x * 32),
		(agent->getWorldPosition().y * 32) + (m_randDistPos.y * 32),
		3,
		GREEN);
}
