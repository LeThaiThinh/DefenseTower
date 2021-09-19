#include "FlyEnemy.h"
#include "BaseObject.h"

std::shared_ptr<AttackAble> FlyEnemy::FindTarget()
{
	return std::make_shared<AttackAble>();
}

void FlyEnemy::Move()
{
}

void FlyEnemy::Attack()
{
}

void FlyEnemy::Update(float deltaTime)
{
	Animation2D::Update(deltaTime);
	AbleToAttack::Update(deltaTime);
	m_currentTimeFindTarget += deltaTime;
	if (m_currentTimeFindTarget >= timeFindTarget) {
		FindTarget();
	}
}
