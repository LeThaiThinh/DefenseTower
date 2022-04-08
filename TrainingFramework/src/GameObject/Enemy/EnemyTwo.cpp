#include "EnemyTwo.h"
#include "Bullet/BulletManager.h"

EnemyTwo::EnemyTwo(float x, float y) :GroundEnemy(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"),
	ResourceManagers::GetInstance()->GetShader("AnimationShader"),
	ResourceManagers::GetInstance()->GetTexture("Enemy/enemy_two_walk_left.tga"), ResourceManagers::GetInstance()->GetTexture("Enemy/enemy_two_walk_right.tga"),
	6, 6, 0.5f, x, y, 30, 30, 25, 25, 60, 150.f, 1.f, 6.f,  
	0.2f,Vector3(0,0,0), ResourceManagers::GetInstance()->GetTexture("Enemy/enemy_two_attack_left.tga"), ResourceManagers::GetInstance()->GetTexture("Enemy/enemy_two_attack_right.tga"),
	3, 3, 0.1f,100, EnemyType::EnemyTwo,2)
{
	SetName("Bomber");
	SetAvatar(ResourceManagers::GetInstance()->GetTexture("Enemy/enemy_two_avatar.tga"));
}

EnemyTwo::~EnemyTwo()
{
}

void EnemyTwo::SpawnBullet()
{
	BulletPoolManager::GetInstance()->AddBullet(
		BulletType::Target_Enemy_Two, std::dynamic_pointer_cast<BaseObject>(m_target),
		Vector3(0, 0, 0), shared_from_this());
}
