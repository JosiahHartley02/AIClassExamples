#pragma once
#include "Enemy.h"

enum EnemyState
{
	WANDER,
	SEEK
};

class WanderBehavior;
class SeekBehavior;

class SimpleEnemy : public Enemy
{
	using Enemy::Enemy;
	bool checkTargetInSight();

	void onCollision(Actor* other) override;
	void start() override;
	void update(float deltaTime) override;

	void setTarget(Actor* target) override;
private:
	EnemyState m_currentState;
	WanderBehavior* m_wander;
	SeekBehavior* m_seek;
};

