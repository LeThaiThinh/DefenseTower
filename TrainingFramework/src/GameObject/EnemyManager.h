#pragma once
#include "../GameManager/Singleton.h"
#include "../../Buffalo.h"
#include <EnemySpawner.h>
#include <Zombie.h>
#define TimeFindPath 3.0;
class EnemyPoolManager : public CSingleton<EnemyPoolManager>
{
public:
	static float currentTimeFindPath;

	std::list<std::shared_ptr<BaseEnemy>> buffaloResources;
	std::list<std::shared_ptr<BaseEnemy>> zombieResources;

	std::list<std::shared_ptr<BaseEnemy>> flyEnemyList;
	std::list<std::shared_ptr<BaseEnemy>> flyEnemyListRemove;
	std::list<std::shared_ptr<BaseEnemy>> groundEnemyList;
	std::list<std::shared_ptr<BaseEnemy>> groundEnemyListRemove;

	std::list<std::shared_ptr<EnemySpawner>> spawnerList;

	static void ResetFindPath() { currentTimeFindPath = TimeFindPath };

	void Init() {
		spawnerList.push_back(std::make_shared<EnemySpawner>(300.f, 800.f, EnemyType::Buffalo, 0.f));
		spawnerList.push_back(std::make_shared<EnemySpawner>(-500.f, -500.f, EnemyType::Buffalo, 0.f));
		spawnerList.push_back(std::make_shared<EnemySpawner>(300.f, 800.f, EnemyType::Buffalo, 0.f));
		spawnerList.push_back(std::make_shared<EnemySpawner>(-500.f, -500.f, EnemyType::Buffalo, 3.f));
		spawnerList.push_back(std::make_shared<EnemySpawner>(300.f, 800.f, EnemyType::Buffalo, 0.f));
		spawnerList.push_back(std::make_shared<EnemySpawner>(-500.f, -500.f, EnemyType::Buffalo, 3.f));
		spawnerList.push_back(std::make_shared<EnemySpawner>(300.f, 800.f, EnemyType::Buffalo, 0.f));
		spawnerList.push_back(std::make_shared<EnemySpawner>(-500.f, -500.f, EnemyType::Buffalo, 3.f));
		spawnerList.push_back(std::make_shared<EnemySpawner>(300.f, 800.f, EnemyType::Buffalo, 0.f));
		spawnerList.push_back(std::make_shared<EnemySpawner>(-500.f, -500.f, EnemyType::Buffalo, 3.f));
		spawnerList.push_back(std::make_shared<EnemySpawner>(300.f, 800.f, EnemyType::Buffalo, 0.f));
		spawnerList.push_back(std::make_shared<EnemySpawner>(-500.f, -500.f, EnemyType::Buffalo, 3.f));
		spawnerList.push_back(std::make_shared<EnemySpawner>(300.f, 800.f, EnemyType::Buffalo, 0.f));
		spawnerList.push_back(std::make_shared<EnemySpawner>(-500.f, -500.f, EnemyType::Buffalo, 3.f));
		spawnerList.push_back(std::make_shared<EnemySpawner>(300.f, 800.f, EnemyType::Buffalo, 0.f));
		spawnerList.push_back(std::make_shared<EnemySpawner>(-500.f, -500.f, EnemyType::Buffalo, 3.f));
	}
	void Add(float x, float y, EnemyType type) {
		if (type == EnemyType::Buffalo) {
			std::shared_ptr<BaseEnemy> enemy;
			if (buffaloResources.empty()) enemy = std::make_shared<Buffalo>(x, y);
			else {
				enemy = buffaloResources.front();
				buffaloResources.pop_front();
				enemy->Set2DPosition(x, y);
			}
			groundEnemyList.push_back(enemy);
		}
		else if (type == EnemyType::Zombie) {
			std::shared_ptr<BaseEnemy> enemy;
			if (zombieResources.empty()) enemy = std::make_shared<Zombie>(x, y);
			else {
				enemy = zombieResources.front();
				zombieResources.pop_front();
				enemy->Set2DPosition(x, y);
			}
			groundEnemyList.push_back(enemy);
		}
	}
	void Spawn(float time) {
		if (!spawnerList.empty() && time >= spawnerList.front()->GetSpawnerTime()) {
			Add(spawnerList.front()->GetX(), spawnerList.front()->GetY(), spawnerList.front()->GetType());
			//std::cout << spawnerList.front()->GetX() <<"_" << spawnerList.front()->GetY() << std::endl;
			spawnerList.pop_front();
		}
	}
	void Update(float deltaTime) {
		currentTimeFindPath += deltaTime;
		if (currentTimeFindPath < 3) {
			for (auto enemy : flyEnemyList) {
				enemy->Update(deltaTime);
			}
			for (auto enemy : groundEnemyList) {
				enemy->Update(deltaTime);
			}
		}
		else {
			for (auto enemy : groundEnemyList) {
				enemy->FindTarget();
				enemy->Update(deltaTime);
			}
			for (auto enemy : flyEnemyList) {
				enemy->FindTarget();
				enemy->Update(deltaTime);
			}
			currentTimeFindPath = 0;
		}
	}
	void HandleTouchEvents(GLint x, GLint y, bool bIsPressed) {
		for (auto enemy : groundEnemyList) {
			//enemy->HandleTouchEvents(x, y, bIsPressed, tower);
		}
		for (auto enemy : flyEnemyList) {
			//enemy->HandleTouchEvents(x, y, bIsPressed, tower);
		}
	}
	void Draw() {
		for (auto enemy : groundEnemyList) {
			enemy->Draw();
		}
		for (auto enemy : flyEnemyList) {
			enemy->Draw();
		}
	}
	void RemoveFly(std::shared_ptr<BaseEnemy> enemy) {
		flyEnemyListRemove.push_back(enemy);
		buffaloResources.push_back(enemy);
		enemy->Reset();
	}
	void RemoveGround(std::shared_ptr<BaseEnemy> enemy) {
		groundEnemyListRemove.push_back(enemy);
		if (enemy->GetType() == EnemyType::Buffalo) {
			buffaloResources.push_back(enemy);
		}
		else if (enemy->GetType() == EnemyType::Zombie) {
			zombieResources.push_back(enemy);
		}
		enemy->Reset();
	}
	void RemoveFlyInstant(std::shared_ptr<BaseEnemy> enemy) {
		flyEnemyList.remove(enemy);
		enemy->Reset();
	}
	void RemoveGroundInstant(std::shared_ptr<BaseEnemy> enemy) {
		groundEnemyList.remove(enemy);
		if (enemy->GetType() == EnemyType::Buffalo) {
			buffaloResources.push_back(enemy);
		}
		else if (enemy->GetType() == EnemyType::Zombie) {
			zombieResources.push_back(enemy);
		}
		enemy->Reset();
	}
	void Remove() {
		for (auto enemy : groundEnemyListRemove) {
			groundEnemyList.remove(enemy);
		}
		groundEnemyListRemove.clear();
		for (auto enemy : flyEnemyListRemove) {
			flyEnemyList.remove(enemy);
		}
		flyEnemyListRemove.clear();
	}
	void Clear() {
		for (auto enemy : groundEnemyList) {
			RemoveGround(enemy);
		}
		for (auto enemy : flyEnemyList) {
			RemoveFly(enemy);
		}
	}
};
