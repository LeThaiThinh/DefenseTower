#pragma once
#include <CMath.h>
#include <list>
#include "Bullet/Bullet.h"
class AbleToAttack
{
protected:
	float m_range;
	float m_attackSpeed;
	float m_currentTimeAttack;
	float m_damage;
	float m_delayAttackTime;
	bool m_isCastingAttack;
	bool m_isAttacking;
	Vector3 m_bulletSpawner;
	std::shared_ptr<Texture> m_attackLeftAnimation;
	std::shared_ptr<Texture> m_attackRightAnimation;
	int m_numFrameAttack,m_numFramesInLineAttack;
	float m_frameTimeAttack;
	std::shared_ptr<BaseObject> m_target;

public:
	AbleToAttack() : m_range(0), m_attackSpeed(1), m_currentTimeAttack(0), m_damage(0),m_delayAttackTime(0), m_bulletSpawner(Vector3(0,0,0)), m_isCastingAttack(false), m_isAttacking(false), m_numFrameAttack(0), m_numFramesInLineAttack(0), m_frameTimeAttack(0) {}
	AbleToAttack(float range, float attackSpeed, float damage, float delayAttackTime, Vector3 bulletSpawner, std::shared_ptr<Texture> attackLeftAnimation, std::shared_ptr<Texture> attackRightAnimation, int numFrames, int numFramesInLine, float frameTime)
		: m_range(range), m_attackSpeed(attackSpeed), m_currentTimeAttack(0), m_damage(damage),m_delayAttackTime(delayAttackTime), m_bulletSpawner(bulletSpawner),m_attackLeftAnimation(attackLeftAnimation),m_attackRightAnimation(attackRightAnimation), m_isCastingAttack(false), m_isAttacking(false), m_numFrameAttack(numFrames), m_numFramesInLineAttack(numFramesInLine), m_frameTimeAttack(frameTime) {}
	AbleToAttack(float range, float attackSpeed, float damage, float delayAttackTime, Vector3 bulletSpawner, std::shared_ptr<Texture> attackLeftAnimation, std::shared_ptr<Texture> attackRightAnimation)
		: m_range(range), m_attackSpeed(attackSpeed), m_currentTimeAttack(0), m_damage(damage),m_delayAttackTime(delayAttackTime), m_bulletSpawner(bulletSpawner),m_attackLeftAnimation(attackLeftAnimation),m_attackRightAnimation(attackRightAnimation), m_isCastingAttack(false), m_isAttacking(false), m_numFrameAttack(0), m_numFramesInLineAttack(0), m_frameTimeAttack(0) {}
	~AbleToAttack() {}
	
	bool CanAttack() { return m_currentTimeAttack > 1 / m_attackSpeed; };
	void SetAttackSpeed(float attackSpeed) { m_attackSpeed = attackSpeed; }
	float GetAttackSpeed() { return m_attackSpeed; }
	void SetRange(float range) { m_range = range; }
	float GetRange() { return m_range; }
	void SetDamage(float range) { m_damage = range; }
	float GetDamage() { return m_damage; }
	Vector3 GetBulletSpawner() { return m_bulletSpawner; }
	bool IsAttacking() { return m_isAttacking; }

	virtual void Attack() = 0;
	void Update(float deltaTime) {m_currentTimeAttack += deltaTime;}
	std::shared_ptr<BaseObject> GetTarget() { return m_target; }
	void Untarget() { m_target.reset(); }

};