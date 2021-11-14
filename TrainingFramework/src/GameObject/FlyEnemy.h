#pragma once
#include "../BaseEnemy.h"
class FlyEnemy :public BaseEnemy
{
public:
	FlyEnemy() :BaseEnemy() {}
	FlyEnemy(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int numFrame, int numFramesInLine, float frameTime,
		float x, float y, int iwidth, int iheight, int width, int height, float speed, float range, float attackSpeed, float damage, float hitPoint, EnemyType type)
		:BaseEnemy(model, shader, texture, numFrame, numFramesInLine, frameTime, x, y, iwidth, iheight, width, height, speed, range, attackSpeed, damage, hitPoint, type) {}
	~FlyEnemy() {}
	std::shared_ptr<UnMoveThroughAbleTower> FindTarget() override;
	void Attack() override;
	void Update(float deltaTim) override;
private:

};
