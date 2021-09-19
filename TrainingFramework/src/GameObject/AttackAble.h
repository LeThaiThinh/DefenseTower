#pragma once
#include <CMath.h>
class AttackAble
{
protected:
	float	m_hitpoint;
public:
	AttackAble() :m_hitpoint(0) {}
	AttackAble(float hitpoint):m_hitpoint(hitpoint){}
	~AttackAble(){}
	void		SetHitPoint(float hitpoint) { m_hitpoint = hitpoint; }
	float		GetHitPoint() { return m_hitpoint; }
	bool		IsDestroyed() { return m_hitpoint <= 0; }
};
