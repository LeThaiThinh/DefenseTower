#pragma once
#include <../BaseTower.h>

class TowerPoolManager : public CSingleton<TowerPoolManager>
{
public:

	void AddTower(std::shared_ptr<BaseTower> bullet) {
		//m_bulletList.push_back(bullet);
	};
	std::shared_ptr<BaseTower> AddBullet(TowerType towerType) {
		std::shared_ptr<BaseTower> bullet = getResource(towerType);
		m_bulletList.push_back(bullet);
		return bullet;
	};
	void Update(float deltaTime) {
		MoveAndUpdateBullet(deltaTime);
		RemoveBullet();
	};
	void MoveAndUpdateBullet(float deltaTime) {
		for (auto bullet : m_bulletList) {
			bullet->Update(deltaTime);
		}
	};
	void RemoveBullet() {
		for (auto bullet : m_removeBulletList) {
			m_bulletList.remove(bullet);
		}
		m_removeBulletList.clear();
	}
	void Draw() {
		for (auto bullet : m_bulletList) {
			bullet->Draw();
		}
	}
	std::shared_ptr<BaseTower> getResource(TowerType type)
	{
		if (resources.empty())
		{
			return std::make_shared<BaseTower>(type);
		}
		else
		{
			std::shared_ptr<BaseTower> resource = resources.front();
			resource->SetType(type);
			resources.pop_front();
			return resource;
		}
	}
	void returnResource(std::shared_ptr<BaseTower> object)
	{
		object->Reset();
		resources.push_back(object);
	}

private:
	std::shared_ptr<BaseTower> mainTower;
	std::list<std::shared_ptr<BaseTower>> m_bulletList;
	std::list<std::shared_ptr<BaseTower>> m_removeBulletList;
	std::list<std::shared_ptr<BaseTower>> resources;
};
