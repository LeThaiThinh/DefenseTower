#pragma once
#include <CMath.h>
#include <list>
#include <Bullet.h>
#include <memory>
class AbleToAttack
{
protected:
	float m_range;
	float m_attackSpeed;
	float m_timeAttack;
public:
	AbleToAttack() : m_range(0),m_attackSpeed(1),m_timeAttack(0){}
	AbleToAttack(float range,float attackSpeed): m_range(range), m_attackSpeed(attackSpeed), m_timeAttack(0){}
	~AbleToAttack() {}
	bool CanAttack() {
		return m_timeAttack > 1 / m_attackSpeed;
	};
	virtual void Attack() = 0;
	void Update(float deltaTime) { m_timeAttack += deltaTime; }
};