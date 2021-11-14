#pragma once
#include "../BaseTower.h"

class MoveThroughAbleTower :public BaseTower
{
public:
	MoveThroughAbleTower() :BaseTower() {};
	MoveThroughAbleTower(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, float range, float attackSpeed, float x, float y, float width, float height, int level)
		:BaseTower(model, shader, texture, x, y, width, height, range, attackSpeed, level) {}
	~MoveThroughAbleTower() {};
	void	Attack() {};
	void	Update(GLfloat deltatime) {
		AbleToAttack::Update(deltatime);
		Sprite2D::Update(deltatime);
	};
private:
};