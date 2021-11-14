#pragma once
#include "../BaseEnemy.h"
class GroundEnemy :public BaseEnemy
{
public:
	GroundEnemy() :BaseEnemy() {}
	GroundEnemy(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int numFrame, int numFramesInLine, float frameTime,
		float x, float y, int iwidth, int iheight, int width, int height, float speed, float range, float attackSpeed, float damage, float hitPoint, EnemyType type)
		:BaseEnemy(model, shader, texture, numFrame, numFramesInLine, frameTime, x, y, iwidth, iheight, width, height, speed, range, attackSpeed, damage, hitPoint, type) {}
	~GroundEnemy() {}

	virtual void Attack() override;

	void FindPath();
	std::shared_ptr<UnMoveThroughAbleTower> FindTarget() override;
	void Update(float deltaTim) override;
	bool CheckCollideTarget(GLfloat deltaTime);
protected:
	Vector3 m_start;
};
