#pragma once
#include "../GameManager/Singleton.h"
#include "EnemyOne.h"
#include <Enemy/EnemySpawner.h>
#include "EnemyTwo.h"
#include "GameStates/GSPlay.h"
#include "Resource/Coin.h"
#include <Enemy/EnemyThree.h>
#define TimeFindPath 3.0;
class EnemyPoolManager : public CSingleton<EnemyPoolManager>
{
public:
	static float currentTimeFindPath;

	std::list<std::shared_ptr<BaseEnemy>> enemyOneResources;
	std::list<std::shared_ptr<BaseEnemy>> enemyTwoResources;
	std::list<std::shared_ptr<BaseEnemy>> enemyThreeResources;

	std::list<std::shared_ptr<BaseEnemy>> flyEnemyList;
	std::list<std::shared_ptr<BaseEnemy>> flyEnemyListRemove;
	std::list<std::shared_ptr<BaseEnemy>> groundEnemyList;
	std::list<std::shared_ptr<BaseEnemy>> groundEnemyListRemove;

	std::list<std::shared_ptr<EnemySpawner>> spawnerList;

	static void ResetFindPath() { currentTimeFindPath = TimeFindPath };

	void Init() {
		//spawnerList.push_back(std::make_shared<EnemySpawner>(300.f, 800.f, EnemyType::EnemyOne, 0.f));
		//spawnerList.push_back(std::make_shared<EnemySpawner>(300.f, 1000.f, EnemyType::EnemyTwo, 1.f));
		//spawnerList.push_back(std::make_shared<EnemySpawner>(100.f, 0.f, EnemyType::EnemyOne, 2.f));
		//spawnerList.push_back(std::make_shared<EnemySpawner>(200.f, 500.f, EnemyType::EnemyTwo, 2.f));
		//spawnerList.push_back(std::make_shared<EnemySpawner>(0.f, 0.f, EnemyType::EnemyTwo, 3.f));
		/**/
		for (int i = 0; i < 25; i++) {
			float x = -100 - Globals::mapWidth/2 + Globals::screenWidth/2 + (Globals::mapWidth + 200) * ((float)rand() / RAND_MAX);
			float y = -100 -Globals::mapHeight/2 + Globals::screenHeight/2 + (Globals::mapHeight + 200) * ((float)rand() / RAND_MAX);
			if (x < Globals::screenWidth + 100 && x> - 100) {
				while (y < Globals::screenHeight +100 && y> - 100)
				{
					y = -100 - Globals::mapHeight / 2 + Globals::screenHeight / 2 + (Globals::mapHeight + 200) * ((float)rand() / RAND_MAX);
				}
			}
			spawnerList.push_back(std::make_shared<EnemySpawner>(x, y, (EnemyType)(i%3), i/3.f));
		}
	}
	void Add(float x, float y, EnemyType type) {
		if (type == EnemyType::EnemyOne) {
			std::shared_ptr<BaseEnemy> enemy;
			if (enemyOneResources.empty()) enemy = std::make_shared<EnemyOne>(x, y);
			else {
				enemy = enemyOneResources.front();
				enemyOneResources.pop_front();
				enemy->Set2DPosition(x, y);
			}
			groundEnemyList.push_back(enemy);
		}
		else if (type == EnemyType::EnemyTwo) {
			std::shared_ptr<BaseEnemy> enemy;
			if (enemyTwoResources.empty()) enemy = std::make_shared<EnemyTwo>(x, y);
			else {
				enemy = enemyTwoResources.front();
				enemyTwoResources.pop_front();
				enemy->Set2DPosition(x, y);
			}
			groundEnemyList.push_back(enemy);
		}
		else if (type == EnemyType::EnemyThree) {
			std::shared_ptr<BaseEnemy> enemy;
			if (enemyThreeResources.empty()) enemy = std::make_shared<EnemyThree>(x, y);
			else {
				enemy = enemyThreeResources.front();
				enemyThreeResources.pop_front();
				enemy->Set2DPosition(x, y);
			}
			groundEnemyList.push_back(enemy);
		}
	}
	void Spawn(float time) {
		if (!spawnerList.empty() && time >= spawnerList.front()->GetSpawnerTime()) {
			Add(spawnerList.front()->GetX(), spawnerList.front()->GetY(), spawnerList.front()->GetType());
			spawnerList.pop_front();
		}
	}
	void Update(float deltaTime) {
		currentTimeFindPath += deltaTime;
		if (currentTimeFindPath < 3) {
			for (auto &enemy : flyEnemyList) {
				enemy->Update(deltaTime);
			}
			for (auto &enemy : groundEnemyList) {
				enemy->Update(deltaTime);
			}
		}
		else {
			for (auto& enemy : groundEnemyList) {
				if (!enemy->IsAttacking())
					enemy->FindTarget();
				enemy->Update(deltaTime);
			}
			for (auto &enemy : flyEnemyList) {
				if (!enemy->IsAttacking())
					enemy->FindTarget();
				enemy->Update(deltaTime);
			}
			currentTimeFindPath = 0;
		}
		if (flyEnemyList.empty() && groundEnemyList.empty() && spawnerList.empty())
			GSPlay::win = 1;
	}
	void Draw() {
		for (auto &enemy : groundEnemyList) {
			enemy->Draw();
		}
		for (auto &enemy : flyEnemyList) {
			enemy->Draw();
		}
	}
	void RemoveFly(std::shared_ptr<BaseEnemy> enemy) {
		flyEnemyListRemove.push_back(enemy);
		enemyOneResources.push_back(enemy);
		enemy->Reset();
	}
	void RemoveGround(std::shared_ptr<BaseEnemy> enemy) {
		Coin::GetInstance()->Bounty(enemy->GetBounty());
		groundEnemyListRemove.push_back(enemy);
		if (enemy->GetType() == EnemyType::EnemyOne) {
			enemyOneResources.push_back(enemy);
		}
		else if (enemy->GetType() == EnemyType::EnemyTwo) {
			enemyTwoResources.push_back(enemy);
		}
		else if (enemy->GetType() == EnemyType::EnemyThree) {
			enemyThreeResources.push_back(enemy);
		}
		enemy->Reset();
	}
	void RemoveFlyInstant(std::shared_ptr<BaseEnemy> enemy) {
		flyEnemyList.remove(enemy);
		enemy->Reset();
	}
	void RemoveGroundInstant(std::shared_ptr<BaseEnemy> enemy) {
		Coin::GetInstance()->Bounty(enemy->GetBounty());
		groundEnemyList.remove(enemy);
		if (enemy->GetType() == EnemyType::EnemyOne) {
			enemyOneResources.push_back(enemy);
		}
		else if (enemy->GetType() == EnemyType::EnemyTwo) {
			enemyTwoResources.push_back(enemy);
		}
		else if (enemy->GetType() == EnemyType::EnemyThree) {
			enemyThreeResources.push_back(enemy);
		}
		enemy->Reset();
	}
	void Remove() {
		for (auto &enemy : groundEnemyListRemove) {
			groundEnemyList.remove(enemy);
		}
		groundEnemyListRemove.clear();
		for (auto &enemy : flyEnemyListRemove) {
			flyEnemyList.remove(enemy);
		}
		flyEnemyListRemove.clear();
	}
	void Clear() {
		for (auto &enemy : groundEnemyList) {
			RemoveGround(enemy);
		}
		for (auto &enemy : flyEnemyList) {
			RemoveFly(enemy);
		}
		spawnerList.clear();
	}
};
