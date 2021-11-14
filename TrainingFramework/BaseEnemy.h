#pragma once
#include "Animation2D.h"
#include "MoveAble.h"
#include "AbleToAttack.h"
#include "AttackAble.h"
#include "DefensiveManager.h"

enum class EnemyType {
	Buffalo,
	Zombie,
};
class BaseEnemy :
	public Animation2D,
	public MoveAble,
	public AbleToAttack,
	public AttackAble
{
public:
	BaseEnemy() :m_type(EnemyType::Buffalo) {}
	BaseEnemy(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int numFrame, int numFramesInLine, float frameTime,
		float x, float y, int iwidth, int iheight, int width, int height, float speed, float range, float attackSpeed, float damage, float hitPoint, EnemyType type)
		:Animation2D(model, shader, texture, numFrame, numFramesInLine, frameTime, x, y, iwidth, iheight, width, height),
		MoveAble(speed), AttackAble(hitPoint, hitPoint), AbleToAttack(range, attackSpeed, damage), m_type(type) {}
	~BaseEnemy() {}

	EnemyType GetType() { return m_type; }
	void SetType(EnemyType type) { m_type = type; }
	virtual void Draw() { Animation2D::Draw(); AttackAble::Draw(); };
	virtual std::shared_ptr<UnMoveThroughAbleTower> FindTarget() = 0;
	void Move(GLfloat deltaTime) {
		Set2DPosition(m_position.x + deltaTime * m_speed * m_direction.x, m_position.y + deltaTime * m_speed * m_direction.y);
	};
	virtual void Attack() = 0;
	void Update(GLfloat deltaTime) {
		Animation2D::Update(deltaTime);
		AbleToAttack::Update(deltaTime);
		AttackAble::UpdateHitPointBarAndLostHitpointBarSize();
		AttackAble::UpdateHitPointBarAndLostHitpointBarPosition(m_position.x, m_position.y - m_iHeight * 2 / 3);
	};
	std::shared_ptr<UnMoveThroughAbleTower> GetTarget() { return std::dynamic_pointer_cast<UnMoveThroughAbleTower>(m_target); }
	void Reset() {
		m_hitpoint = m_maxHitPoint;
		for (auto tower : m_attackedList) {
			std::dynamic_pointer_cast<AbleToAttack>(tower.lock())->Untarget();
		}
		m_attackedList.clear();
		if (m_target) {
			std::dynamic_pointer_cast<AttackAble>(m_target)->RemoveEnemyIsAttacking(shared_from_this());
			m_target.reset();
		}
	};
protected:
	Vector3 m_nextMove;
	EnemyType m_type;
};