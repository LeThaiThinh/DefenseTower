#pragma once
#include "BaseDefensive.h"

class MoveThroughAbleTower :public BaseDefensive
{
public:
	MoveThroughAbleTower() :BaseDefensive() {};
	MoveThroughAbleTower(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture,
		float x, float y, int iwidth, int iheight, int width, int height, float range, float attackSpeed, float damage, float delayAttackTime,Vector3 bulletSpawner, std::shared_ptr<Texture> attackLeftAnimation, std::shared_ptr<Texture> attackRightAnimation, int level, TowerType type, int maxlevel)
		:BaseDefensive(model, shader, texture, x, y, iwidth, iheight, width, height, range, attackSpeed, damage, delayAttackTime, bulletSpawner, attackLeftAnimation, attackRightAnimation, level,type,maxlevel) {}
	~MoveThroughAbleTower() {};
	void	Attack() {};
	void	Update(GLfloat deltatime) {
		AbleToAttack::Update(deltatime);
		Sprite2D::Update(deltatime);
	};
private:
};