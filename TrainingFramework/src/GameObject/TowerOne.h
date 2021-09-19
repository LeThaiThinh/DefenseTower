#pragma once
#include <UnMoveThroughAbleTower.h>
#include "ObjectPoolManager.h"
class TowerOne
	:public UnMoveThroughAbleTower
{
public:
	TowerOne();
	TowerOne(float x,float y);
	~TowerOne() {};

	void	Attack();
	void	Reset();
	void	Update(GLfloat deltatime);
private:

};
