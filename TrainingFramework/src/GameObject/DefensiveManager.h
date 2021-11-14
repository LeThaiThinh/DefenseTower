#pragma once
#include "MainTower.h"
#include "TowerOne.h"
#include "TowerTwo.h"
#include "SpotTower.h"

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
		DefensivePoolManager::GetInstance()->Add(Globals::screenWidth / 2.f, Globals::screenHeight * 1 / 2.f, TowerType::Main);
		DefensivePoolManager::GetInstance()->Add(Globals::screenWidth / 2.f, Globals::screenHeight * 1 / 4.f, TowerType::Spot);
		DefensivePoolManager::GetInstance()->Add(Globals::screenWidth / 2.f, Globals::screenHeight * 3 / 4.f, TowerType::Spot);
		DefensivePoolManager::GetInstance()->Add(Globals::screenWidth * 1 / 4.f, Globals::screenHeight / 2.f, TowerType::Spot);
		DefensivePoolManager::GetInstance()->Add(Globals::screenWidth * 3 / 4.f, Globals::screenHeight / 2.f, TowerType::Spot);
		DefensivePoolManager::GetInstance()->Add(Globals::screenWidth * 3 / 8.f, Globals::screenHeight * 3 / 8.f, TowerType::Spot);
		DefensivePoolManager::GetInstance()->Add(Globals::screenWidth * 3 / 8.f, Globals::screenHeight * 5 / 8.f, TowerType::Spot);
		DefensivePoolManager::GetInstance()->Add(Globals::screenWidth * 3 / 8.f + 50, Globals::screenHeight * 5 / 8.f, TowerType::Spot);
		DefensivePoolManager::GetInstance()->Add(Globals::screenWidth * 3 / 8.f + 100, Globals::screenHeight * 5 / 8.f, TowerType::Spot);
		DefensivePoolManager::GetInstance()->Add(Globals::screenWidth * 3 / 8.f + 150, Globals::screenHeight * 5 / 8.f, TowerType::Spot);
		DefensivePoolManager::GetInstance()->Add(Globals::screenWidth * 3 / 8.f + 200, Globals::screenHeight * 5 / 8.f, TowerType::Spot);
		DefensivePoolManager::GetInstance()->Add(Globals::screenWidth * 3 / 8.f, Globals::screenHeight * 5 / 8.f - 50, TowerType::Spot);
		DefensivePoolManager::GetInstance()->Add(Globals::screenWidth * 5 / 8.f, Globals::screenHeight * 3 / 8.f, TowerType::Spot);
		DefensivePoolManager::GetInstance()->Add(Globals::screenWidth * 5 / 8.f, Globals::screenHeight * 5 / 8.f, TowerType::Spot);
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
		for (auto tower : spotList) {
			tower->Update(deltaTime);
		}
		for (auto tower : unMoveThroughAbleTowerList) {
			tower->Update(deltaTime);
		}
	}
	void HandleTouchEvents(GLint x, GLint y, bool bIsPressed) {
		for (auto tower : spotList) {
			tower->HandleTouchEvents(x, y, bIsPressed, tower);
		}
		for (auto tower : unMoveThroughAbleTowerList) {
			tower->HandleTouchEvents(x, y, bIsPressed, tower);
		}
	}
	void Draw() {
		for (auto spot : spotList) {
			spot->Draw();
		}
		for (auto tower : unMoveThroughAbleTowerList) {
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
		for (auto tower : spotListRemove) {
			std::dynamic_pointer_cast<SpotTower>(tower)->Reset();
			spotList.remove(tower);
		}
		spotListRemove.clear();
		for (auto tower : unMoveThroughAbleTowerListRemove) {
			std::dynamic_pointer_cast<UnMoveThroughAbleTower>(tower)->Reset();
			unMoveThroughAbleTowerList.remove(tower);
		}
		unMoveThroughAbleTowerListRemove.clear();
	}
	void Clear() {
		for (auto spot : spotList) {
			RemoveSpot(spot);
		}
		for (auto tower : unMoveThroughAbleTowerList) {
			RemoveUnmove(tower);
		}
	}
};
