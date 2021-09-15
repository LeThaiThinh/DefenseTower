#pragma once
#include <CMath.h>
#include <list>
#include <Bullet.h>
#include <memory>
class AttackAble
{
protected:
	float m_range;
	float m_attackSpeed;
	float m_timeAttack;
	std::list<std::shared_ptr<Bullet>> m_bulletList;
public:
	AttackAble() :m_bulletList(NULL), m_range(0),m_attackSpeed(1),m_timeAttack(0){}
	~AttackAble() {}
	bool CanAttack() {
		return m_timeAttack > 1 / m_attackSpeed;
	};
	virtual void AttackLinear(Vector2 targetPosition)=0;
	virtual void AttackCircular()=0;
	void Update(float deltaTime) { m_timeAttack += deltaTime; }
};