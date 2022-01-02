#include "UnMoveThroughAbleTower.h"
#include "../Application.h"
#include "DefensiveManager.h"
#include "EnemyManager.h"
std::shared_ptr<BaseEnemy> UnMoveThroughAbleTower::FindEnemyTarget() {
	std::shared_ptr<BaseEnemy> enemyMin;
	float distanceMin = 10000;
	for (auto &enemy : DefensivePoolManager::GetInstance()->mainTower->GetEnemyIsAttacking())
	{
		std::shared_ptr<BaseEnemy> e = std::dynamic_pointer_cast<BaseEnemy>(enemy.lock());
		if ((e->GetCenterPosition() - GetPosition()).Length() <= m_range) {
			m_target = enemy.lock();
			return e;
		}
	}
	for (auto &enemy : m_attackedList) {
		std::shared_ptr<BaseEnemy> e = std::dynamic_pointer_cast<BaseEnemy>(enemy.lock());
		if ((e->GetCenterPosition() - GetPosition()).Length() <= m_range) {
			m_target = enemy.lock();
			return e;
		}
	}
	for (auto &enemy : EnemyPoolManager::GetInstance()->groundEnemyList) {
		float distance = (enemy->GetCenterPosition() - GetPosition()).Length();
		if (distance <= m_range && distance < distanceMin) {
			distanceMin = distance;
			enemyMin = enemy;
		}
	}
	m_target = enemyMin;
	return enemyMin;
}

void UnMoveThroughAbleTower::Update(GLfloat deltatime)
{
	BaseDefensive::Update(deltatime);
	if (!m_target) {
		FindEnemyTarget();
		if (m_target)
			std::dynamic_pointer_cast<BaseEnemy>(m_target)->AddEnemyIsAttacking(shared_from_this());
		if (m_currentTimeAttack > 1 / m_attackSpeed)
			m_currentTimeAttack = 1 / m_attackSpeed;
	}
	else if (m_target && CanAttack()) {
		Attack();
	}
}
void UnMoveThroughAbleTower::Attack() {
	m_currentTimeAttack -= 1 / m_attackSpeed;
}

void UnMoveThroughAbleTower::Reset()
{
	BaseDefensive::Reset();
}
