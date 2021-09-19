#pragma once
#include "../BaseEnemy.h"
class FlyEnemy :public BaseEnemy
{
public:
	FlyEnemy() :BaseEnemy() {}
	FlyEnemy(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int numFrame, int numFramesInLine, float frameTime,
		float x, float y, float width, float height, float speed, float range, float attackSpeed, float hitPoint)
		:BaseEnemy(model, shader, texture, numFrame, numFramesInLine, frameTime, x, y, width, height, speed, range, attackSpeed, hitPoint) {}
	~FlyEnemy() {}
	std::shared_ptr<AttackAble> FindTarget() override;
	void Move() override;
	void Attack() override;
	void Update(float deltaTim) override;
private:

};
