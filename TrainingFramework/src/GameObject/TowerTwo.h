#pragma once
#include <UnMoveThroughAbleTower.h>
class TowerTwo
	:public UnMoveThroughAbleTower
{
public:
	TowerTwo();
	TowerTwo(float x, float y);
	~TowerTwo() {};

	void	Attack();
	void	Reset() override;
	void	LocateOption();
	void	Update(GLfloat deltatime);
	void	Upgrade() override;

private:

};
