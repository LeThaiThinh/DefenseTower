#pragma once
#include "../BaseEnemy.h"
class EnemySpawner
{
public:
	EnemySpawner() : m_x(0), m_y(0), m_type(), m_spawnTime(0) {};
	EnemySpawner(float x, float y, EnemyType type, float spawnTime) :m_x(x), m_y(y), m_type(type), m_spawnTime(spawnTime) {}
	~EnemySpawner() {};
	float GetSpawnerTime() { return m_spawnTime; }
	float GetX() { return m_x; }
	float GetY() { return m_y; }
	EnemyType GetType() { return m_type; }

private:
	float m_x;
	float m_y;
	EnemyType m_type;
	float m_spawnTime;
};
