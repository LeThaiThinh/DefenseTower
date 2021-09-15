#pragma once
class SelfDestructable
{
protected:
	float m_timeExist;
	float m_timeDestruct;
	float m_time;
public:
	SelfDestructable() :m_timeExist(0), m_timeDestruct(0), m_time(0) {};
	SelfDestructable(float timeExist, float timeDestruct) :m_timeExist(timeExist), m_timeDestruct(timeDestruct), m_time(0) {}
	bool IsExist() { return m_time < m_timeExist; }
};

