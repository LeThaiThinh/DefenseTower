#pragma once
#include "GroundEnemy.h"
class EnemyThree :public GroundEnemy
{
public:
	EnemyThree() {};
	EnemyThree(float x, float y);
	~EnemyThree();
	void SpawnBullet();
private:

};
