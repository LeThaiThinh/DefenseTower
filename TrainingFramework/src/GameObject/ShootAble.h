#pragma once
#include <CMath.h>
#include <list>
#include <Bullet.h>
#include <memory>
class ShootAble
{
protected:
	float range;
	float attackSpeed;
	std::list<std::shared_ptr<Bullet>> m_bulletList;
public:
	ShootAble() :m_bulletList(NULL), range(0),attackSpeed(1){}
	~ShootAble() {}
	virtual void ShootLinear(Vector2 targetPosition)=0;
	virtual void ShootCircular()=0;
};