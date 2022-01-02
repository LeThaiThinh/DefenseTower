#pragma once
#include "GroundEnemy.h"
class EnemyOne :public GroundEnemy
{
public:
	EnemyOne() {};
	EnemyOne(float x, float y);
	~EnemyOne();
	void SpawnBullet();
private:

};
