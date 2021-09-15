#pragma once
#include <CMath.h>
class MoveAble
{
protected:
	float	m_speed;
	Vector2	m_direction;
	Vector2	m_destination;
public:
	MoveAble() :m_speed(0), m_destination(Vector2(0, 0)),m_direction(Vector2(0,0)) {}
	void	SetSpeed(float speed) { m_speed = speed; }
	float	GetSpeed() { return m_speed; }
	void	SetDirection(Vector2 direction) { m_direction = direction; }
	void	AddDirection(Vector2 direction) { m_direction = (m_direction+ direction).Normalize(); }
	Vector2	GetDirection() { return m_direction; }
	virtual void Move(GLfloat deltatime) = 0;
};

