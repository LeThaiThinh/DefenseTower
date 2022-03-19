#pragma once
#include "UnMoveThroughAbleTower.h"

class UnMoveThroughAbleTower;
class MainTower :public UnMoveThroughAbleTower
{
public:
	MainTower();
	MainTower(float x, float y);
	~MainTower() {};
	void	Attack();
	void	LocateOption();
	void	Reset();
	void	Update(GLfloat deltatime);
	void	Upgrade() override;

private:

};