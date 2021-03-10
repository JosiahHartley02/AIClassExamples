#include "Character.h"

Character::Character()
{
	m_damage = 0;
	m_health = 0;
}

Character::Character(float x, float y, float collisionRadius, const char* spriteFilePath, float health, float damage, float m_maxSpeed, float maxForce)
	: Agent(x, y, collisionRadius, spriteFilePath, health, damage)
{
	m_health = health;
	m_damage = damage;
}