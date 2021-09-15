#pragma once
#include <CMath.h>
class AttackAble
{
protected:
	int	m_hitpoint;
public:
	AttackAble() :m_hitpoint(0) {}
	void	SetHitPoint(int hitpoint) { m_hitpoint = hitpoint; }
	int		GetHitPoint() { return m_hitpoint; }

};
