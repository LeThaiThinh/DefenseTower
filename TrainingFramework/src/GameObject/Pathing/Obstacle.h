#pragma once
#include "Base/Sprite2D.h"
#include <Pathing/WayPoint.h>
class Obstacle:public Sprite2D
{
public:
	Obstacle(){};
	Obstacle::Obstacle(std::shared_ptr<Sprite2D> obs) {
		this->obs = obs;
		for (int i = 0; i < 4; i++) {
			switch (i)
			{
			case 0:
				wayPointList.push_back(std::make_shared<WayPoint>(obs->GetPosition().x - obs->GetWidth() / 2.f, obs->GetPosition().y - obs->GetHeight() / 2.f));
				break;
			case 1:
				wayPointList.push_back(std::make_shared<WayPoint>(obs->GetPosition().x + obs->GetWidth() / 2.f, obs->GetPosition().y - obs->GetHeight() / 2.f));
				break;
			case 2:
				wayPointList.push_back(std::make_shared<WayPoint>(obs->GetPosition().x + obs->GetWidth() / 2.f, obs->GetPosition().y + obs->GetHeight() / 2.f));
				break;
			case 3:
				wayPointList.push_back(std::make_shared<WayPoint>(obs->GetPosition().x - obs->GetWidth() / 2.f, obs->GetPosition().y + obs->GetHeight() / 2.f));
				break;
			default:
				break;
			}
		}
	};
	~Obstacle(){};
	void InitEdge() {
		for (auto& waypoint : wayPointList) {
			waypoint->InitEdge();
		}
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
		auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		auto texture = ResourceManagers::GetInstance()->GetTexture("Tower/way_point.tga");
		for (int i = 0; i < 4; i++) {
			/*if (wayPointList[i]->active && wayPointList[(i + 1) % 4]->active) {
			auto& edge = std::make_shared<Sprite2D>(model, shader, texture,
				(wayPointList[i]->wayPoint->GetPosition().x + wayPointList[(i+1) % 4]->wayPoint->GetPosition().x) / 2.f,
				(wayPointList[i]->wayPoint->GetPosition().y + wayPointList[(i + 1) % 4]->wayPoint->GetPosition().y) / 2.f,
				(int)((wayPointList[i]->wayPoint->GetPosition() - wayPointList[(i + 1) % 4]->wayPoint->GetPosition()).Length()), 4,
				(int)((wayPointList[i]->wayPoint->GetPosition() - wayPointList[(i + 1) % 4]->wayPoint->GetPosition()).Length()), 4);
			edge->SetRotation(Vector3(0, 0,
				std::atan((wayPointList[i]->wayPoint->GetPosition().y - wayPointList[(i + 1) % 4]->wayPoint->GetPosition().y) 
					/ ((wayPointList[i]->wayPoint->GetPosition().x - wayPointList[(i + 1) % 4]->wayPoint->GetPosition().x)))));
			wayPointList[i]->edgeList.push_back(edge);
			wayPointList[(i + 1)%4]->edgeList.push_back(edge);
			wayPointList[i]->adjWayPointList.push_back(wayPointList[(i + 1) % 4]);
			wayPointList[(i + 1) % 4]->adjWayPointList.push_back(wayPointList[i]);
			}*/
		}
		for (int i = 0; i < 4; i++) {
			std::cout << wayPointList[i]->adjWayPointList.size()<<" ";
		}
	}
	void Draw() {
		obs->Draw();
		for (auto &wayPoint : wayPointList) {
			wayPoint->Draw();
		}
	}
	void Reset() {

	}

	std::shared_ptr<Sprite2D> obs;
	std::vector<std::shared_ptr<WayPoint>> wayPointList;
};