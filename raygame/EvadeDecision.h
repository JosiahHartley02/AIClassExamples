#pragma once
#include "Decision.h"
class EvadeDecision :
    public Decision
{
    void makeDecision(Agent* agent, float deltaTime) override;
};

