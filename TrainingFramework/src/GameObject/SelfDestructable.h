#pragma once
class SelfDestructable
{
protected:
	float m_timeExist;
	float m_timeDestruct;
	float m_currentTimeExist;
public:
	SelfDestructable() :m_timeExist(0), m_timeDestruct(0), m_currentTimeExist(0) {};
	SelfDestructable(float timeExist, float timeDestruct) :m_timeExist(timeExist), m_timeDestruct(timeDestruct), m_currentTimeExist(0) {}
	bool IsExist() { return m_currentTimeExist < m_timeExist; }
	bool Update(float deltaTime) { return m_currentTimeExist += deltaTime; }
};

