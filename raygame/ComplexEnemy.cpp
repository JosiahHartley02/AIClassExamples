#include "ComplexEnemy.h"
#include "DecisionBehavior.h"
#include "PursueBehavior.h"
#include "WanderBehavior.h"
#include "EvadeBehavior.h"
#include "Game.h"
void ComplexEnemy::start()
{
    Enemy::start();
    //retrives behavior from agent
    m_decision = getBehavior<DecisionBehavior>();
    m_pursue = getBehavior<PursueBehavior>();
    m_wander = getBehavior<WanderBehavior>();
    m_evade = getBehavior<EvadeBehavior>();

    //set target
    setTarget(Enemy::getTarget());
}

void ComplexEnemy::update(float deltaTime)
{
    Enemy::update(deltaTime);
    if (getHealth() <= 0)
        Game::destroy(this);
}



void ComplexEnemy::setTarget(Actor* agent)
{
    Enemy::setTarget(agent);
    m_pursue->setTarget(agent);
    m_evade->setTarget(agent);
}