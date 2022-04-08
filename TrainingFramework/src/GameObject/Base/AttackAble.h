#pragma once
#include <CMath.h>
#include "Sprite2D.h"
#include "ResourceManagers.h"
#define StandardHitpoint 1000.f
#define StandardHitPointBarWidth 80.f
#define StandardHitPointBarHeight 8.f
class AttackAble
{
protected:
	float	m_hitpoint;
	float	m_maxHitPoint;
	float	m_regen;
	std::list<std::weak_ptr<BaseObject>> m_attackedList;
	std::shared_ptr<Sprite2D> m_hitpointBar;
	std::shared_ptr<Sprite2D> m_lostHitpointBar;
	Vector2 m_hitpointBarMaxSize;
	std::shared_ptr<Texture> m_avatar;

public:
	AttackAble() :m_hitpoint(0), m_maxHitPoint(1), m_hitpointBarMaxSize(Vector2(0, 0)) {}
	AttackAble(float hitpoint, float maxHitPoint) :m_hitpoint(hitpoint), m_maxHitPoint(maxHitPoint), m_regen(0),
		//m_hitpointBarMaxSize(Vector2(std::sqrt(m_maxHitPoint/StandardHitpoint)*StandardHitPointBarWidth,std::sqrt(m_maxHitPoint/StandardHitpoint)*StandardHitPointBarHeight)),
		m_hitpointBar(std::make_shared<Sprite2D>(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"), ResourceManagers::GetInstance()->GetShader("TextureShader"), ResourceManagers::GetInstance()->GetTexture("UI/bar_4.tga"))),
		m_lostHitpointBar(std::make_shared<Sprite2D>(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"), ResourceManagers::GetInstance()->GetShader("TextureShader"), ResourceManagers::GetInstance()->GetTexture("UI/bar_bg.tga")))
	{
		m_hitpointBarMaxSize = Vector2(std::sqrt(m_maxHitPoint / StandardHitpoint) * StandardHitPointBarWidth, std::sqrt(m_maxHitPoint / StandardHitpoint) * StandardHitPointBarHeight);
		m_hitpointBar->SetISize(hitpoint / maxHitPoint * m_hitpointBarMaxSize.x, hitpoint / maxHitPoint * m_hitpointBarMaxSize.y);
		m_lostHitpointBar->SetISize((1 - hitpoint / maxHitPoint) * m_hitpointBarMaxSize.x, (1 - hitpoint / maxHitPoint) * m_hitpointBarMaxSize.y);
	}
	~AttackAble() {}

	void		TakeDamage(float damage) { m_hitpoint -= damage; }
	void		SetHitPoint(float hitpoint) { m_hitpoint = hitpoint; UpdateHitPointBarAndLostHitpointBarSize(); }
	void		SetMaxHitPoint(float hitpoint) { m_maxHitPoint = hitpoint; }
	float		GetHitPoint() { return m_hitpoint; }
	float		GetMaxHitPoint() { return m_maxHitPoint; }

	void		Draw() { m_lostHitpointBar->Draw(); m_hitpointBar->Draw(); }
	void		Update(float deltaTime) { 
		if (m_hitpoint < m_maxHitPoint) {
			m_hitpoint += m_regen * deltaTime;
			if (m_hitpoint > m_maxHitPoint) 
				m_hitpoint = m_maxHitPoint;
		}
	}
	void		UpdateHitPointBarAndLostHitpointBarPosition(float x, float y) {
		m_hitpointBar->Set2DPosition(x - (m_hitpointBarMaxSize.x - std::floor(m_hitpoint / m_maxHitPoint * m_hitpointBarMaxSize.x)) / 2, y);
		m_lostHitpointBar->Set2DPosition(x, y);
	}
	void		UpdateHitPointBarAndLostHitpointBarSize() {
		m_hitpointBar->SetISize(std::ceil(m_hitpoint / m_maxHitPoint * m_hitpointBarMaxSize.x), m_hitpointBarMaxSize.y);
		m_lostHitpointBar->SetISize(m_hitpointBarMaxSize.x, m_hitpointBarMaxSize.y);
	}
	bool	IsDestroyed() { return m_hitpoint <= 0; }
	void	AddEnemyIsAttacking(std::shared_ptr<BaseObject> attacker) {
		bool exist = false;
		for (auto &i : m_attackedList) {
			if (i.lock() == attacker)
				exist = true;
		}
		if (!exist)m_attackedList.push_back(attacker);
	}
	void	RemoveEnemyIsAttacking(std::shared_ptr<BaseObject> attacker) {
		for (auto &i = m_attackedList.begin(); i != m_attackedList.end(); ++i)
			if (i->lock() == attacker) {
				m_attackedList.erase(i);
				break;
			}
	};
	std::list<std::weak_ptr<BaseObject>> GetEnemyIsAttacking() { return m_attackedList; }
	void	ClearAttackingEnemyList() { m_attackedList.clear(); }
	void SetAvatar(std::shared_ptr<Texture> avatar) { m_avatar = avatar; }
	std::shared_ptr<Texture> GetAvatar() { return m_avatar; }
};
