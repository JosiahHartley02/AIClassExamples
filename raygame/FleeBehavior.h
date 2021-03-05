#pragma once
#include "SteeringBehavior.h"

class Actor;

class FleeBehavior : public SteeringBehavior
{
public:
	FleeBehavior();
	FleeBehavior(Actor* target, float fleeForce = 1);
	/// <summary>
	/// This Initializer allows for the programmer to specift the distance they want the agent to maintain from the target 
	/// </summary>
	/// <param name="target">The actor that this agent wants to follow</param>
	/// <param name="fleeForce">the weight of how much this agent wants to flee from the target</param>
	/// <param name="socialDistancing">the distance that this agent wants to maintain, the actor will start fleeing when the
	///  social distance is less than the distance from target</param>
	FleeBehavior(Actor* target, float fleeForce, float socialDistancing);

	Actor* getTarget() { return m_target; }
	void setTarget(Actor* target) { m_target = target; }

	MathLibrary::Vector2 calculateForce(Agent* agent) override;
	void update(Agent* agent, float deltaTime) override;
private:
	//The agent that the behavior is seeking
	Actor* m_target;
	float m_fleeForce;
	float m_socialDistance;
};

