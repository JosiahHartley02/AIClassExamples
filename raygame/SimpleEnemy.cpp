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
    if (dotProductAngle < m_visionAngle)
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
    //Set the vision angle for simple enemy in degrees
    setVisionAngle(15);
}

void SimpleEnemy::update(float deltaTime)
{
    //Create a switch statement for the state machine
    switch (checkTargetInSight())
    {
        case false:        
            m_wander->setForce(100);
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
    //create a reference to looking right
    MathLibrary::Vector2 getRight = MathLibrary::Vector2(1, 0);
    //call dotproduct to see if simple enemy is looking right or left
    float dotProduct = MathLibrary::Vector2::dotProduct(getForward(), getRight);
    //get the angle from the forward vector
    float forwardAngle = atanf(getForward().y / getForward().x);
    //add the half of the actors total vision to get a positive angle
    float positiveAngle = forwardAngle + m_visionAngle;
    //add a full rotation minus half of the simple enemy total vision to get a negative angle
    float negativeAngle = forwardAngle + ((2*PI) - m_visionAngle);
    //check to see if the simple enemy is facing left
    if (dotProduct < 0)
    {
        //If it is, add 3.14 radians
        forwardAngle += PI;
        positiveAngle += PI;
        negativeAngle += PI;
    }

    Enemy::draw();

    if (checkTargetInSight())
    {
        DrawLine(getWorldPosition().x * 32,
            getWorldPosition().y * 32,
            getWorldPosition().x * 32 + cosf(positiveAngle) * 32 * 100,
            getWorldPosition().y * 32 + sinf(positiveAngle) * 32 * 100,
            GREEN);
        DrawLine(getWorldPosition().x * 32,
            getWorldPosition().y * 32,
            getWorldPosition().x * 32 + cosf(negativeAngle) * 32 * 100,
            getWorldPosition().y * 32 + sinf(negativeAngle) * 32 * 100,
            GREEN);
    }
    else
    {
        DrawLine(getWorldPosition().x * 32,
            getWorldPosition().y * 32,
            getWorldPosition().x * 32 + cosf(positiveAngle) * 32 * 100,
            getWorldPosition().y * 32 + sinf(positiveAngle) * 32 * 100,
            RED);
        DrawLine(getWorldPosition().x * 32,
            getWorldPosition().y * 32,
            getWorldPosition().x * 32 + cosf(negativeAngle) * 32 * 100,
            getWorldPosition().y * 32 + sinf(negativeAngle) * 32 * 100,
            RED);
    }
}

void SimpleEnemy::setTarget(Actor* target)
{
    Enemy::setTarget(target);
    m_seek->setTarget(target);
}