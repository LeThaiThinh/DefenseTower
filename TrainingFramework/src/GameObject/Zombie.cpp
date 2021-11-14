#include "Zombie.h"
#include "BulletManager.h"

Zombie::Zombie(float x, float y) :GroundEnemy(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"),
	ResourceManagers::GetInstance()->GetShader("AnimationShader"),
	ResourceManagers::GetInstance()->GetTexture("BuffaloMoveLeft.tga"),
	4, 4, 1.f, x, y, 30, 30, 30, 30, 40, 150, 1.f, 6, 100, EnemyType::Zombie)
{
}

Zombie::~Zombie()
{
}

void Zombie::Attack()
{
	GroundEnemy::Attack();
	BulletPoolManager::GetInstance()->AddBullet(
		BulletType::Target_Enemy, std::dynamic_pointer_cast<BaseObject>(m_target),
		Vector3(0, 0, 0), shared_from_this());
}
