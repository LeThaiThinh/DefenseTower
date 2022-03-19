#pragma once
#include "GroundEnemy.h"
class EnemyTwo :public GroundEnemy
{
public:
	EnemyTwo() {};
	EnemyTwo(float x, float y);
	~EnemyTwo();

	void SpawnBullet();
private:

};
