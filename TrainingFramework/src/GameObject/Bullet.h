#pragma once
#include "MoveAble.h"
#include "SelfDestructable.h"
class Bullet :public MoveAble, SelfDestructable
{

public:
	Bullet();
	~Bullet();
	void Move(GLfloat deltatime) override;
private:

};
