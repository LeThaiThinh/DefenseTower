#pragma once
#include "Animation2D.h"
#include "MoveAble.h"
#include "AbleToAttack.h"
#include "AttackAble.h"
#include "BountyObject.h"
#include "DefensiveManager.h"
#include "../GameStates/GSMenu.h"
enum class EnemyType {
	EnemyOne,
	EnemyTwo,
};
class BaseEnemy :
	public Animation2D,
	public MoveAble,
	public AbleToAttack,
	public AttackAble,
	public BountyObject
{
public:
	BaseEnemy() :m_type(EnemyType::EnemyOne) {}
	BaseEnemy(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> textureLeft, std::shared_ptr<Texture> textureRight, int numFrame, int numFramesInLine, float frameTime,
		float x, float y, int iwidth, int iheight, int width, int height, float speed, float range, float attackSpeed, float damage,float delayAttackTime, Vector3 bulletSpawner, 
		std::shared_ptr<Texture> attackLeftAnimation, std::shared_ptr<Texture> attackRightAnimation, int numFrameAttack, int numFramesInLineAttack, float frameTimeAttack, float hitPoint, EnemyType type,int bounty)
		:Animation2D(model, shader, textureLeft, numFrame, numFramesInLine, frameTime, x, y, iwidth, iheight, width, height),
		MoveAble(speed,textureLeft,textureRight,numFrame,numFramesInLine,frameTime), 
		AttackAble((GSMenu::difficulty * 0.2 + 0.8)* hitPoint,(GSMenu::difficulty * 0.2 + 0.8)*hitPoint), BountyObject(bounty),
		AbleToAttack(range, attackSpeed,(GSMenu::difficulty*0.2+0.8)*damage,delayAttackTime,bulletSpawner, attackLeftAnimation,attackRightAnimation,numFrameAttack,numFramesInLineAttack,frameTimeAttack), m_type(type) {}
	~BaseEnemy() {}

	EnemyType GetType() { return m_type; }
	void SetType(EnemyType type) { m_type = type; }

	void Move(GLfloat deltaTime) {
		if (m_direction.x > 0 && !m_isCastingAttack)
			m_pTexture = m_walkRightAnimation;
		else if (m_direction.x < 0 && !m_isCastingAttack)
			m_pTexture = m_walkLeftAnimation;
		Set2DPosition(m_position.x + deltaTime * m_speed * m_direction.x, m_position.y + deltaTime * m_speed * m_direction.y);
	};
	void Attack() {
		m_currentTimeAttack -= 1 / m_attackSpeed;
		m_isCastingAttack = true;
		if ((m_target->GetPosition() - m_position).x < 0) {
			m_pTexture = m_attackLeftAnimation;
		}
		else {
			m_pTexture = m_attackRightAnimation;
		}
		m_frameTime = m_frameTimeAttack;
	};

	void Update(GLfloat deltaTime) {
		Animation2D::Update(deltaTime);
		AbleToAttack::Update(deltaTime);
		if (m_currentTimeAttack >= m_delayAttackTime / 2 && m_isCastingAttack) {
			m_isCastingAttack = false;
			if (m_target)
				SpawnBullet();
		}
		if (m_currentTimeAttack >= m_delayAttackTime) {
			m_frameTime = 0.5;
			if (m_pTexture == m_attackLeftAnimation) {
				m_pTexture = m_walkLeftAnimation;
			}
			else if (m_pTexture == m_attackRightAnimation) {
				m_pTexture = m_walkRightAnimation;
			}
		}
		AttackAble::UpdateHitPointBarAndLostHitpointBarSize();
		AttackAble::UpdateHitPointBarAndLostHitpointBarPosition(m_position.x, m_position.y - m_iHeight * static_cast<float>(2) / 3);
		std::shared_ptr<UnMoveThroughAbleTower> target = std::dynamic_pointer_cast<UnMoveThroughAbleTower>(m_target);

		//  if target is found but its hitpoint < 0 then find another, 
		//	else if target is not destroyed  
		if (target) {
			//if in range able to attack then attack
			if ((target->GetCenterPosition() - m_centerPosition).Length() <= m_range + target->GetHeight() / 2.f || CheckCollideTarget(deltaTime)) {
				m_isAttacking = true;
				if (CanAttack()) {
					Attack();
				}
			}
			else if ((m_nextMove - m_position).Length() <= deltaTime * m_speed)
			{
				SetPosition(m_nextMove);
				m_start = m_nextMove;
				SetDirection(Vector3(0, 0, 0));
				FindPath();
			}
			else {
				SetDirection((m_nextMove - m_position).Normalize());
				Move(deltaTime);
				if (m_currentTimeAttack > 1 / m_attackSpeed)
					m_currentTimeAttack = 1 / m_attackSpeed;
			}
		}
		//find target when target not found
		else {
			m_isAttacking = false;
			FindTarget();
		}
	}
	void Reset() {
		m_hitpoint = m_maxHitPoint;
		for (auto& tower : m_attackedList) {
			std::dynamic_pointer_cast<AbleToAttack>(tower.lock())->Untarget();
		}
		m_attackedList.clear();
		if (m_target) {
			std::dynamic_pointer_cast<AttackAble>(m_target)->RemoveEnemyIsAttacking(shared_from_this());
			m_target.reset();
		}
	};
	virtual void Draw() { Animation2D::Draw(); AttackAble::Draw(); };

	virtual void FindPath()=0;
	std::shared_ptr<UnMoveThroughAbleTower> FindTarget() {
		std::shared_ptr<UnMoveThroughAbleTower> towerMin;
		for (auto& tower : DefensivePoolManager::GetInstance()->unMoveThroughAbleTowerList) {
			if (!towerMin)
				towerMin = std::dynamic_pointer_cast<UnMoveThroughAbleTower>(tower);
			else
				if ((tower->GetPosition() - m_position).Length() < (towerMin->GetPosition() - m_position).Length())
					towerMin = std::dynamic_pointer_cast<UnMoveThroughAbleTower>(tower);
		}
		if (towerMin) {
			if (!m_target) {
				towerMin->AddEnemyIsAttacking(std::dynamic_pointer_cast<BaseEnemy>(shared_from_this()));
			}
			else if (m_target && m_target != towerMin) {
				std::dynamic_pointer_cast<UnMoveThroughAbleTower>(m_target)->RemoveEnemyIsAttacking(std::dynamic_pointer_cast<BaseEnemy>(shared_from_this()));
				towerMin->AddEnemyIsAttacking(std::dynamic_pointer_cast<BaseEnemy>(shared_from_this()));
			}
			m_target = towerMin;
			FindPath();
		}
		return towerMin;
	};
	virtual void SpawnBullet() = 0;

	std::shared_ptr<UnMoveThroughAbleTower> GetTarget() { return std::dynamic_pointer_cast<UnMoveThroughAbleTower>(m_target); }
	bool CheckCollideTarget(GLfloat deltaTime)
	{
		std::shared_ptr<UnMoveThroughAbleTower> target = std::dynamic_pointer_cast<UnMoveThroughAbleTower>(m_target);
		if(target)
			if ((target->GetCenterPosition().x + target->GetWidth() / 2.f > m_position.x - m_width / 2.f - deltaTime * m_speed * m_direction.x) && (target->GetCenterPosition().x - target->GetWidth() / 2.f < m_position.x + m_width / 2.f + deltaTime * m_speed * m_direction.x)
				&& (target->GetCenterPosition().y + target->GetHeight() / 2.f > m_position.y - m_height / 2.f - deltaTime * m_speed * m_direction.y) && (target->GetCenterPosition().y - target->GetHeight() / 2.f < m_position.y + m_height / 2.f + deltaTime * m_speed * m_direction.y))
			{
				return true;
			}
		return false;
	}
protected:
	Vector3 m_nextMove;
	Vector3 m_start;
	EnemyType m_type;
};