#include "GroundEnemy.h"
#include "BaseObject.h"
#include "CheckCollision.h"

std::shared_ptr<UnMoveThroughAbleTower> GroundEnemy::FindTarget()
{
	std::shared_ptr<UnMoveThroughAbleTower> towerMin;
	for (auto tower : DefensivePoolManager::GetInstance()->unMoveThroughAbleTowerList) {
		if (!towerMin)
			towerMin = std::dynamic_pointer_cast<UnMoveThroughAbleTower>(tower);
		else
			if ((tower->GetPosition() - m_position).Length() < (towerMin->GetPosition() - m_position).Length())
				towerMin = std::dynamic_pointer_cast<UnMoveThroughAbleTower>(tower);
	}
	if (towerMin) {
		if (!m_target) {
			towerMin->AddEnemyIsAttacking(std::dynamic_pointer_cast<GroundEnemy>(shared_from_this()));
		}
		else if (m_target && m_target != towerMin) {
			std::dynamic_pointer_cast<UnMoveThroughAbleTower>(m_target)->RemoveEnemyIsAttacking(std::dynamic_pointer_cast<GroundEnemy>(shared_from_this()));
			towerMin->AddEnemyIsAttacking(std::dynamic_pointer_cast<GroundEnemy>(shared_from_this()));
		}
		m_target = towerMin;
		FindPath();
	}
	return towerMin;
}

void GroundEnemy::FindPath()
{
	//if line connect target and subject not intersect any spot tower , next move is the target position
	float min = 10000;
	Vector3 nextMove;
	bool find = false;
	//&& (start.x != m_nextMove.x || start.y != m_nextMove.y)
	std::shared_ptr<UnMoveThroughAbleTower> target = std::dynamic_pointer_cast<UnMoveThroughAbleTower>(m_target);
	std::list<std::shared_ptr<BaseDefensive>> intersectSpots;
	for (auto spot : DefensivePoolManager::GetInstance()->spotList) {
		if (CheckCollision::LineIntersectsRect(m_position, target->GetCenterPosition(), std::dynamic_pointer_cast<Sprite2D>(spot))) {
			intersectSpots.push_back(spot);
			Vector3 righttop = spot->GetRightTop() + Vector3(m_width / 2, -m_height / 2, 0);
			Vector3 lefttop = spot->GetLeftTop() + Vector3(-m_width / 2, -m_height / 2, 0);
			Vector3 rightbottom = spot->GetRightBottom() + Vector3(m_width / 2, m_height / 2, 0);
			Vector3 leftbottom = spot->GetLeftBottom() + Vector3(-m_width / 2, m_height / 2, 0);
			if (!CheckCollision::LineIntersectsRect(m_position, righttop, std::dynamic_pointer_cast<Sprite2D>(spot))
				&& (m_position - righttop).Length() + (target->GetCenterPosition() - righttop).Length() < min) {
				find = true;
				if ((m_start.x != righttop.x || m_position.y != righttop.y)) {
					nextMove = righttop;
					min = (m_position - righttop).Length() + (target->GetCenterPosition() - righttop).Length();
				}
			}
			if (!CheckCollision::LineIntersectsRect(m_position, lefttop, std::dynamic_pointer_cast<Sprite2D>(spot))
				&& (m_position - lefttop).Length() + (target->GetCenterPosition() - lefttop).Length() < min) {
				find = true;
				if ((m_start.x != lefttop.x || m_position.y != lefttop.y)) {
					nextMove = lefttop;
					min = (m_position - lefttop).Length() + (target->GetCenterPosition() - lefttop).Length();
				}
			}
			if (!CheckCollision::LineIntersectsRect(m_position, rightbottom, std::dynamic_pointer_cast<Sprite2D>(spot))
				&& (m_position - rightbottom).Length() + (target->GetCenterPosition() - rightbottom).Length() < min) {
				find = true;
				if ((m_start.x != rightbottom.x || m_position.y != rightbottom.y)) {
					nextMove = rightbottom;
					min = (m_position - rightbottom).Length() + (target->GetCenterPosition() - rightbottom).Length();
				}
			}
			if (!CheckCollision::LineIntersectsRect(m_position, leftbottom, std::dynamic_pointer_cast<Sprite2D>(spot))
				&& (m_position - leftbottom).Length() + (target->GetCenterPosition() - leftbottom).Length() < min) {
				find = true;
				if ((m_start.x != leftbottom.x || m_position.y != leftbottom.y)) {
					nextMove = leftbottom;
					min = (m_position - leftbottom).Length() + (target->GetCenterPosition() - leftbottom).Length();
				}
			}
			//m_nextMove = start;
		}
	}
	if (find) {
		m_nextMove = nextMove;
		//std::cout << m_nextMove.x << " " << m_nextMove.y << std::endl;
		//std::cout << target->GetCenterPosition().x << " " << target->GetCenterPosition().y << std::endl;
	}
	else {
		m_nextMove = target->GetCenterPosition();
		//std::cout << m_nextMove.x << " " << m_nextMove.y << std::endl;
		//std::cout << target->GetCenterPosition().x << " " << target->GetCenterPosition().y << std::endl;
	}
	return;
}

void GroundEnemy::Attack()
{
	m_currentTimeAttack -= 1 / m_attackSpeed;
}

void GroundEnemy::Update(float deltaTime)
{
	BaseEnemy::Update(deltaTime);
	std::shared_ptr<UnMoveThroughAbleTower> target = std::dynamic_pointer_cast<UnMoveThroughAbleTower>(m_target);

	//  if target is found but its hitpoint < 0 then find another, 
	//	else if target is not destroyed  
	if (target) {
		//if in range able to attack then attack
		if ((target->GetCenterPosition() - m_position).Length() <= m_range + target->GetHeight() / 3 || CheckCollideTarget(deltaTime)) {
			if (CanAttack()) {
				Attack();
			}
		}
		else if ((m_nextMove - m_position).Length() <= deltaTime * m_speed)
		{
			SetPosition(m_nextMove);
			m_start = m_nextMove;
			SetDirection(Vector3(0, 0, 0));
			FindPath();
		}
		else {
			SetDirection((m_nextMove - m_position).Normalize());
			Move(deltaTime);
			if (m_currentTimeAttack > 1 / m_attackSpeed)
				m_currentTimeAttack = 1 / m_attackSpeed;
		}
	}
	//find target when target not found
	else {
		FindTarget();
	}
}

bool GroundEnemy::CheckCollideTarget(GLfloat deltaTime)
{
	std::shared_ptr<UnMoveThroughAbleTower> target = std::dynamic_pointer_cast<UnMoveThroughAbleTower>(m_target);
	if ((target->GetCenterPosition().x + target->GetWidth() / 2 > m_position.x - m_width / 2 - deltaTime * m_speed * m_direction.x) && (target->GetCenterPosition().x - target->GetWidth() / 2 < m_position.x + m_width / 2 + deltaTime * m_speed * m_direction.x)
		&& (target->GetCenterPosition().y + target->GetHeight() / 2 > m_position.y - m_height / 2 - deltaTime * m_speed * m_direction.y) && (target->GetCenterPosition().y - target->GetHeight() / 2 < m_position.y + m_height / 2 + deltaTime * m_speed * m_direction.y))
	{
		return true;
	}
	return false;
}

