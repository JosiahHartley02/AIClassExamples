#include "WanderBehavior.h"
#include "Agent.h"
#include "Actor.h"

WanderBehavior::WanderBehavior()
{
	m_target = MathLibrary::Vector2(NULL,NULL);
	m_wanderForce = 1;
	m_jitter = 1;
}

WanderBehavior::WanderBehavior(MathLibrary::Vector2 target, float wanderForce, float radius)
{
	m_target = target;
	m_wanderForce = wanderForce;
	m_radius = radius;
	m_jitter = 1;
}

MathLibrary::Vector2 WanderBehavior::calculateForce(Agent* agent)
{
	//create a random degree between 0 and 360
	float theta = rand() / RAND_MAX/360;
	//Start with Random Target somewhere congruent with the radius of this agent
	m_target = MathLibrary::Vector2((cos(theta * m_radius)), (sin(theta * m_radius)));
	//Add a random vector to the the Random Target with a magnitude specified by a jitter amount
	theta = rand() / RAND_MAX / 360;
	m_target = MathLibrary::Vector2(m_target.x + cos(theta * m_jitter), m_target.y + sin(theta * m_jitter));
	//Bring the Random Target to be congruent with the perimeter of the radius by normalizing and scaling by radius
	//Add the agents current vector multiplied by a random distance to the random target
	//Return the random target
	return MathLibrary::Vector2();
}

void WanderBehavior::update(Agent* agent, float deltaTime)
{
	if (agent)
		agent->addForce(calculateForce(agent));
}
