#pragma once
#include "Obstacle.h"
#include "Defensive/DefensiveManager.h"
class ObstacleManager : public CSingleton<ObstacleManager>
{
public:
	std::list<std::shared_ptr<Obstacle>> obstacleList25;
	std::list<std::shared_ptr<Obstacle>> obstacleList50;
	std::list<std::shared_ptr<Obstacle>> obstacleList100;
	std::list<std::shared_ptr<WayPoint>> waypointList25;
	std::list<std::shared_ptr<WayPoint>> waypointList50;
	std::list<std::shared_ptr<WayPoint>> waypointList100;
	std::list<std::shared_ptr<WayPoint>> wayPointGoalList25;
	std::list<std::shared_ptr<WayPoint>> wayPointGoalList50;
	std::list<std::shared_ptr<WayPoint>> wayPointGoalList100;


	void Init(){
		Init25();
	}
	void Init25() {
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
		auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		auto texture = ResourceManagers::GetInstance()->GetTexture("Tower/obstacle_border.tga");
		//create all waypoint
		for (auto &spot : DefensivePoolManager::GetInstance()->spotList)
		{
			std::shared_ptr<Sprite2D> obs= std::make_shared<Sprite2D>(model,shader,texture, spot->GetPosition().x, spot->GetPosition().y, 25+spot->GetIWidth(), 25 + spot->GetIHeight(), 25 + spot->GetWidth(), 25 + spot->GetHeight());
			std::shared_ptr<Obstacle> obstacle = std::make_shared<Obstacle>(obs);
			obstacleList25.push_back(obstacle);
		}
		//remove unused waypoint
		auto _obstacleList25 = obstacleList25;
		for (auto& obstacle : obstacleList25) {
			_obstacleList25.pop_front();
			for (auto& _obstacle : _obstacleList25) {
				int i = 0;
				for (auto& wayPoint : obstacle->wayPointList) {
					if (CheckCollision::PointInRect(wayPoint->wayPoint->GetPosition(), _obstacle->obs)) {
						wayPoint->active = false;
						_obstacle->wayPointList[(i+2)%4]->active = false;
					}
					i++;
				}
			}
		}
		//create graph
			//bettween waypoint
		_obstacleList25 = obstacleList25;
		/**/for (auto& obstacle : obstacleList25) {
			for (auto& _obstacle : _obstacleList25) {
				for (auto& wayPoint : obstacle->wayPointList) {
					for (auto& _wayPoint : _obstacle->wayPointList) {
						if (wayPoint->active && _wayPoint->active && wayPoint!=_wayPoint) {
							bool intersect = false;
							for (auto& __obstacle : obstacleList25) {
								if (CheckCollision::LineIntersectsRectPathing2(wayPoint->wayPoint->GetPosition(), _wayPoint->wayPoint->GetPosition(), __obstacle->obs)) {
									intersect = true;
								}
							}
							if (!intersect) {
								wayPoint->adjWayPointList.push_back(_wayPoint);
								_wayPoint->adjWayPointList.push_back(wayPoint);
							}
						}
					}
				}
			}
		}
			//bettween goal and waypoint
		/**/auto wayPoint = std::make_shared<WayPoint>(DefensivePoolManager::GetInstance()->mainTower->GetPosition().x, DefensivePoolManager::GetInstance()->mainTower->GetPosition().y);
		wayPointGoalList25.push_back(wayPoint);
		for (auto& _obstacle : _obstacleList25) {
			if (!_obstacle->obs->GetPosition().operator==(wayPoint->wayPoint->GetPosition())) {
				for (auto& _wayPoint : _obstacle->wayPointList) {
					bool intersect = false;
					for (auto& __obstacle : obstacleList25) {
						if (wayPoint->active && _wayPoint->active && CheckCollision::LineIntersectsRectPathing(wayPoint->wayPoint->GetPosition(), _wayPoint->wayPoint->GetPosition(), __obstacle->obs)) {
							intersect = true;
						}
					}
					if (!intersect) {
						_wayPoint->adjWayPointList.push_back(wayPoint);
					}
				}
			}
		}
		_obstacleList25 = obstacleList25;
		for (auto& obstacle : obstacleList25) {
			auto wayPoint = std::make_shared<WayPoint>(obstacle->obs->GetPosition().x, obstacle->obs->GetPosition().y);
			wayPointGoalList25.push_back(wayPoint);
			for (auto& _obstacle : _obstacleList25) {
				if (!_obstacle->obs->GetPosition().operator==(wayPoint->wayPoint->GetPosition())) {
					for (auto& _wayPoint : _obstacle->wayPointList) {
						bool intersect = false;
						for (auto& __obstacle : obstacleList25) {
							if (obstacle != __obstacle) {
								if (_wayPoint->active && CheckCollision::LineIntersectsRectPathing(wayPoint->wayPoint->GetPosition(), _wayPoint->wayPoint->GetPosition(), __obstacle->obs)) {
									intersect = true;
								}
							}
						}
						if (!intersect) {
							_wayPoint->adjWayPointList.push_back(wayPoint);
						}
					}
				}
			}
		}

		//visualize
		for (auto& obstacle : obstacleList25) {
			//obstacle->InitEdge();
		}
		//gather to one list
		for (auto& obstacle : obstacleList25) {
			for (auto& wayPoint : obstacle->wayPointList) {
				waypointList25.push_back(wayPoint);
			}
		}
		for (auto& wayPointGoal : wayPointGoalList25) {
			waypointList25.push_back(wayPointGoal);
		}
	};
	void Init50() {
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
		auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		auto texture = ResourceManagers::GetInstance()->GetTexture("Tower/obstacle_border.tga");
		//create all waypoint
		for (auto& spot : DefensivePoolManager::GetInstance()->spotList)
		{
			std::shared_ptr<Sprite2D> obs = std::make_shared<Sprite2D>(model, shader, texture, spot->GetPosition().x, spot->GetPosition().y, 50 + spot->GetIWidth(), 50 + spot->GetIHeight(), 50 + spot->GetWidth(), 50 + spot->GetHeight());
			std::shared_ptr<Obstacle> obstacle = std::make_shared<Obstacle>(obs);
			obstacleList50.push_back(obstacle);
		}
		//remove unused waypoint
		auto _obstacleList50 = obstacleList50;
		for (auto& obstacle : obstacleList50) {
			_obstacleList50.pop_front();
			for (auto& _obstacle : _obstacleList50) {
				int i = 0;
				for (auto& wayPoint : obstacle->wayPointList) {
					if (CheckCollision::PointInRect(wayPoint->wayPoint->GetPosition(), _obstacle->obs)) {
						wayPoint->active = false;
						_obstacle->wayPointList[(i + 2) % 4]->active = false;
					}
					i++;
				}
			}
		}
		//create graph
			//bettween waypoint
		_obstacleList50 = obstacleList50;
		/**/for (auto& obstacle : obstacleList50) {
			for (auto& _obstacle : _obstacleList50) {
				for (auto& wayPoint : obstacle->wayPointList) {
					for (auto& _wayPoint : _obstacle->wayPointList) {
						if (wayPoint->active && _wayPoint->active && wayPoint != _wayPoint) {
							bool intersect = false;
							for (auto& __obstacle : obstacleList50) {
								if (CheckCollision::LineIntersectsRectPathing2(wayPoint->wayPoint->GetPosition(), _wayPoint->wayPoint->GetPosition(), __obstacle->obs)) {
									intersect = true;
								}
							}
							if (!intersect) {
								wayPoint->adjWayPointList.push_back(_wayPoint);
								_wayPoint->adjWayPointList.push_back(wayPoint);
							}
						}
					}
				}
			}
		}
		//bettween goal and waypoint
		/**/auto wayPoint = std::make_shared<WayPoint>(DefensivePoolManager::GetInstance()->mainTower->GetPosition().x, DefensivePoolManager::GetInstance()->mainTower->GetPosition().y);
		wayPointGoalList50.push_back(wayPoint);
		for (auto& _obstacle : _obstacleList50) {
			if (!_obstacle->obs->GetPosition().operator==(wayPoint->wayPoint->GetPosition())) {
				for (auto& _wayPoint : _obstacle->wayPointList) {
					bool intersect = false;
					for (auto& __obstacle : obstacleList50) {
						if (wayPoint->active && _wayPoint->active && CheckCollision::LineIntersectsRectPathing(wayPoint->wayPoint->GetPosition(), _wayPoint->wayPoint->GetPosition(), __obstacle->obs)) {
							intersect = true;
						}
					}
					if (!intersect) {
						_wayPoint->adjWayPointList.push_back(wayPoint);
					}
				}
			}
		}
		_obstacleList50 = obstacleList50;
		for (auto& obstacle : obstacleList50) {
			auto wayPoint = std::make_shared<WayPoint>(obstacle->obs->GetPosition().x, obstacle->obs->GetPosition().y);
			wayPointGoalList50.push_back(wayPoint);
			for (auto& _obstacle : _obstacleList50) {
				if (!_obstacle->obs->GetPosition().operator==(wayPoint->wayPoint->GetPosition())) {
					for (auto& _wayPoint : _obstacle->wayPointList) {
						bool intersect = false;
						for (auto& __obstacle : obstacleList50) {
							if (obstacle != __obstacle) {
								if (_wayPoint->active && CheckCollision::LineIntersectsRectPathing(wayPoint->wayPoint->GetPosition(), _wayPoint->wayPoint->GetPosition(), __obstacle->obs)) {
									intersect = true;
								}
							}
						}
						if (!intersect) {
							_wayPoint->adjWayPointList.push_back(wayPoint);
						}
					}
				}
			}
		}

		//visualize
		for (auto& obstacle : obstacleList50) {
			//obstacle->InitEdge();
		}
		//gather to one list
		for (auto& obstacle : obstacleList50) {
			for (auto& wayPoint : obstacle->wayPointList) {
				waypointList50.push_back(wayPoint);
			}
		}
		for (auto& wayPointGoal : wayPointGoalList50) {
			waypointList50.push_back(wayPointGoal);
		}
	};
	void Init100() {
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
		auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		auto texture = ResourceManagers::GetInstance()->GetTexture("Tower/obstacle_border.tga");
		//create all waypoint
		for (auto& spot : DefensivePoolManager::GetInstance()->spotList)
		{
			std::shared_ptr<Sprite2D> obs = std::make_shared<Sprite2D>(model, shader, texture, spot->GetPosition().x, spot->GetPosition().y, 100 + spot->GetIWidth(), 100 + spot->GetIHeight(), 100 + spot->GetWidth(), 100 + spot->GetHeight());
			std::shared_ptr<Obstacle> obstacle = std::make_shared<Obstacle>(obs);
			obstacleList100.push_back(obstacle);
		}
		//remove unused waypoint
		auto _obstacleList100 = obstacleList100;
		for (auto& obstacle : obstacleList100) {
			_obstacleList100.pop_front();
			for (auto& _obstacle : _obstacleList100) {
				int i = 0;
				for (auto& wayPoint : obstacle->wayPointList) {
					if (CheckCollision::PointInRect(wayPoint->wayPoint->GetPosition(), _obstacle->obs)) {
						wayPoint->active = false;
						_obstacle->wayPointList[(i + 2) % 4]->active = false;
					}
					i++;
				}
			}
		}
		//create graph
			//bettween waypoint
		_obstacleList100 = obstacleList100;
		/**/for (auto& obstacle : obstacleList100) {
			for (auto& _obstacle : _obstacleList100) {
				for (auto& wayPoint : obstacle->wayPointList) {
					for (auto& _wayPoint : _obstacle->wayPointList) {
						if (wayPoint->active && _wayPoint->active && wayPoint != _wayPoint) {
							bool intersect = false;
							for (auto& __obstacle : obstacleList100) {
								if (CheckCollision::LineIntersectsRectPathing2(wayPoint->wayPoint->GetPosition(), _wayPoint->wayPoint->GetPosition(), __obstacle->obs)) {
									intersect = true;
								}
							}
							if (!intersect) {
								wayPoint->adjWayPointList.push_back(_wayPoint);
								_wayPoint->adjWayPointList.push_back(wayPoint);
							}
						}
					}
				}
			}
		}
		//bettween goal and waypoint
		/**/auto wayPoint = std::make_shared<WayPoint>(DefensivePoolManager::GetInstance()->mainTower->GetPosition().x, DefensivePoolManager::GetInstance()->mainTower->GetPosition().y);
		wayPointGoalList100.push_back(wayPoint);
		for (auto& _obstacle : _obstacleList100) {
			if (!_obstacle->obs->GetPosition().operator==(wayPoint->wayPoint->GetPosition())) {
				for (auto& _wayPoint : _obstacle->wayPointList) {
					bool intersect = false;
					for (auto& __obstacle : obstacleList100) {
						if (wayPoint->active && _wayPoint->active && CheckCollision::LineIntersectsRectPathing(wayPoint->wayPoint->GetPosition(), _wayPoint->wayPoint->GetPosition(), __obstacle->obs)) {
							intersect = true;
						}
					}
					if (!intersect) {
						_wayPoint->adjWayPointList.push_back(wayPoint);
					}
				}
			}
		}
		_obstacleList100 = obstacleList100;
		for (auto& obstacle : obstacleList100) {
			auto wayPoint = std::make_shared<WayPoint>(obstacle->obs->GetPosition().x, obstacle->obs->GetPosition().y);
			wayPointGoalList100.push_back(wayPoint);
			for (auto& _obstacle : _obstacleList100) {
				if (!_obstacle->obs->GetPosition().operator==(wayPoint->wayPoint->GetPosition())) {
					for (auto& _wayPoint : _obstacle->wayPointList) {
						bool intersect = false;
						for (auto& __obstacle : obstacleList100) {
							if (obstacle != __obstacle) {
								if (_wayPoint->active && CheckCollision::LineIntersectsRectPathing(wayPoint->wayPoint->GetPosition(), _wayPoint->wayPoint->GetPosition(), __obstacle->obs)) {
									intersect = true;
								}
							}
						}
						if (!intersect) {
							_wayPoint->adjWayPointList.push_back(wayPoint);
						}
					}
				}
			}
		}

		//visualize
		for (auto& obstacle : obstacleList100) {
			//obstacle->InitEdge();
		}
		//gather to one list
		for (auto& obstacle : obstacleList100) {
			for (auto& wayPoint : obstacle->wayPointList) {
				waypointList100.push_back(wayPoint);
			}
		}
		for (auto& wayPointGoal : wayPointGoalList100) {
			waypointList100.push_back(wayPointGoal);
		}
	};
	void Draw() {
		for (auto &obstacle : obstacleList25) {
			//obstacle->Draw();
		}
		for (auto& obstacle : obstacleList50) {
			//obstacle->Draw();
		}
		for (auto& obstacle : obstacleList100) {
			obstacle->Draw();
		}
	}
	void Clear() {
		for (auto& obstacle : obstacleList25) {
			obstacle.reset();
		}
		for (auto& waypoint : waypointList25) {
			waypoint.reset();
		}
		obstacleList25.clear();
		waypointList25.clear();
		wayPointGoalList25.clear();
		for (auto& obstacle : obstacleList50) {
			obstacle.reset();
		}
		for (auto& waypoint : waypointList50) {
			waypoint.reset();
		}
		obstacleList50.clear();
		waypointList50.clear();
		wayPointGoalList50.clear();
		for (auto& obstacle : obstacleList100) {
			obstacle.reset();
		}
		for (auto& waypoint : waypointList100) {
			waypoint.reset();
		}
		obstacleList100.clear();
		waypointList100.clear();
		wayPointGoalList100.clear();
	}
private:

};
