#pragma once
#include "BaseEnemy.h"
class GroundEnemy :public BaseEnemy
{
public:
	GroundEnemy() :BaseEnemy() {}
	GroundEnemy(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader,  std::shared_ptr<Texture> textureLeft, std::shared_ptr<Texture> textureRight, int numFrame, int numFramesInLine, float frameTime,
		float x, float y, int iwidth, int iheight, int width, int height, float speed, float range, float attackSpeed, float damage, float delayAttackTime,Vector3 bulletSpawner, 
		std::shared_ptr<Texture> attackLeftAnimation, std::shared_ptr<Texture> attackRightAnimation, int numFrameAttack, int numFramesInLineAttack, float frameTimeAttack, float hitPoint, EnemyType type, int bounty)
		:BaseEnemy(model, shader, textureLeft,textureRight , numFrame, numFramesInLine, frameTime, x, y, iwidth, iheight, width, height, speed, range, attackSpeed, damage,delayAttackTime, bulletSpawner,
			attackLeftAnimation,attackRightAnimation,numFrameAttack,numFramesInLineAttack,frameTimeAttack, hitPoint, type,bounty) {}
	~GroundEnemy() {}

	virtual void SpawnBullet()=0;
	void FindPath();
	void Update(float deltaTim) override;
protected:
};
