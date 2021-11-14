#pragma once
#include "../BaseDefensive.h"
class SpotTower
	:public BaseDefensive
{
public:
	SpotTower();
	SpotTower(float x, float y);
	~SpotTower();
	void	Reset();
	void	Attack() {}
	void	LocateOption();
	void	Update(GLfloat deltatime);

private:

};
