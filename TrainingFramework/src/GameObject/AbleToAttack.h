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
	float m_damage;
	std::shared_ptr<BaseObject> m_target;

public:
	AbleToAttack() : m_range(0), m_attackSpeed(1), m_currentTimeAttack(0), m_damage(0) {}
	AbleToAttack(float range, float attackSpeed, float damage) : m_range(range), m_attackSpeed(attackSpeed), m_currentTimeAttack(0), m_damage(damage) {}
	~AbleToAttack() {}

	bool CanAttack() { return m_currentTimeAttack > 1 / m_attackSpeed; };
	void SetAttackSpeed(float attackSpeed) { m_attackSpeed = attackSpeed; }
	float GetAttackSpeed() { return m_attackSpeed; }
	void SetRange(float range) { m_range = range; }
	float GetRange() { return m_range; }
	void SetDamage(float range) { m_damage = range; }
	float GetDamage() { return m_damage; }

	virtual void Attack() = 0;
	void Update(float deltaTime) { m_currentTimeAttack += deltaTime; }

	std::shared_ptr<BaseObject> GetTarget() { return m_target; }
	void Untarget() { m_target.reset(); }

};