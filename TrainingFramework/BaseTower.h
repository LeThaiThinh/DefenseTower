#pragma once
#include "../GameObject/AttackAble.h"
#include "../GameObject/AbleToAttack.h"
enum TowerType
{
	UnMoveThroughAble,
	MoveThroughAble
};
class BaseTower:
	public AttackAble,
	public AbleToAttack,
	public Sprite2D
{
public:
	BaseTower():AttackAble(),AbleToAttack(),Sprite2D(){}
	BaseTower(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, float x, float y, float width, float height, float range, float attackSpeed, float hitpoint)
		:Sprite2D(model, shader, texture,x,y,  width,  height), AbleToAttack(range, attackSpeed), AttackAble(hitpoint) {}
	~BaseTower(){}

	virtual void	Attack() = 0;
	virtual void	Reset() =0;
	virtual void	Update(GLfloat deltatime)=0 ;
	virtual void	SetType(TowerType type) = 0;
private:
};
