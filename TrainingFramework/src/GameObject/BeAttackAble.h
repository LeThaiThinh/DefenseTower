#pragma once
#include <CMath.h>
class BeAttackAble
{
protected:
	float	m_hitpoint;
public:
	BeAttackAble() :m_hitpoint(0) {}
	void	SetHitPoint(int hitpoint) { m_hitpoint = hitpoint; }
	float		GetHitPoint() { return m_hitpoint; }

};
