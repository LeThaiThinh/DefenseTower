#pragma once
#include "../BaseTower.h"
class MoveThroughAbleTower :public BaseTower
{
public:
	MoveThroughAbleTower():BaseTower() {};
	MoveThroughAbleTower(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, float range, float attackSpeed, float hitpoint, float x, float y, float width, float height)
		:BaseTower(model, shader, texture, x, y, width, height, range, attackSpeed, hitpoint) {}
	~MoveThroughAbleTower() {};
	void	Attack() {};
	void	Reset() {};
	void	Update(GLfloat deltatime) {
		AbleToAttack::Update(deltatime);
	};
	void	SetType(TowerType type) {};

private:

};