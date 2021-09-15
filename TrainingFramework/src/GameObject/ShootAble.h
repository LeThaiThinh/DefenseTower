#pragma once
#include <CMath.h>
#include <list>
#include <Bullet.h>
#include <memory>
class ShootAble
{
protected:
	std::list<std::shared_ptr<Bullet>> m_bulletList;
public:
	ShootAble() :m_bulletList(NULL) {}
	~ShootAble() {}
};