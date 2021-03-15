#pragma once
#include "Decision.h"

class ABDecision : public Decision
{
public:
    ABDecision(Decision* left = nullptr, Decision* right = nullptr);

    void makeDecision(Agent* agent, float deltaTime) override;
    virtual bool checkCondition(Agent* agent, float deltaTime) { return false; }
    Decision* getLeft() { return m_left; }
    Decision* getRight() { return m_right; }

private:
    Decision* m_left;
    Decision* m_right;
};