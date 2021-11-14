#pragma once
#include <CMath.h>
class MoveAble
{
protected:
	float	m_speed;
	Vector3	m_direction;
public:
	MoveAble() :m_speed(0), m_direction(Vector3(0, 0, 0)) {}
	MoveAble(float speed) :m_speed(speed) {}
	~MoveAble() {};

	void	SetSpeed(float speed) { m_speed = speed; }
	float	GetSpeed() { return m_speed; }
	void	SetDirection(Vector3 direction) { m_direction = direction; }
	void	AddDirection(Vector3 direction) { m_direction = (m_direction + direction).Normalize(); }
	Vector3	GetDirection() { return m_direction; }

	virtual void Move(GLfloat deltatime) = 0;
};

