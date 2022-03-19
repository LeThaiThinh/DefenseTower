#include "FlyEnemy.h"
#include "Base/BaseObject.h"
#include "Defensive/DefensiveManager.h"
void FlyEnemy::FindPath()
{
	std::shared_ptr<UnMoveThroughAbleTower> target = std::dynamic_pointer_cast<UnMoveThroughAbleTower>(m_target);
	m_wayPointList.push_back(target->GetCenterPosition());
}

void FlyEnemy::Update(float deltaTime)
{
	BaseEnemy::Update(deltaTime);
	Move(deltaTime);
}
