#pragma once
#include "Behavior.h"
#include <Vector2.h>

class SteeringBehavior : public Behavior
{
public:
	virtual MathLibrary::Vector2 calculateForce(Agent* agent) = 0;
};