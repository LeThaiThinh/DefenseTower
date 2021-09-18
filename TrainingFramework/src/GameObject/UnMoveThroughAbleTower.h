#pragma once
#include "../BaseTower.h"
class UnMoveThroughAbleTower :public BaseTower
{
public:
	UnMoveThroughAbleTower() :BaseTower() {};
	UnMoveThroughAbleTower(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture,  float x, float y, float width, float height, float range, float attackSpeed, float hitpoint )
		:BaseTower(model, shader, texture, x, y, width, height, range, attackSpeed, hitpoint) {}
	~UnMoveThroughAbleTower() {};

	void	Attack() {};
	void	Reset() {};
	void	Update(GLfloat deltatime) {
		AbleToAttack::Update(deltatime);
		Sprite2D::Update(deltatime);
	};
	void	SetType(TowerType type) {};
private:

};