#pragma once
#include <Defensive/UnMoveThroughAbleTower.h>
class TowerOne
	:public UnMoveThroughAbleTower
{
public:
	TowerOne();
	TowerOne(float x, float y);
	~TowerOne() {};

	void	Attack();
	void	Reset() override;
	void	Upgrade() override;
	void	LocateOption();
	void	Update(GLfloat deltatime);

private:

};
