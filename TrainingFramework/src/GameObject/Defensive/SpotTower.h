#pragma once
#include "BaseDefensive.h"
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
	void	Draw() { Sprite2D::Draw();  m_towerOption->Draw(); };
	void	Update(GLfloat deltatime);

private:

};
