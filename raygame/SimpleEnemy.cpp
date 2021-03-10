#include "SimpleEnemy.h"
#include "WanderBehavior.h"
#include "SeekBehavior.h"

bool SimpleEnemy::checkTargetInSight()
{
    //check if the target is null if so return false
    if (getTarget() == nullptr)
        return false;
    //find the direction vector that represents where the target is relative to the enemy
    MathLibrary::Vector2 direction = MathLibrary::Vector2::normalize(getTarget()->getWorldPosition() - getWorldPosition());
    //Find the dot product of the enemy's forward and the direction vector
    float dotProduct = MathLibrary::Vector2::dotProduct(getForward(), direction);
    //Find the angle using the dot product
    float dotProductAngle = acosf(dotProduct);
    //Check if that angle is greater than the enemy's viewing angle(any value you see fit is fine) (0.523599 = 30°)
    if (dotProductAngle < .7)
        //Return if the enemy saw the target
        return true;
    return false;
}

void SimpleEnemy::onCollision(Character * other)
{
    //Check to see if the enemy ran into the player
    if (checkCollision(other))
    {
        //If the enemy has run into the player, deal damage to the player
        other->takeDamage(1);
        //If the player's health is less than 0, set the target to be nullptr
        if (other->getHealth() == 0)
            setTarget(nullptr);
    }
}

    void SimpleEnemy::start()
{
    //Call the base start function
    Enemy::start();
    //Set the default state of the enemy
    m_currentState = WANDER;
    //Initialize member variables
    m_seek = getBehavior<SeekBehavior>();
    m_wander = getBehavior<WanderBehavior>();
    //Set the target to be the base class target
    setTarget(Enemy::getTarget());
}

void SimpleEnemy::update(float deltaTime)
{
    //Create a switch statement for the state machine
    switch (checkTargetInSight())
    {
        case false:        
            m_wander->setForce(1);
            m_seek->setForce(0);
            break;
        case true:
            m_seek->setForce(10);
            m_wander->setForce(0);
            break;
    }
    // BehaviorType* behavior = dynamic_cast<BehaviorType*>(m_behaviors[i]);
    onCollision(dynamic_cast<Character*>(getTarget()));
    Enemy::update(deltaTime);
}

void SimpleEnemy::draw()
{
    MathLibrary::Vector2 getRight = MathLibrary::Vector2(getWorldPosition().x + 1, getWorldPosition().y);
    float dotProduct = MathLibrary::Vector2::dotProduct(getForward(), getRight);
    float forwardVector = atanf(getForward().y / getForward().x);
    MathLibrary::Vector2 referenceVector = MathLibrary::Vector2(cosf(forwardVector), sinf(forwardVector));
    Enemy::draw();
    DrawLine(getWorldPosition().x * 32,
        getWorldPosition().y * 32,
        getWorldPosition().x * 32 + referenceVector.x * 32,
        getWorldPosition().y * 32 + referenceVector.x * 32,
        ORANGE);
    
}

void SimpleEnemy::setTarget(Actor* target)
{
    Enemy::setTarget(target);
    m_seek->setTarget(target);
}