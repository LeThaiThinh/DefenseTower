#pragma once
#include <Bullet.h>

class BulletPoolManager : public CSingleton<BulletPoolManager>
{
public:

	void AddBullet(std::shared_ptr<Bullet> bullet) {
		//m_bulletList.push_back(bullet);
	};
	std::shared_ptr<Bullet> AddBullet(BulletType bulletType) {
		std::shared_ptr<Bullet> bullet = getResource(bulletType);
		m_bulletList.push_back(bullet);
		return bullet;
	};
	void Update(float deltaTime) {
		MoveAndUpdateBullet(deltaTime);
		RemoveBullet();
	};
	void MoveAndUpdateBullet(float deltaTime) {
		for (auto bullet : m_bulletList) {
			bullet->Move(deltaTime);
			bullet->Update(deltaTime);
			if (!bullet->IsExist()) {
				m_removeBulletList.push_back(bullet);
				GetInstance()->returnResource(bullet);
			}
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
	std::shared_ptr<Bullet> getResource(BulletType type)
	{
		if (resources.empty())
		{
			return std::make_shared<Bullet>(type);
		}
		else
		{
			std::shared_ptr<Bullet> resource = resources.front();
			resource->SetType(type);
			resources.pop_front();
			return resource;
		}
	}
	void returnResource(std::shared_ptr<Bullet> object)
	{
		object->Reset();
		resources.push_back(object);
	}

private:
	std::list<std::shared_ptr<Bullet>> m_bulletList;
	std::list<std::shared_ptr<Bullet>> m_removeBulletList;
	std::list<std::shared_ptr<Bullet>> resources;
};
