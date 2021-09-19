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
	float m_currentTimeAttack;
public:
	AbleToAttack() : m_range(0),m_attackSpeed(1),m_currentTimeAttack(0){}
	AbleToAttack(float range,float attackSpeed): m_range(range), m_attackSpeed(attackSpeed), m_currentTimeAttack(0){}
	~AbleToAttack() {}
	bool CanAttack() {
		return m_currentTimeAttack > 1 / m_attackSpeed;
	};
	virtual void Attack() = 0;
	void SetAttackSpeed(float attackSpeed) { m_attackSpeed = attackSpeed; }
	float GetAttackSpeed() { return m_attackSpeed; }
	void SetRange(float range) { m_range = range; }
	float GetRange() { return m_range; }
	void Update(float deltaTime) { m_currentTimeAttack += deltaTime; }
};