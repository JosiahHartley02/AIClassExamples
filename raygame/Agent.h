#pragma once
#include "Actor.h"
#include <vector>

class Behavior;

class Agent : public Actor
{
public:
	Agent();
    ~Agent();
    /// <param name="x">Position on the x axis</param>
    /// <param name="y">Position on the y axis</param>
    /// <param name="icon">The symbol that will appear when drawn</param>
    /// <param name = "maxForce"> The largest the magnitude of the force vector can be</param>
    Agent(float x, float y, float collisionRadius, char icon, float maxSpeed, float maxForce);

    /// <param name="x">Position on the x axis</param>
    /// <param name="y">Position on the y axis</param>
    /// <param name="icon">The symbol that will appear when drawn</param>
    /// <param name = "maxForce"> The largest the magnitude of the force vector can be</param>
    Agent(float x, float y, float collisionRadius, Sprite* sprite, float maxSpeed, float maxForce);

    /// <param name="x">Position on the x axis</param>
    /// <param name="y">Position on the y axis</param>
    /// <param name="icon">The symbol that will appear when drawn</param>
    /// <param name = "maxForce"> The largest the magnitude of the force vector can be</param>
    Agent(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed, float maxForce);

    void update(float deltatime) override;
    void draw() override;

    float getMaxForce() { return m_maxForce; }
    void setMaxForce(float maxForce) { m_maxForce = maxForce; }
    
    //Add the given force to the total force that is being applied to the agent.
    void addForce(MathLibrary::Vector2 force);
    void addBehavior(Behavior* behavior);
    /// <summary>
   /// Returns the first behavior that matches the given type
   /// If no behavior matches the type, returns null.
   /// </summary>
   /// <typeparam name="BehaviorType"></typeparam>
   /// <returns></returns>
    template<typename BehaviorType>
    BehaviorType* getBehavior();
private:
	MathLibrary::Vector2 m_force;
	float m_maxForce;
	std::vector<Behavior*> m_behaviors;
};

template<typename BehaviorType>
inline BehaviorType* Agent::getBehavior()
{
    //Iterate through the list of behaviors
    for (int i = 0; i < m_behaviors.size(); i++)
    {
        //Attempt to cast behavior at the current index as the given type
        //casts a templeted behavior type variable as a dynamic cast of the templeted
        //behavior of the behavior at the index of i
        BehaviorType* behavior = dynamic_cast<BehaviorType*>(m_behaviors[i]);

        //If the cast is successful return the beavior that was found
        if (behavior)
            return behavior;
    }
    //If no behaviors were found to match the type, return null
    return nullptr;
}

