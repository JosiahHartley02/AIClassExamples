#include "Agent.h"
#include "Behavior.h"

Agent::Agent()
{
	m_force = { 0, 0 };
	m_maxForce = 1;
}

Agent::~Agent()
{

}

Agent::Agent(float x, float y, float collisionRadius, char icon, float maxSpeed, float maxForce) :
	Actor(x, y, collisionRadius, icon, maxSpeed)
{
	m_force = { 0, 0 };
	m_maxForce = maxForce;
}

Agent::Agent(float x, float y, float collisionRadius, Sprite* sprite, float maxSpeed, float maxForce) :
	Actor(x, y, collisionRadius, sprite, maxSpeed)
{
	m_force = { 0, 0 };
	m_maxForce = maxForce;
}

Agent::Agent(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed, float maxForce) :
	Actor(x, y, collisionRadius, spriteFilePath, maxSpeed)
{
	m_force = { 0, 0 };
	m_maxForce = maxForce;
}

void Agent::update(float deltatime)
{
	//Reset the force
	m_force = { 0,0 };
	//update each behavior
	for (int i = 0; i < m_behaviors.size(); i++)
		m_behaviors[i]->update(this, deltatime);
	//Set the new velocity to be the old velocitty plus the force of the behaviors
	setVelocity(getVelocity() + m_force * deltatime);
	//Update the icon to face the direction its moving
	updateFacing();
	//Call the base update
	Actor::update(deltatime);

}
void Agent::draw()
{
	for (int i = 0; i < m_behaviors.size(); i++)
		m_behaviors[i]->draw(this);
	Actor::draw();
}

void Agent::addForce(MathLibrary::Vector2 force)
{
	//Add the force given to the total force
	m_force = m_force + force;

	//TO DO: Update forces

	//If the total force is greater than the max force, set its magnitude to be the max force
	if (m_force.getMagnitude() > getMaxForce())
		m_force = m_force.getNormalized() * getMaxForce();
}

void Agent::addBehavior(Behavior* behavior)
{
	if(behavior)
		m_behaviors.push_back(behavior);
}
