#pragma once
#include <MainTower.h>
#include <TowerOne.h>
#include "ObjectPoolManager.h"
#include <TowerTwo.h>
#include <SpotTower.h>


class TowerPoolManager : public CSingleton<TowerPoolManager>
{
public:
	std::list<std::shared_ptr<SpotTower>> spotList;
	std::list<std::shared_ptr<UnMoveThroughAbleTower>> unMoveThroughAbleTowerList;

	std::shared_ptr<ObjectPoolManager<TowerOne>> towerOneManager= std::make_shared<ObjectPoolManager<TowerOne>>();
	std::shared_ptr<ObjectPoolManager<TowerTwo>> towerTwoManager= std::make_shared<ObjectPoolManager<TowerTwo>>();
	std::shared_ptr<MainTower> mainTower;


	std::list<std::shared_ptr<SpotTower>> GetSpotTower(){
		return spotList;
	}

	void Add(float x,float y,TowerType type){
		if (type == TowerType::Spot) {
			std::shared_ptr<SpotTower> spot = std::make_shared<SpotTower>();
			spot->Set2DPosition(x, y);
			spotList.push_back(spot);
		}else if (type == TowerType::Main) {
			mainTower = std::make_shared<MainTower>();
			mainTower->Set2DPosition(x, y);
			unMoveThroughAbleTowerList.push_back(mainTower);
		}else if (type == TowerType::One) {
			std::shared_ptr<TowerOne> towerOne = towerOneManager->GetInstance()->AddResource();
			towerOne->Set2DPosition(x, y);
			unMoveThroughAbleTowerList.push_back(towerOne);
		}else if (type == TowerType::Two) {
			std::shared_ptr<TowerTwo> towerOne = towerTwoManager->GetInstance()->AddResource();
			towerOne->Set2DPosition(x, y);
			unMoveThroughAbleTowerList.push_back(towerOne);
		}
	}
	void Update(float deltaTime) {
		for (auto spot : spotList) {
			spot->Update(deltaTime);
		}
		towerOneManager->GetInstance()->Update(deltaTime);
		towerTwoManager->GetInstance()->Update(deltaTime);
		mainTower->Update(deltaTime);
	}
	void Draw() {
		for (auto spot : spotList) {
			spot->Draw();
		}
		towerOneManager->GetInstance()->Draw();
		towerTwoManager->GetInstance()->Draw();
		mainTower->Draw();
	}
	void Remove() {
		for (auto tower : towerOneManager->GetInstance()->Remove()) {
			//towerTwoManager->GetInstance()->Remove();
			unMoveThroughAbleTowerList.remove(tower);
		}
		for (auto tower : towerTwoManager->GetInstance()->Remove()) {
			//towerTwoManager->GetInstance()->Remove();
			unMoveThroughAbleTowerList.remove(tower);
		}
	}
};
