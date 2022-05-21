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
    std::map<std::shared_ptr<WayPoint>, std::map<std::shared_ptr<WayPoint>, float>> dist100;
    std::map<std::shared_ptr<WayPoint>, std::map<std::shared_ptr<WayPoint>, std::shared_ptr<WayPoint>>> prev100;
    void Init() {
        ObstacleManager::GetInstance()->Init();
        Init25();
        floydWarshall25();
        Init50();
        floydWarshall50();
        Init100();
        floydWarshall100();
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
        for (auto& k : ObstacleManager::GetInstance()->waypointList25) {
            for (auto& i : ObstacleManager::GetInstance()->waypointList25) {
                for (auto& j : ObstacleManager::GetInstance()->waypointList25) {
                    if (dist25[i][k] == -1 || dist25[k][j] == -1) {
                        continue;
                    }else 
                    if (dist25[i][j] > dist25[i][k]+ dist25[k][j]) {
                        dist25[i][j] = dist25[i][k] + dist25[k][j];
                        prev25[i][j] = prev25[i][k];
                    }
                }
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
    void Init100() {
        for (auto& wayPoint : ObstacleManager::GetInstance()->waypointList100) {
            for (auto& _wayPoint : ObstacleManager::GetInstance()->waypointList100) {
                if (std::find(wayPoint->adjWayPointList.begin(), wayPoint->adjWayPointList.end(), _wayPoint) != wayPoint->adjWayPointList.end()) {
                    dist100[wayPoint][_wayPoint] = (wayPoint->wayPoint->GetPosition() - _wayPoint->wayPoint->GetPosition()).Length();
                    prev100[wayPoint][_wayPoint] = _wayPoint;
                    //std::cout << (wayPoint->wayPoint->GetPosition() - _wayPoint->wayPoint->GetPosition()).Length()<<" ";
                }
                else if (wayPoint == _wayPoint) {
                    dist100[wayPoint][_wayPoint] = 0;
                    prev100[wayPoint][_wayPoint] = _wayPoint;
                }
                else {
                    dist100[wayPoint][_wayPoint] = INFINITY;
                    prev100[wayPoint][_wayPoint] = nullptr;
                }
            }
        }
    }
    void floydWarshall100()
    {

        for (auto& wayPoint : ObstacleManager::GetInstance()->waypointList100) {
            for (auto& _wayPoint : ObstacleManager::GetInstance()->waypointList100) {
                for (auto& __wayPoint : ObstacleManager::GetInstance()->waypointList100) {
                    if (dist100[_wayPoint][wayPoint] == -1 || dist100[wayPoint][__wayPoint] == -1) {
                        continue;
                    }
                    else
                        if (dist100[_wayPoint][__wayPoint] > dist100[_wayPoint][wayPoint] + dist100[wayPoint][__wayPoint]) {
                            dist100[_wayPoint][__wayPoint] = dist100[_wayPoint][wayPoint] + dist100[wayPoint][__wayPoint];
                            prev100[_wayPoint][__wayPoint] = prev100[_wayPoint][wayPoint];
                        }
                }
            }
        }
    }
    std::list<Vector3> constructPath100(std::shared_ptr<WayPoint> u, std::shared_ptr<WayPoint> v)
    {
        if (prev100[u][v] == nullptr)
            return {};

        // Storing the path in a vector
        std::list<Vector3> path;
        path.push_back(u->wayPoint->GetPosition());
        while (u != v) {
            u = prev100[u][v];
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
        dist100.clear();
        prev100.clear();
    }
};
