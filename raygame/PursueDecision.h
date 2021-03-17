#pragma once
#include "ABDecision.h"

class PursueDecision :
    public ABDecision
{
    void makeDecision(Agent* agent, float deltaTime) override;
};

