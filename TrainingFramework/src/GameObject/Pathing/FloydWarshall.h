#pragma once
#include "ObstacleManager.h"
#include <algorithm>
#include "../GameStates/GSLoadGame.h"
class FloydWarshall : public CSingleton<FloydWarshall>
{
public:
	std::map<std::shared_ptr<WayPoint>, std::map<std::shared_ptr<WayPoint>, float>> dist25;
	std::map<std::shared_ptr<WayPoint>, std::map<std::shared_ptr<WayPoint>, std::shared_ptr<WayPoint>>> prev25;
    std::map<std::shared_ptr<WayPoint>, std::map<std::shared_ptr<WayPoint>, float>> dist50;
    std::map<std::shared_ptr<WayPoint>, std::map<std::shared_ptr<WayPoint>, std::shared_ptr<WayPoint>>> prev50;
    void Init() {
        ObstacleManager::GetInstance()->Init();
        Init25();
        Init50();
    }
    void Init25() {
        for (auto& wayPoint : ObstacleManager::GetInstance()->waypointList25) {
            for (auto& _wayPoint : ObstacleManager::GetInstance()->waypointList25) {
                if (std::find(wayPoint->adjWayPointList.begin(), wayPoint->adjWayPointList.end(), _wayPoint) != wayPoint->adjWayPointList.end()) {
                    dist25[wayPoint][_wayPoint] = (wayPoint->wayPoint->GetPosition() - _wayPoint->wayPoint->GetPosition()).Length();
                    prev25[wayPoint][_wayPoint] = _wayPoint;
                    //std::cout << (wayPoint->wayPoint->GetPosition() - _wayPoint->wayPoint->GetPosition()).Length()<<" ";
                }
                else if (wayPoint == _wayPoint) {
                    dist25[wayPoint][_wayPoint] = 0;
                    prev25[wayPoint][_wayPoint] = _wayPoint;
                }
                else {
                    dist25[wayPoint][_wayPoint] = INFINITY;
                    prev25[wayPoint][_wayPoint] = nullptr;
                }
            }
        }
    }
    void floydWarshall25()
    {
        for (auto& wayPoint : ObstacleManager::GetInstance()->waypointList25) {
            for (auto& _wayPoint : ObstacleManager::GetInstance()->waypointList25) {
                for (auto& __wayPoint : ObstacleManager::GetInstance()->waypointList25) {
                    if (dist25[_wayPoint][wayPoint] == -1 || dist25[wayPoint][__wayPoint] == -1) {
                        continue;
                    }else 
                    if (dist25[_wayPoint][__wayPoint] > dist25[_wayPoint][wayPoint]+ dist25[wayPoint][__wayPoint]) {
                        //std::cout << "(" << dist25[_wayPoint][wayPoint] <<"," << dist25[wayPoint][__wayPoint] << ")";
                        dist25[_wayPoint][__wayPoint] = dist25[_wayPoint][wayPoint] + dist25[wayPoint][__wayPoint];
                        prev25[_wayPoint][__wayPoint] = prev25[_wayPoint][wayPoint];
                    }
                }
            }
        }
        for (auto& wayPoint : ObstacleManager::GetInstance()->waypointList25) {
            for (auto& _wayPoint : ObstacleManager::GetInstance()->waypointList25) {
            }
        }
    }
    std::list<Vector3> constructPath25(std::shared_ptr<WayPoint> u, std::shared_ptr<WayPoint> v)
    {
        if (prev25[u][v] == nullptr)
            return {};

        // Storing the path in a vector
        std::list<Vector3> path;
        path.push_back(u->wayPoint->GetPosition());
        while (u != v) {
            u = prev25[u][v];
            path.push_back(u->wayPoint->GetPosition());
        }
        return path;
    }
    void Init50() {
        for (auto& wayPoint : ObstacleManager::GetInstance()->waypointList50) {
            for (auto& _wayPoint : ObstacleManager::GetInstance()->waypointList50) {
                if (std::find(wayPoint->adjWayPointList.begin(), wayPoint->adjWayPointList.end(), _wayPoint) != wayPoint->adjWayPointList.end()) {
                    dist50[wayPoint][_wayPoint] = (wayPoint->wayPoint->GetPosition() - _wayPoint->wayPoint->GetPosition()).Length();
                    prev50[wayPoint][_wayPoint] = _wayPoint;
                    //std::cout << (wayPoint->wayPoint->GetPosition() - _wayPoint->wayPoint->GetPosition()).Length()<<" ";
                }
                else if (wayPoint == _wayPoint) {
                    dist50[wayPoint][_wayPoint] = 0;
                    prev50[wayPoint][_wayPoint] = _wayPoint;
                }
                else {
                    dist50[wayPoint][_wayPoint] = INFINITY;
                    prev50[wayPoint][_wayPoint] = nullptr;
                }
            }
        }
    }
    void floydWarshall50()
    {

        for (auto& wayPoint : ObstacleManager::GetInstance()->waypointList50) {
            for (auto& _wayPoint : ObstacleManager::GetInstance()->waypointList50) {
                for (auto& __wayPoint : ObstacleManager::GetInstance()->waypointList50) {
                    if (dist50[_wayPoint][wayPoint] == -1 || dist50[wayPoint][__wayPoint] == -1) {
                        continue;
                    }
                    else
                        if (dist50[_wayPoint][__wayPoint] > dist50[_wayPoint][wayPoint] + dist50[wayPoint][__wayPoint]) {
                            dist50[_wayPoint][__wayPoint] = dist50[_wayPoint][wayPoint] + dist50[wayPoint][__wayPoint];
                            prev50[_wayPoint][__wayPoint] = prev50[_wayPoint][wayPoint];
                        }
                }
            }
        }
        for (auto& wayPoint : ObstacleManager::GetInstance()->waypointList50) {
            for (auto& _wayPoint : ObstacleManager::GetInstance()->waypointList50) {
            }
        }
    }
    std::list<Vector3> constructPath50(std::shared_ptr<WayPoint> u, std::shared_ptr<WayPoint> v)
    {
        if (prev50[u][v] == nullptr)
            return {};

        // Storing the path in a vector
        std::list<Vector3> path;
        path.push_back(u->wayPoint->GetPosition());
        while (u != v) {
            u = prev50[u][v];
            path.push_back(u->wayPoint->GetPosition());
        }
        return path;
    }
    void Clear() {
        ObstacleManager::GetInstance()->Clear();
        dist25.clear();
        prev25.clear();
        dist50.clear();
        prev50.clear();
    }
};
