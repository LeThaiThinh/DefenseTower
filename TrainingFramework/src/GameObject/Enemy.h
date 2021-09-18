#pragma once
#include "Animation2D.h"
#include "../../BaseEnemy.h"
enum class EnemyType
{
	WormMonster,
	MoveThroughAble
};
class Enemy
{
public:

	Enemy(std::shared_ptr <BaseEnemy> enemy) :m_enemy(enemy) {};
	~Enemy();

	void	Attack();
	void	Reset();
	void	Draw();
	void	Update(GLfloat deltatime);
	void	setState(EnemyType state);
	std::shared_ptr<BaseEnemy> getState();
private:
	std::shared_ptr <BaseEnemy> m_enemy;
	EnemyType enemyType;
};