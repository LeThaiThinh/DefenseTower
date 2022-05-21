#include "GroundEnemy.h"
#include "Base/BaseObject.h"
#include "CheckCollision.h"
#include "Pathing/ObstacleManager.h"
#include "Pathing/FloydWarshall.h"
#include "GameObject/Timer.h"
void GroundEnemy::FindPath()
{
	/*if (m_width == 25) {
		Timer::GetInstance()->AddTimeOperation("GroundEnemy25");
	}
	else if (m_width == 50) {
		Timer::GetInstance()->AddTimeOperation("GroundEnemy50");
	}
	else if (m_width == 100) {
		Timer::GetInstance()->AddTimeOperation("GroundEnemy100");
	}*/
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
			//Timer::GetInstance()->AddTimeOperation("GroundEnemyConnect25");
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
				//Timer::GetInstance()->EndOperation("GroundEnemyConnect25");
			}
			else {
				for (auto& obstacle : ObstacleManager::GetInstance()->obstacleList25) {
					for (auto wayPoint : obstacle->wayPointList) {
						if ((m_position - wayPoint->wayPoint->GetPosition()).Length()  < minF && wayPoint->active 
							&& (CheckCollision::CheckLesser90Degree(std::dynamic_pointer_cast<Sprite2D>(shared_from_this()), wayPoint->wayPoint, endWayPoint->wayPoint))) {
							startWayPoint = wayPoint;
							minF = (m_position - wayPoint->wayPoint->GetPosition()).Length();
						}
					}
				}
				//Timer::GetInstance()->EndOperation("GroundEnemyConnect25");
				m_wayPointList = FloydWarshall::GetInstance()->constructPath25(startWayPoint, endWayPoint);
			}
			break;
		case 50:
			//Timer::GetInstance()->AddTimeOperation("GroundEnemyConnect50");
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
				//Timer::GetInstance()->EndOperation("GroundEnemyConnect50");
			}
			else {
				for (auto& obstacle : ObstacleManager::GetInstance()->obstacleList50) {
					for (auto wayPoint : obstacle->wayPointList) {
						if ((m_position - wayPoint->wayPoint->GetPosition()).Length()  < minF && wayPoint->active
							&& (CheckCollision::CheckLesser90Degree(std::dynamic_pointer_cast<Sprite2D>(shared_from_this()), wayPoint->wayPoint, endWayPoint->wayPoint))) {
							startWayPoint = wayPoint;
							minF = (m_position - wayPoint->wayPoint->GetPosition()).Length();
						}
					}
				}
				//Timer::GetInstance()->EndOperation("GroundEnemyConnect50");
				m_wayPointList = FloydWarshall::GetInstance()->constructPath50(startWayPoint, endWayPoint);
			}
			break;
		case 100:
			//Timer::GetInstance()->AddTimeOperation("GroundEnemyConnect100");
			for (auto& obstacle : ObstacleManager::GetInstance()->obstacleList100) {
				if (!(obstacle->obs->GetCenterPosition() == m_target->GetPosition()) && CheckCollision::LineIntersectsRect(m_position, m_target->GetPosition(), obstacle->obs)) {
					intersect = true;
					break;
				}
			}
			for (auto& wayPoint : ObstacleManager::GetInstance()->wayPointGoalList100) {
				if (m_target->GetPosition() == wayPoint->wayPoint->GetPosition()) {
					endWayPoint = wayPoint;
				}
			}
			if (!intersect) {
				m_wayPointList.push_back(m_target->GetPosition());
				//Timer::GetInstance()->EndOperation("GroundEnemyConnect100");
			}
			else {
				for (auto& obstacle : ObstacleManager::GetInstance()->obstacleList100) {
					for (auto wayPoint : obstacle->wayPointList) {
						if ((m_position - wayPoint->wayPoint->GetPosition()).Length()  < minF && wayPoint->active
							&& (CheckCollision::CheckLesser90Degree(std::dynamic_pointer_cast<Sprite2D>(shared_from_this()), wayPoint->wayPoint, endWayPoint->wayPoint))) {
							startWayPoint = wayPoint;
							minF = (m_position - wayPoint->wayPoint->GetPosition()).Length();
						}
					}
				}
				//Timer::GetInstance()->EndOperation("GroundEnemyConnect100");
				m_wayPointList = FloydWarshall::GetInstance()->constructPath100(startWayPoint, endWayPoint);
			}
			break;
		default:
			break;
		}
	}
	/*if (m_wayPointList.size() == 0) {
		std::cout << "error";
	}
	if (m_width == 25) {
		Timer::GetInstance()->EndOperation("GroundEnemy25");
	}
	else if (m_width == 50) {
		Timer::GetInstance()->EndOperation("GroundEnemy50");
	}
	else if (m_width == 100) {
		Timer::GetInstance()->EndOperation("GroundEnemy100");
	}*/
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


