#include "HUD.h"
#include <Base/AttackAble.h>
#include <Base/AbleToAttack.h>
#include "Defensive/DefensiveManager.h"
#include "Enemy/EnemyManager.h"
HUD::HUD()
{
}

HUD::~HUD()
{
}

void HUD::ChangeSubject(std::shared_ptr<BaseObject> obj)
{
	m_hitpoint = std::dynamic_pointer_cast<AttackAble>(obj)->GetHitPoint();
	m_maxHitpoint = std::dynamic_pointer_cast<AttackAble>(obj)->GetMaxHitPoint();
	m_attackDamage = std::dynamic_pointer_cast<AbleToAttack>(obj)->GetDamage();
	m_attackRange = std::dynamic_pointer_cast<AbleToAttack>(obj)->GetRange();
	m_attackSpeed = std::dynamic_pointer_cast<AbleToAttack>(obj)->GetAttackSpeed();
}

bool HUD::HandleTouchEvents(GLint x, GLint y, bool bIsPressed)
{
	for (auto& enemy:EnemyPoolManager::GetInstance()->flyEnemyList)
	{
		if (enemy->HandleTouchEvents(x, y, bIsPressed)) {
			ChangeSubject(std::dynamic_pointer_cast<BaseObject>(enemy));
			return true;
		}
	}
	for (auto& enemy : EnemyPoolManager::GetInstance()->groundEnemyList)
	{
		if (enemy->HandleTouchEvents(x, y, bIsPressed)) {
			ChangeSubject(std::dynamic_pointer_cast<BaseObject>(enemy));
			return true;
		}
	}
	for (auto& tower : DefensivePoolManager::GetInstance()->unMoveThroughAbleTowerList)
	{
		if (tower->HandleTouchEvents(x, y, bIsPressed)) {
			ChangeSubject(std::dynamic_pointer_cast<BaseObject>(tower));
			return true;
		}
	}
	if (DefensivePoolManager::GetInstance()->mainTower->HandleTouchEvents(x, y, bIsPressed)) {
		ChangeSubject(std::dynamic_pointer_cast<BaseObject>(DefensivePoolManager::GetInstance()->mainTower));
		return true;
	}
	return false;
}

void HUD::Draw()
{

}
