#pragma once
#include "ResourceManagers.h"

class MoveAble
{
protected:
	float	m_speed;
	std::shared_ptr<Texture> m_walkLeftAnimation;
	std::shared_ptr<Texture> m_walkRightAnimation;
	Vector3	m_direction;
	int		m_numFrameWalk;
	int		m_numFramesInLineWalk;
	float	m_frameTimeWalk;

public:
	MoveAble() :m_speed(0), m_direction(Vector3(0, 0, 0)), m_numFrameWalk(0), m_numFramesInLineWalk(0), m_frameTimeWalk(0) {}
	MoveAble(float speed, std::shared_ptr<Texture> walkLeft, std::shared_ptr<Texture> walkRight,int numFrames, int numFramesInLine, float frameTime) 
		:m_speed(speed),m_walkLeftAnimation(walkLeft),m_walkRightAnimation(walkRight),m_numFrameWalk(numFrames),m_numFramesInLineWalk(numFramesInLine),m_frameTimeWalk(frameTime) {}
	~MoveAble() {};

	void	SetSpeed(float speed) { m_speed = speed; }
	float	GetSpeed() { return m_speed; }
	void	SetDirection(Vector3 direction) { m_direction = direction; }
	void	AddDirection(Vector3 direction) { m_direction = (m_direction + direction).Normalize(); }
	Vector3	GetDirection() { return m_direction; }

	virtual void Move(GLfloat deltatime) = 0;
};

