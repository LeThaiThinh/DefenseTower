#pragma once
#include <UnMoveThroughAbleTower.h>
#include "ObjectPoolManager.h"
class SpotTower
	:public BaseTower
{
public:
	SpotTower();
	~SpotTower() {};
	void	Attack(){}
	void	Update(GLfloat deltatime);
private:

};
