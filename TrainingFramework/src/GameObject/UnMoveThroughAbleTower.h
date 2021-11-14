#pragma once
#include "../BaseDefensive.h"

class UnMoveThroughAbleTower :
	public BaseDefensive
{
public:
	UnMoveThroughAbleTower() :BaseDefensive() {};
	UnMoveThroughAbleTower(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture,
		float x, float y, int iwidth, int iheight, int width, int height, float range, float attackSpeed, float damage, float hitpoint, int level, TowerType type, int maxlevel)
		:BaseDefensive(model, shader, texture, x, y, iwidth, iheight, width, height, range, attackSpeed, damage, level, type, maxlevel, hitpoint, hitpoint) {}
	~UnMoveThroughAbleTower() {};

	std::shared_ptr<BaseEnemy> FindEnemyTarget();

	virtual	void	Attack();
	virtual void	Update(GLfloat deltatime);
	virtual	void	Reset() override;
	virtual	void	Upgrade() { BaseDefensive::Upgrade(); }

protected:
};