#include "EnemyThree.h"
#include "Defensive/DefensiveManager.h"

EnemyThree::EnemyThree(float x, float y) :GroundEnemy(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"),
	ResourceManagers::GetInstance()->GetShader("AnimationShader"),
	ResourceManagers::GetInstance()->GetTexture("Enemy/enemy_three_walk_left.tga"), ResourceManagers::GetInstance()->GetTexture("Enemy/enemy_three_walk_right.tga"),
	6, 6, 0.5f, x, y, 110, 110, 100, 100, 20, 0, 1.f, 6,
	0.3f, Vector3(0, 0, 0), ResourceManagers::GetInstance()->GetTexture("Enemy/enemy_three_attack_left.tga"), ResourceManagers::GetInstance()->GetTexture("Enemy/enemy_three_attack_right.tga"),
	3, 3, 0.1f, 100, EnemyType::EnemyThree, 2)
{
	SetName("Tongue");
	SetAvatar(ResourceManagers::GetInstance()->GetTexture("Enemy/enemy_three_avatar.tga"));
}

EnemyThree::~EnemyThree()
{
}

void EnemyThree::SpawnBullet()
{
	std::dynamic_pointer_cast<UnMoveThroughAbleTower>(m_target)->TakeDamage(m_damage);
	if (std::dynamic_pointer_cast<UnMoveThroughAbleTower>(m_target)->GetHitPoint() <= 0) {
		DefensivePoolManager::GetInstance()->Add(m_target->GetPosition().x, m_target->GetPosition().y, TowerType::Spot);
		DefensivePoolManager::GetInstance()->RemoveUnmoveInstant(std::dynamic_pointer_cast<BaseDefensive>(m_target));
	}
}
