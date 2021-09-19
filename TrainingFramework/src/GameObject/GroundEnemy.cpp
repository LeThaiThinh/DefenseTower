#include "GroundEnemy.h"
#include "BaseObject.h"

std::shared_ptr<AttackAble> GroundEnemy::FindTarget()
{
	return 0;
}

void GroundEnemy::Move()
{
	if (m_target->GetHitPoint() <= 0) {
		m_target = nullptr;

	}
}

void GroundEnemy::Attack()
{
}

void GroundEnemy::Update(float deltaTime)
{
	Animation2D::Update(deltaTime);
	AbleToAttack::Update(deltaTime);
	m_currentTimeFindTarget += deltaTime;
	if (m_currentTimeFindTarget >= timeFindTarget) {
		FindTarget();
	}
}
