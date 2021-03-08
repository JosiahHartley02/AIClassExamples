#include "WanderBehavior.h"
#include "Agent.h"
#include "Actor.h"

WanderBehavior::WanderBehavior()
{
	m_target = MathLibrary::Vector2(NULL,NULL);
	m_wanderForce = 1;
	m_jitter = 1;
}

WanderBehavior::WanderBehavior(float wanderForce, float radius, float jitter)
{
	m_target = MathLibrary::Vector2(0,0);
	m_wanderForce = wanderForce;
	m_radius = radius;
	m_jitter = jitter;
}

MathLibrary::Vector2 WanderBehavior::calculateForce(Agent* agent)
{
	//create a random degree between 0 and 360 then converts it to radians
	float theta = (rand() / (RAND_MAX / 360)) * (3.14159265359/180);	
	//Start with Random Target somewhere congruent with the radius of this agent
	MathLibrary::Vector2 randomTarget = MathLibrary::Vector2((cos(theta) * m_radius), (sin(theta) * m_radius));
	//Add a random vector to the the Random Target with a magnitude specified by a jitter amount
	theta = (rand() / (RAND_MAX / 360)) * (3.14159265359 / 180);
	randomTarget = MathLibrary::Vector2(randomTarget.x + cos(theta) * m_jitter, randomTarget.y + sin(theta) * m_jitter);
	//Bring the Random Target to be congruent with the perimeter of the radius by normalizing and scaling by radius
	randomTarget = (randomTarget / randomTarget.getMagnitude()) * m_radius;
	//Add the agents current vector multiplied by a random distance to the random target
	theta = rand() / (RAND_MAX / 15);
	randomTarget = randomTarget + (agent->getForward() * theta);
	//Return the random target
	return randomTarget;
}

void WanderBehavior::update(Agent* agent, float deltaTime)
{
	if (agent)
		agent->addForce(calculateForce(agent));
}
