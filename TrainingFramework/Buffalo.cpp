#include "Buffalo.h"


Buffalo::Buffalo(float x, float y) :GroundEnemy(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"),
	ResourceManagers::GetInstance()->GetShader("AnimationShader"),
	ResourceManagers::GetInstance()->GetTexture("BuffaloMoveLeft.tga"),
	4, 4, 1.f, x, y, 30, 30, 30, 30, 40, 0, 1.f, 6, 100, EnemyType::Buffalo)
{
}

Buffalo::~Buffalo()
{
}

void Buffalo::Attack()
{
	GroundEnemy::Attack();
	std::dynamic_pointer_cast<UnMoveThroughAbleTower>(m_target)->TakeDamage(m_damage);
	if (std::dynamic_pointer_cast<UnMoveThroughAbleTower>(m_target)->GetHitPoint() <= 0) {
		DefensivePoolManager::GetInstance()->Add(m_target->GetPosition().x, m_target->GetPosition().y, TowerType::Spot);
		DefensivePoolManager::GetInstance()->RemoveUnmoveInstant(std::dynamic_pointer_cast<BaseDefensive>(m_target));
	}
}
