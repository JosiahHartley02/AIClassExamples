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

	void onCollision(Character* other);
	void start() override;
	void update(float deltaTime) override;
	void draw() override;

	void setTarget(Actor* target) override;
	void setVisionAngle(float degrees) { m_visionAngle = degrees * (3.14159265359f / 180); }
private:
	EnemyState m_currentState;
	WanderBehavior* m_wander;
	SeekBehavior* m_seek;
	float m_visionAngle;
};
