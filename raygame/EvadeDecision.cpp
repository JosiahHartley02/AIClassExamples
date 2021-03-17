#include "EvadeDecision.h"
#include "EvadeBehavior.h"
#include "PursueBehavior.h"
#include "WanderBehavior.h"
#include "ComplexEnemy.h"

void EvadeDecision::makeDecision(Agent* agent, float deltaTime)
{
	ComplexEnemy* enemy = dynamic_cast<ComplexEnemy*>(agent);
	if (enemy)
	{
		enemy->getPursue()->setEnabled(false);
		enemy->getWander()->setEnabled(true);
		enemy->getEvade()->setEnabled(true);
	}
}