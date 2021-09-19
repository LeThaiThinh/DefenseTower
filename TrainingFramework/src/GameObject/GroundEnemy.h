#pragma once
#include "../BaseEnemy.h"
#include "../../BaseTower.h"
class GroundEnemy:public BaseEnemy
{
public:
	GroundEnemy():BaseEnemy(){}
	GroundEnemy(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int numFrame, int numFramesInLine, float frameTime,
		float x, float y, float width, float height, float speed, float range, float attackSpeed, float hitPoint)
		:BaseEnemy(model, shader, texture, numFrame, numFramesInLine, frameTime, x, y, width, height, speed, range, attackSpeed, hitPoint){}
	~GroundEnemy(){}
	std::shared_ptr<AttackAble> FindTarget() override ;
	void Move() override;
	void Attack() override;
	void Update(float deltaTim) override;
private:

};
