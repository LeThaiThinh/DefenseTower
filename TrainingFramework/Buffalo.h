#pragma once
#include "GroundEnemy.h"
class Buffalo:public GroundEnemy
{
public:
	Buffalo() {};
	Buffalo(float x, float y) ;
	~Buffalo();
	void Attack();
private:

};
