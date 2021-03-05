#pragma once

class Agent;

//Abstract class for all behaviors
class Behavior
{
public:
	virtual void update(Agent* agent, float deltaTime) = 0;
};