#pragma once
#include "GroundEnemy.h"
class Zombie :public GroundEnemy
{
public:
	Zombie() {};
	Zombie(float x, float y);
	~Zombie();

	void Attack();
private:

};
