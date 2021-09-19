#pragma once
#include "../BaseTower.h"
class UnMoveThroughAbleTower :
	public BaseTower,
	public AttackAble
{
public:
	UnMoveThroughAbleTower() :BaseTower(),AttackAble() {};
	UnMoveThroughAbleTower(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture,  float x, float y, float width, float height, float range, float attackSpeed, float hitpoint,int level )
		:BaseTower(model, shader, texture, x, y, width, height, range, attackSpeed, level),AttackAble(hitpoint) {}
	~UnMoveThroughAbleTower() {};

	void	Attack();
	void	Update(GLfloat deltatime);
private:

};