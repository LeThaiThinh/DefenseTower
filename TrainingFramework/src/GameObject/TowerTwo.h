#pragma once
#include <UnMoveThroughAbleTower.h>
#include "ObjectPoolManager.h"
class TowerTwo
	:public UnMoveThroughAbleTower
{
public:
	TowerTwo();
	TowerTwo(float x, float y);
	~TowerTwo() {};

	void	Attack();
	void	Reset();
	void	Update(GLfloat deltatime);
private:

};
