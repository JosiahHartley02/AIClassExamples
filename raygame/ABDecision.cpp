#include "ABDecision.h"

ABDecision::ABDecision(Decision* left, Decision* right)
{
	m_left = left;
	m_right = right;
}

void ABDecision::makeDecision(Agent* agent, float deltaTime)
{
	if (checkCondition(agent, deltaTime))
		if (m_left)
			m_left->makeDecision(agent, deltaTime);
		else
			if (m_right)
				m_right->makeDecision(agent, deltaTime);
}