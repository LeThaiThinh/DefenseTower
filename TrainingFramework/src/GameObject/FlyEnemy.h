#pragma once
#include "BaseEnemy.h"
class FlyEnemy :public BaseEnemy
{
public:
	FlyEnemy() :BaseEnemy() {}
	FlyEnemy(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> textureLeft, std::shared_ptr<Texture> textureRight, int numFrame, int numFramesInLine, float frameTime,
		float x, float y, int iwidth, int iheight, int width, int height, float speed, float range, float attackSpeed, float damage, float delayAttackTime,Vector3 bulletSpawner, 
		std::shared_ptr<Texture> attackLeftAnimation, std::shared_ptr<Texture> attackRightAnimation, int numFrameAttack, int numFramesInLineAttack, float frameTimeAttack, float hitPoint, EnemyType type, int bounty)
		:BaseEnemy(model, shader, textureLeft,textureRight, numFrame, numFramesInLine, frameTime, x, y, iwidth, iheight, width, height, speed, range, attackSpeed, damage, delayAttackTime, bulletSpawner, 
			attackLeftAnimation, attackRightAnimation,numFrameAttack,numFramesInLineAttack,frameTimeAttack, hitPoint, type,bounty) {}
	~FlyEnemy() {}
	void FindPath() override;
	virtual void SpawnBullet() = 0;
	void Update(float deltaTim) override;
private:

};
