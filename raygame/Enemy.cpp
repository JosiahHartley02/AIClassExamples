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

	//Checks if the enemy goes outside the bounds of the screen.
	//If so the enemy is teleported to the other side
	if (getWorldPosition().x > Game::getScreenWidth() / 32)
		setWorldPostion(MathLibrary::Vector2(0, getWorldPosition().y));
	if (getWorldPosition().x < 0)
		setWorldPostion(MathLibrary::Vector2(Game::getScreenWidth() / 32, getWorldPosition().y));
	if (getWorldPosition().x > Game::getScreenHeight() / 32)
		setWorldPostion(MathLibrary::Vector2(0, getWorldPosition().y));
	if (getWorldPosition().x < 0)
		setWorldPostion(MathLibrary::Vector2(Game::getScreenHeight() / 32, getWorldPosition().y));

}