#include "Character.h"

Character::Character(float x, float y, float collisionRadius, const char* spriteFilePath, float health, float damage, float m_maxSpeed, float maxForce)
	: Agent(x,y,collisionRadius,spriteFilePath,health,damage)
{
	m_health = health;
	m_damage = damage;
}
