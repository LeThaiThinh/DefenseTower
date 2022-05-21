#pragma once
#include "MainTower.h"
#include "TowerOne.h"
#include "TowerTwo.h"
#include "SpotTower.h"
#include "GameStates/GSPlay.h"
#include "CheckCollision.h"
class DefensivePoolManager : public CSingleton<DefensivePoolManager>
{
public:
	std::list<std::shared_ptr<SpotTower>> spotResources;
	std::list<std::shared_ptr<TowerOne>> oneResources;
	std::list<std::shared_ptr<TowerTwo>> twoResources;

	std::list<std::shared_ptr<BaseDefensive>> unMoveThroughAbleTowerList;
	std::list<std::shared_ptr<BaseDefensive>> unMoveThroughAbleTowerListRemove;
	std::list<std::shared_ptr<BaseDefensive>> spotList;
	std::list<std::shared_ptr<BaseDefensive>> spotListRemove;
	std::shared_ptr<MainTower> mainTower;

	void Init() {
		DefensivePoolManager::GetInstance()->Add(Globals::screenWidth * 1.f / 2.f, Globals::screenHeight * 1.f / 2.f, TowerType::Main);
		/*DefensivePoolManager::GetInstance()->Add(Globals::screenWidth * 1.f / 2.f, Globals::screenHeight * 1.f / 4.f, TowerType::Spot);
		DefensivePoolManager::GetInstance()->Add(Globals::screenWidth * 1.f / 2.f, Globals::screenHeight * 3.f / 4.f, TowerType::Spot);
				DefensivePoolManager::GetInstance()->Add(Globals::screenWidth * 1.f / 2.f + 75, Globals::screenHeight * 3.f / 4.f + 50, TowerType::Spot);
		DefensivePoolManager::GetInstance()->Add(Globals::screenWidth * 1.f / 2.f, Globals::screenHeight * 3.f / 4.f, TowerType::Spot);

		DefensivePoolManager::GetInstance()->Add(Globals::screenWidth * 1.f / 4.f, Globals::screenHeight / 2.f, TowerType::Spot);
		DefensivePoolManager::GetInstance()->Add(Globals::screenWidth * 3.f / 4.f, Globals::screenHeight / 2.f, TowerType::Spot);*/

		/**/for (int i = 0; i < 20; i++) {
			float x = - 0.1 * Globals::screenWidth + Globals::screenWidth * 1.2 * ((float)rand()/RAND_MAX);
			float y = - 0.1 * Globals::screenHeight + Globals::screenHeight * 1.2 * ((float)rand() / RAND_MAX);
			std::shared_ptr<Sprite2D> s = std::make_shared<Sprite2D>(nullptr, nullptr, nullptr, x, y, 120, 100, 120, 100);
			std::shared_ptr<Sprite2D> s0 = std::make_shared<Sprite2D>(nullptr, nullptr, nullptr, x, y, 120, 100, 130, 110);
			bool intersect = true;
			while (intersect) {
				intersect = false;
				x = -0.1 * Globals::screenWidth + Globals::screenWidth * 1.2 * ((float)rand() / RAND_MAX);
				y = -0.1 * Globals::screenHeight + Globals::screenHeight * 1.2 * ((float)rand() / RAND_MAX);
				//std::cout << x << " " << y << std::endl;
				s0->Set2DPosition(x, y);
				for (auto& spot:spotList) {
					if (CheckCollision::RectIntersectRect(spot, s0)) {
						intersect = true;
					}
				}
				if (CheckCollision::RectIntersectRect(mainTower, s0)) {
					intersect = true;
				}
				if (CheckCollision::RectIntersectRect(MainCharacter::GetInstance(), s0)) {
					intersect = true;
				}
			}
			DefensivePoolManager::GetInstance()->Add(x, y, TowerType::Spot);
		}
	}

	void Add(float x, float y, TowerType type) {
		if (type == TowerType::Spot) {
			std::shared_ptr<BaseDefensive> tower;
			if (spotResources.empty()) tower = std::make_shared<SpotTower>(x, y);
			else {
				tower = spotResources.front();
				spotResources.pop_front();
				tower->Set2DPosition(x, y);
			}
			tower->LocateOption();
			spotList.push_back(tower);
			//printf("add spot\n");
		}
		else if (type == TowerType::Main) {
			mainTower = std::make_shared<MainTower>(x, y);
			mainTower->LocateOption();
			unMoveThroughAbleTowerList.push_back(mainTower);
			//printf("add main\n");
		}
		else if (type == TowerType::One) {
			std::shared_ptr<BaseDefensive> tower;
			if (oneResources.empty()) tower = std::make_shared<TowerOne>(x, y);
			else {
				tower = oneResources.front();
				oneResources.pop_front();
				tower->Set2DPosition(x, y);
			}
			//towerManager->GetInstance()->AddResourceOne(x, y);
			tower->LocateOption();
			unMoveThroughAbleTowerList.push_back(tower);
			//printf("add one\n");
		}
		else if (type == TowerType::Two) {
			std::shared_ptr<BaseDefensive> tower;
			if (twoResources.empty()) tower = std::make_shared<TowerTwo>(x, y);
			else {
				tower = twoResources.front();
				twoResources.pop_front();
				tower->Set2DPosition(x, y);
			}
			//towerManager->GetInstance()->AddResourceTwo(x, y);
			tower->LocateOption();
			unMoveThroughAbleTowerList.push_back(tower);
			//printf("add two\n");
		}
	}
	void Update(float deltaTime) {
		for (auto &tower : spotList) {
			tower->Update(deltaTime);
		}
		for (auto &tower : unMoveThroughAbleTowerList) {
			tower->Update(deltaTime);
		}
	}
	bool HandleTouchEvents(GLint x, GLint y, bool bIsPressed) {
		for (auto & spot : spotList) {
			if (spot->HandleTouchEvents(x, y, bIsPressed, spot)) {
				return true;
			}
		}
		for (auto &tower : unMoveThroughAbleTowerList) {
			if(tower->HandleTouchEvents(x, y, bIsPressed, tower)) {
				return true;
			}
		}
		return false;
	}
	void Draw() {
		for (auto &spot : spotList) {
			spot->Draw();
		}
		for (auto &tower : unMoveThroughAbleTowerList) {
			tower->Draw();
		}
	}
	void RemoveSpot(std::shared_ptr<BaseDefensive> tower) {
		spotListRemove.push_back(tower);
		spotResources.push_back(std::dynamic_pointer_cast<SpotTower>(tower));
		tower->Reset();
		//printf("remove spot\n");
	}
	void RemoveUnmove(std::shared_ptr<BaseDefensive> tower) {
		unMoveThroughAbleTowerListRemove.push_back(tower);
		if (tower->GetType() == TowerType::One) {
			oneResources.push_back(std::dynamic_pointer_cast<TowerOne>(tower));
			std::dynamic_pointer_cast<UnMoveThroughAbleTower>(tower)->Reset();
			//printf("remove one\n");
		}
		else if (tower->GetType() == TowerType::Two) {
			twoResources.push_back(std::dynamic_pointer_cast<TowerTwo>(tower));
			std::dynamic_pointer_cast<UnMoveThroughAbleTower>(tower)->Reset();
			//printf("remove two\n");
		}
	}
	void RemoveUnmoveInstant(std::shared_ptr<BaseDefensive> tower) {
		if (tower->GetType() == TowerType::Main) {
			unMoveThroughAbleTowerList.remove(tower);
			std::dynamic_pointer_cast<UnMoveThroughAbleTower>(tower)->Reset();
			tower.reset();
			GSPlay::win = 0;
		}
		else if (tower->GetType() == TowerType::One) {
			oneResources.push_back(std::dynamic_pointer_cast<TowerOne>(tower));
			unMoveThroughAbleTowerList.remove(tower);
			std::dynamic_pointer_cast<UnMoveThroughAbleTower>(tower)->Reset();
		}
		else if (tower->GetType() == TowerType::Two) {
			twoResources.push_back(std::dynamic_pointer_cast<TowerTwo>(tower));
			unMoveThroughAbleTowerList.remove(tower);
			std::dynamic_pointer_cast<UnMoveThroughAbleTower>(tower)->Reset();
		}
	}
	void Remove() {
		for (auto &tower : spotListRemove) {
			std::dynamic_pointer_cast<SpotTower>(tower)->Reset();
			spotList.remove(tower);
		}
		spotListRemove.clear();
		for (auto &tower : unMoveThroughAbleTowerListRemove) {
			std::dynamic_pointer_cast<UnMoveThroughAbleTower>(tower)->Reset();
			unMoveThroughAbleTowerList.remove(tower);
		}
		unMoveThroughAbleTowerListRemove.clear();
	}
	void Clear() {
		for (auto &spot : spotList) {
			RemoveSpot(spot);
		}
		for (auto &tower : unMoveThroughAbleTowerList) {
			RemoveUnmove(tower);
		}
	}
};
