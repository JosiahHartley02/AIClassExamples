#pragma once
#include "SteeringBehavior.h"

class Actor;

class SeekBehavior : public SteeringBehavior
{
public:
	SeekBehavior();
	SeekBehavior(Actor* target, float seekForce = 1);
	/// <summary>
	/// This Initializer allows for the programmer to specify the distance they want the agent to maintain from the target
	/// </summary>
	/// <param name="target">the actor that this agent will follow from a distance</param>
	/// <param name="seekForce">the weight of how much this agent wants to follow the target</param>
	/// <param name="socialDistancing">This is the distance that the actor will maintain, the actor will stop seeking if too close</param>
	SeekBehavior(Actor* target, float seekForce, float socialDistancing);

	Actor* getTarget() { return m_target; }
	void setTarget(Actor* target) { m_target = target; }

	MathLibrary::Vector2 calculateForce(Agent* agent) override;
	void update(Agent* agent, float deltaTime) override;
	void draw(Agent* agent) override;
private:
	//The agent that the behavior is seeking
	Actor* m_target;
	float m_socialDistance;
};

