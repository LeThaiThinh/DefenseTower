#pragma once
#include <Bullet/Bullet.h>

class BaseEnemy;
class Buffalo;
class BulletPoolManager : public CSingleton<BulletPoolManager>
{
public:
	std::list<std::shared_ptr<Bullet>> GetBullet() { return bulletList; };

	std::shared_ptr<Bullet> AddBullet(BulletType bulletType, std::shared_ptr<BaseObject> target, Vector3 targetPosition, std::shared_ptr<BaseObject> source) {
		std::shared_ptr<Bullet> bullet = getResource(bulletType, target, targetPosition, source);
		bulletList.push_back(bullet);
		return bullet;
	};
	void Update(float deltaTime) {
		for (auto &bullet : bulletList) {
			bullet->Move(deltaTime);
			bullet->Update(deltaTime);
			if (!bullet->IsExist()) {
				removeBulletList.push_back(bullet);
				returnResource(bullet);
			}
		}
	};
	void Remove() {
		for (auto &bullet : removeBulletList) {
			bulletList.remove(bullet);
		}
		removeBulletList.clear();
	}
	void RemoveBullet(std::shared_ptr<Bullet> bullet) {
		removeBulletList.push_back(bullet);
		resources.push_back(bullet);
		bullet->Reset();
	}
	void Draw() {
		for (auto &bullet : bulletList) {
			bullet->Draw();
			//std::cout << bullet->GetPosition().x << "-" << bullet->GetPosition().y << std::endl;
		}
	}
	std::shared_ptr<Bullet> getResource(BulletType bulletType, std::shared_ptr<BaseObject> target, Vector3 targetPosition, std::shared_ptr<BaseObject> source)
	{
		if (resources.empty())
		{
			return std::make_shared<Bullet>(bulletType, target, targetPosition, source);
		}
		else
		{
			std::shared_ptr<Bullet> resource = resources.front();
			resource->Init(bulletType, target, targetPosition, source);
			resources.pop_front();
			return resource;
		}
	}
	void returnResource(std::shared_ptr<Bullet> object)
	{
		resources.push_back(object);
	}

	void Clear() {
		for (auto &bullet : bulletList) {
			RemoveBullet(bullet);
		}
	}



	std::list<std::shared_ptr<Bullet>> bulletList;
	std::list<std::shared_ptr<Bullet>> removeBulletList;
	std::list<std::shared_ptr<Bullet>> resources;
};
