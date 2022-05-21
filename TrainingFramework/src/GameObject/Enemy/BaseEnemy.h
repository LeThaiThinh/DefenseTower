#pragma once
#include "Base/Animation2D.h"
#include "Base/MoveAble.h"
#include "Base/AbleToAttack.h"
#include "Base/AttackAble.h"
#include "Base/BountyObject.h"
#include "Defensive/DefensiveManager.h"
#include "../GameStates/GSMenu.h"
enum class EnemyType {
	EnemyOne,
	EnemyTwo,
	EnemyThree,
};
class BaseEnemy :
	public Animation2D,
	public MoveAble,
	public AbleToAttack,
	public AttackAble,
	public BountyObject
{
public:
	BaseEnemy() :m_type(EnemyType::EnemyOne) {
		m_typeObject = "Enemy";
	}
	BaseEnemy(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> textureLeft, std::shared_ptr<Texture> textureRight, int numFrame, int numFramesInLine, float frameTime,
		float x, float y, int iwidth, int iheight, int width, int height, float speed, float range, float attackSpeed, float damage,float delayAttackTime, Vector3 bulletSpawner, 
		std::shared_ptr<Texture> attackLeftAnimation, std::shared_ptr<Texture> attackRightAnimation, int numFrameAttack, int numFramesInLineAttack, float frameTimeAttack, float hitPoint, EnemyType type,int bounty)
		:Animation2D(model, shader, textureLeft, numFrame, numFramesInLine, frameTime, x, y, iwidth, iheight, width, height),
		MoveAble(speed,textureLeft,textureRight,numFrame,numFramesInLine,frameTime), 
		AttackAble((GSMenu::difficulty * 0.2f + 0.8f)* hitPoint,(GSMenu::difficulty * 0.2f + 0.8f)*hitPoint), BountyObject(bounty+ Upgrade::GetInstance()->upgradeList.find("Upgrade Resource")->second->GetLevel()*1),
		AbleToAttack(range, attackSpeed,(GSMenu::difficulty*0.2f+0.8f)*damage,delayAttackTime,bulletSpawner, attackLeftAnimation,attackRightAnimation,numFrameAttack,numFramesInLineAttack,frameTimeAttack), m_type(type)
		,m_isHolding(false)
	{
		m_typeObject = "Enemy";
	}
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
		//	if target is targeted  
		if (target) {
			//if in range able to attack then attack
			if (CheckCollideTarget(deltaTime) || (m_range > 0 && (target->GetCenterPosition() - m_centerPosition).Length() <= m_range + target->GetHeight() / 2.f + m_height / 2.f)) {
				m_isAttacking = true;
				if (CanAttack()) {
					Attack();
				}
				m_wayPointList.clear();
			}
			//if closed at goal
			else if (!m_wayPointList.empty()) {
				if ((m_wayPointList.front() - m_position).Length() <= deltaTime * m_speed)
				{
					SetPosition(m_wayPointList.front());
					SetDirection(Vector3(0, 0, 0));
					m_wayPointList.pop_front();
				}
				//if not at goal
				else {
					SetDirection((m_wayPointList.front() - m_position).Normalize());
					Move(deltaTime);
					if (m_currentTimeAttack > 1 / m_attackSpeed)
						m_currentTimeAttack = 1 / m_attackSpeed;
				}
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
		m_isAttacking = false;
		m_isCastingAttack = false;
		for (auto& tower : m_attackedList) {
			std::dynamic_pointer_cast<AbleToAttack>(tower.lock())->Untarget();
		}
		m_attackedList.clear();
		if (m_target) {
			std::dynamic_pointer_cast<AttackAble>(m_target)->RemoveEnemyIsAttacking(shared_from_this());
			m_target.reset();
		}
		m_wayPointList.clear();
	};

	virtual void Draw() { Animation2D::Draw(); };
	void DrawHUD() { AttackAble::Draw(); }
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
				m_target = towerMin;
				FindPath();
			}
			else if (m_target && m_target == towerMin) {
				
			}
			else if (m_target && m_target != towerMin) {
				std::dynamic_pointer_cast<UnMoveThroughAbleTower>(m_target)->RemoveEnemyIsAttacking(std::dynamic_pointer_cast<BaseEnemy>(shared_from_this()));
				towerMin->AddEnemyIsAttacking(std::dynamic_pointer_cast<BaseEnemy>(shared_from_this()));
				m_target = towerMin;
				FindPath();
			}
		}
		return towerMin;
	};

	virtual void SpawnBullet() = 0;

	std::shared_ptr<UnMoveThroughAbleTower> GetTarget() { return std::dynamic_pointer_cast<UnMoveThroughAbleTower>(m_target); }

	bool CheckCollideTarget(GLfloat deltaTime)
	{
		std::shared_ptr<UnMoveThroughAbleTower> target = std::dynamic_pointer_cast<UnMoveThroughAbleTower>(m_target);
		if(target)
			if ((target->GetCenterPosition().x + target->GetWidth() / 2.f > m_position.x - m_width / 2.f ) && (target->GetCenterPosition().x - target->GetWidth() / 2.f < m_position.x + m_width / 2.f)
				&& (target->GetCenterPosition().y + target->GetHeight() / 2.f > m_position.y - m_height / 2.f) && (target->GetCenterPosition().y - target->GetHeight() / 2.f < m_position.y  + m_height / 2.f))
			{
				return true;
			}
		return false;
	}

	bool HandleTouchHUD(GLint x, GLint y, bool bIsPressed) {
		bool m_isHandled = false;
		if (bIsPressed)
		{
			if (CheckCollision::PointInRect(Vector3(x,y,0),std::dynamic_pointer_cast<Sprite2D>(shared_from_this())))
			{
				// The button is being pressed down
				m_isHolding = true;
			}
		}
		else
		{
			if (CheckCollision::PointInRect(Vector3(x, y, 0), std::dynamic_pointer_cast<Sprite2D>(shared_from_this()))
				&& m_isHolding == true)
			{
				// Only perform click action when the same button was pressed down and released
				m_isHandled = true;
			}
			m_isHolding = false;
		}
		return m_isHandled;
	}

protected:
	bool m_isHolding;
	std::list<Vector3> m_wayPointList;
	EnemyType m_type;
};