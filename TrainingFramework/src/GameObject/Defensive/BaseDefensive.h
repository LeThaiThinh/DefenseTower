#pragma once
#include "Base/AttackAble.h"
#include "Base/AbleToAttack.h"
#include "Others/GameButton.h"
#include "Others/TowerOption.h"


class BaseEnemy;
class TowerOption;

enum class TowerType
{
	Spot,
	Main,
	One,
	Two,
	Three,
	Four,
	Five
};
class BaseDefensive :
	public AbleToAttack,
	public Sprite2D,
	public AttackAble,
{
public:
	BaseDefensive() :AbleToAttack(), Sprite2D(), AttackAble(), m_level(0), m_maxlevel(3), m_totalCost(0), m_costUpgrade(0), m_disposable(false), m_type(TowerType::Spot) {}
	BaseDefensive(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture,
		float x, float y, int iwidth, int iheight, int width, int height, float range, float attackSpeed, float damage, float delayAttackTime,Vector3 bulletSpawner, std::shared_ptr<Texture> attackLeftAnimation, std::shared_ptr<Texture> attackRightAnimation, int level, TowerType type, int maxlevel)
		:Sprite2D(model, shader, texture, x, y, iwidth, iheight, width, height), AttackAble(0,0),
		AbleToAttack(range, attackSpeed, damage, delayAttackTime, bulletSpawner, attackLeftAnimation, attackRightAnimation),
		m_level(level), m_disposable(false), m_totalCost(0), m_costUpgrade(0), m_type(type), m_maxlevel(maxlevel) {}
	BaseDefensive(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture,
		float x, float y, int iwidth, int iheight, int width, int height, float range, float attackSpeed, float damage, float delayAttackTime, Vector3 bulletSpawner, std::shared_ptr<Texture> attackLeftAnimation, std::shared_ptr<Texture> attackRightAnimation, int level, TowerType type, int maxlevel, float hitPoint, float maxHitPoint)
		:Sprite2D(model, shader, texture, x, y, iwidth, iheight, width, height), AttackAble(hitPoint, maxHitPoint),
		AbleToAttack(range, attackSpeed, damage, delayAttackTime, bulletSpawner, attackLeftAnimation, attackRightAnimation), m_level(level), m_disposable(false), m_totalCost(0), m_costUpgrade(0), m_type(type), m_maxlevel(maxlevel) {}
	~BaseDefensive() {}

	int GetTotalCost() { return m_totalCost; }
	int GetNextCost() { return m_costUpgrade; }

	TowerType GetType() { return m_type; }
	void SetType(TowerType type) { m_type = type; }
	bool IsDisposable() { return m_disposable; }
	void SetDisposable(bool disposable) { m_disposable = disposable; }
	void SetSecondOptionVisible(bool visible) { m_towerOption->SetSecondOptionVisible(visible); }

	virtual void Upgrade() { if (m_level < m_maxlevel) { m_level++; } }
	bool HandleTouchEvents(GLint x, GLint y, bool bIsPressed, std::shared_ptr<BaseDefensive> tower) { return m_towerOption->HandleTouchEvents(x, y, bIsPressed, tower); };
	virtual void	Draw() { Sprite2D::Draw(); AttackAble::Draw(); m_towerOption->Draw(); };
	virtual void	Attack() = 0;
	virtual void	Update(GLfloat deltatime) {
		Sprite2D::Update(deltatime);
		AbleToAttack::Update(deltatime);
		AttackAble::UpdateHitPointBarAndLostHitpointBarPosition(m_position.x, m_position.y - m_iHeight * static_cast<float>(2) / 3);
		AttackAble::UpdateHitPointBarAndLostHitpointBarSize();
		m_towerOption->Update(deltatime);
	};
	virtual void	LocateOption() = 0;
	virtual void	Reset() {
		m_totalCost = 0;
		m_level = 0;
		m_disposable = false;
		for (auto &enemy : m_attackedList) {
			std::dynamic_pointer_cast<AbleToAttack>(enemy.lock())->Untarget();
		}
		m_attackedList.clear();
		if (m_target) {
			std::dynamic_pointer_cast<AttackAble>(m_target)->RemoveEnemyIsAttacking(shared_from_this());
			m_target.reset();
		}
	};

protected:
	int m_totalCost;
	int m_costUpgrade;
	bool m_disposable;
	int m_level;
	int m_maxlevel;
	TowerType m_type;
	std::shared_ptr<TowerOption> m_towerOption;
};
