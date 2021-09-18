#pragma once
#include "UnMoveThroughAbleTower.h"
class UnMoveThroughAbleTower;
class MainTower:public UnMoveThroughAbleTower
{
public:
	MainTower();
	~MainTower() {};
	void	Attack() ;
	void	Reset() ;
	void	Update(GLfloat deltatime);
private:

};