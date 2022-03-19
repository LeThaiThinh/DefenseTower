#include "EnemyOne.h"
#include "Defensive/DefensiveManager.h"

EnemyOne::EnemyOne(float x, float y) :GroundEnemy(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"),
	ResourceManagers::GetInstance()->GetShader("AnimationShader"),
	ResourceManagers::GetInstance()->GetTexture("Enemy/enemy_one_walk_left.tga"), ResourceManagers::GetInstance()->GetTexture("Enemy/enemy_one_walk_right.tga"),
	6, 6, 0.5f, x, y, 60, 60, 50, 50, 40, 0, 1.f, 6,
	0.3f,Vector3(0,0,0), ResourceManagers::GetInstance()->GetTexture("Enemy/enemy_one_attack_left.tga"), ResourceManagers::GetInstance()->GetTexture("Enemy/enemy_one_attack_right.tga"),
	3,3,0.1f,100, EnemyType::EnemyOne,2)
{
}

EnemyOne::~EnemyOne()
{
}

void EnemyOne::SpawnBullet()
{
	std::dynamic_pointer_cast<UnMoveThroughAbleTower>(m_target)->TakeDamage(m_damage);
	if (std::dynamic_pointer_cast<UnMoveThroughAbleTower>(m_target)->GetHitPoint() <= 0) {
		DefensivePoolManager::GetInstance()->Add(m_target->GetPosition().x, m_target->GetPosition().y, TowerType::Spot);
		DefensivePoolManager::GetInstance()->RemoveUnmoveInstant(std::dynamic_pointer_cast<BaseDefensive>(m_target));
	}
}
