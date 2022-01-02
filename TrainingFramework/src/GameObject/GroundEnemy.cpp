#include "GroundEnemy.h"
#include "BaseObject.h"
#include "CheckCollision.h"

void GroundEnemy::FindPath()
{
	//if line connect target and subject not intersect any spot tower , next move is the target position
	float min = 10000;
	Vector3 nextMove;
	bool find = false;
	//&& (start.x != m_nextMove.x || start.y != m_nextMove.y)
	std::shared_ptr<UnMoveThroughAbleTower> target = std::dynamic_pointer_cast<UnMoveThroughAbleTower>(m_target);
	std::list<std::shared_ptr<BaseDefensive>> intersectSpots;
	for (auto &spot : DefensivePoolManager::GetInstance()->spotList) {
		if (CheckCollision::LineIntersectsRect(m_position, target->GetCenterPosition(), std::dynamic_pointer_cast<Sprite2D>(spot))) {
			//intersectSpots.push_back(spot);
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

void GroundEnemy::Update(float deltaTime)
{
	BaseEnemy::Update(deltaTime);

}


