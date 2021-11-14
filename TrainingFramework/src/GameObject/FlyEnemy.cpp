#include "FlyEnemy.h"
#include "BaseObject.h"

std::shared_ptr<UnMoveThroughAbleTower> FlyEnemy::FindTarget()
{
	std::shared_ptr<UnMoveThroughAbleTower> towerMin;
	for (auto tower : DefensivePoolManager::GetInstance()->unMoveThroughAbleTowerList) {
		if (!towerMin)
			towerMin = std::dynamic_pointer_cast<UnMoveThroughAbleTower>(tower);
		else
			if ((tower->GetPosition() - m_position).Length() < (towerMin->GetPosition() - m_position).Length())
				towerMin = std::dynamic_pointer_cast<UnMoveThroughAbleTower>(tower);
	}
	SetDirection(towerMin->GetPosition() - m_position);
	return towerMin;
}

void FlyEnemy::Attack()
{
}

void FlyEnemy::Update(float deltaTime)
{
	BaseEnemy::Update(deltaTime);
	if (std::dynamic_pointer_cast<UnMoveThroughAbleTower>(m_target)->GetHitPoint() <= 0) {
		m_target = nullptr;
	}
	Move(deltaTime);
}
