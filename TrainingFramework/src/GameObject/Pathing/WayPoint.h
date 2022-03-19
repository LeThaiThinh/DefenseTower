#pragma once
#include "Base/Sprite2D.h"
class WayPoint
{
public:
	WayPoint():active(true) {};
	WayPoint(float x,float y) {
		active = true;
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
		auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		auto texture = ResourceManagers::GetInstance()->GetTexture("Tower/way_point.tga");
		wayPoint = std::make_shared<Sprite2D>(model, shader, texture, x, y, 4, 4, 4, 4);
	};
	void InitEdge() {
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
		auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		auto texture = ResourceManagers::GetInstance()->GetTexture("Tower/way_point.tga");
		for (auto& adjWayPoint : adjWayPointList) {
				auto& edge = std::make_shared<Sprite2D>(model, shader, texture,
					(wayPoint->GetPosition().x + adjWayPoint->wayPoint->GetPosition().x) / 2.f,
					(wayPoint->GetPosition().y + adjWayPoint->wayPoint->GetPosition().y) / 2.f,
					(int)((wayPoint->GetPosition() - adjWayPoint->wayPoint->GetPosition()).Length()), 2,
					(int)((wayPoint->GetPosition() - adjWayPoint->wayPoint->GetPosition()).Length()), 2);
				edge->SetRotation(Vector3(0, 0,
					std::atan((wayPoint->GetPosition().y - adjWayPoint->wayPoint->GetPosition().y) / (wayPoint->GetPosition().x - adjWayPoint->wayPoint->GetPosition().x))));
				edgeList.push_back(edge);
		}
	}
	void Draw() {
		if(active)
			wayPoint->Draw();
		for (auto& edge : edgeList) {
			edge->Draw();
		}
	};
	~WayPoint(){};
	bool active;
	std::shared_ptr<Sprite2D> wayPoint;
	std::list<std::shared_ptr<Sprite2D>> edgeList;
	std::list<std::shared_ptr<WayPoint>> adjWayPointList;
};

