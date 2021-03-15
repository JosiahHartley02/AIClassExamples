#include "Enemy.h"
#include "Game.h"

Enemy::Enemy(float x, float y, float collisionRadius, const char* spriteFilePath, Agent* target, float health, float damage, float maxSpeed, float maxForce)
	: Character(x, y, collisionRadius, spriteFilePath, health, damage, maxSpeed, maxForce)
{
	setTarget(target);
}

void Enemy::update(float deltaTime)
{
	Character::update(deltaTime);

}