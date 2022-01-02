#include "FlyEnemy.h"
#include "BaseObject.h"
#include "DefensiveManager.h"
void FlyEnemy::FindPath()
{
	std::shared_ptr<UnMoveThroughAbleTower> target = std::dynamic_pointer_cast<UnMoveThroughAbleTower>(m_target);
	m_nextMove = target->GetCenterPosition();
}

void FlyEnemy::Update(float deltaTime)
{
	BaseEnemy::Update(deltaTime);
	if (std::dynamic_pointer_cast<UnMoveThroughAbleTower>(m_target)->GetHitPoint() <= 0) {
		m_target = nullptr;
	}
	Move(deltaTime);
}
