#include "GroundEnemy.h"
#include "Base/BaseObject.h"
#include "CheckCollision.h"
#include "Pathing/ObstacleManager.h"
#include "Pathing/FloydWarshall.h"
void GroundEnemy::FindPath()
{
	//
	if (m_wayPointList.empty() || (!m_wayPointList.empty() && !(m_target->GetPosition() == m_wayPointList.back()))) {
		m_wayPointList.clear();
		std::shared_ptr<WayPoint> startWayPoint;
		float minF = INFINITY;
		bool intersect = false;
		std::shared_ptr<WayPoint> endWayPoint;
		switch (m_width)
		{
		case 25:
			for (auto& obstacle : ObstacleManager::GetInstance()->obstacleList25) {
				if (!(obstacle->obs->GetCenterPosition() == m_target->GetPosition()) && CheckCollision::LineIntersectsRect(m_position, m_target->GetPosition(), obstacle->obs)) {
					intersect = true;
					break;
				}
			}
			for (auto& wayPoint : ObstacleManager::GetInstance()->wayPointGoalList25) {
				if (m_target->GetPosition() == wayPoint->wayPoint->GetPosition()) {
					endWayPoint = wayPoint;
				}
			}
			if (!intersect) {
				m_wayPointList.push_back(m_target->GetPosition());
			}
			else {
				for (auto& obstacle : ObstacleManager::GetInstance()->obstacleList25) {
					for (auto wayPoint : obstacle->wayPointList) {
						if ((m_position - wayPoint->wayPoint->GetPosition()).Length() < minF) {
							startWayPoint = wayPoint;
							minF = (m_position - wayPoint->wayPoint->GetPosition()).Length();
						}
					}
				}
				m_wayPointList = FloydWarshall::GetInstance()->constructPath25(startWayPoint, endWayPoint);
			}
			break;
		case 50:
			for (auto& obstacle : ObstacleManager::GetInstance()->obstacleList50) {
				if (!(obstacle->obs->GetCenterPosition() == m_target->GetPosition()) && CheckCollision::LineIntersectsRect(m_position, m_target->GetPosition(), obstacle->obs)) {
					intersect = true;
					break;
				}
			}
			for (auto& wayPoint : ObstacleManager::GetInstance()->wayPointGoalList50) {
				if (m_target->GetPosition() == wayPoint->wayPoint->GetPosition()) {
					endWayPoint = wayPoint;
				}
			}
			if (!intersect) {
				m_wayPointList.push_back(m_target->GetPosition());
			}
			else {
				for (auto& obstacle : ObstacleManager::GetInstance()->obstacleList50) {
					for (auto wayPoint : obstacle->wayPointList) {
						if ((m_position - wayPoint->wayPoint->GetPosition()).Length() < minF) {
							startWayPoint = wayPoint;
							minF = (m_position - wayPoint->wayPoint->GetPosition()).Length();
						}
					}
				}
				m_wayPointList = FloydWarshall::GetInstance()->constructPath50(startWayPoint, endWayPoint);
			}
			break;
		case 75:
			break;
		default:
			break;
		}
	}

}

std::list<Vector3> GroundEnemy::AStarAlgo25(std::shared_ptr<WayPoint> start, std::shared_ptr<WayPoint> end)
{
	std::list<Vector3> a;
	a.push_back(start->wayPoint->GetPosition());
	a.push_back(end->wayPoint->GetPosition());
	return a;
}

void GroundEnemy::Update(float deltaTime)
{

	BaseEnemy::Update(deltaTime);

}


