#pragma once
#include "Base/MoveAble.h"
#include "Base/SelfDestructable.h"
#include "Base/Animation2D.h"
#include "../GameManager/ResourceManagers.h"

class UnMoveThroughAbleTower;
class BaseEnemy;
enum class BulletType
{
	Linear_MainCharacter,
	AOE,
	Target_Tower_One,
	TowerTwo,
	TowerThree,
	Chain,
	Target_Enemy_Two,
};
class Bullet :public MoveAble, public SelfDestructable, public Animation2D
{

public:
	Bullet();
	Bullet(BulletType bulletType, std::shared_ptr<BaseObject> target, Vector3 targetPosition, std::shared_ptr<BaseObject> source);
	Bullet(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int numFrame, int numFramesInLine, float frameTime, float x, float y, int iwidth, int iheight, int width, int height, Vector3 targetPosition, BulletType m_bulletType, std::weak_ptr<BaseObject> source);
	Bullet(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int numFrame, int numFramesInLine, float frameTime, float x, float y, int iwidth, int iheight, int width, int height, std::weak_ptr<BaseObject> target, BulletType m_bulletType, std::weak_ptr<BaseObject> source);

	~Bullet();
	void SetTargetPosition(Vector3 targetPosition) { m_targetPosition = targetPosition; }
	BulletType GetType() { return m_bulletType; }

	void Move(GLfloat deltatime) override;
	void Init(BulletType bulletType, std::shared_ptr<BaseObject> target, Vector3 targetPosition, std::shared_ptr<BaseObject> source);
	void Update(float deltaTime);
	std::shared_ptr<BaseEnemy> CheckCollideGroundEnemy(GLfloat deltaTime);
	std::shared_ptr<BaseEnemy> CheckCollideFlyEnemy(GLfloat deltaTime);
	std::shared_ptr<BaseEnemy> CheckCollideEnemyTarget(GLfloat deltaTime);
	std::shared_ptr<UnMoveThroughAbleTower> CheckCollideTower(GLfloat deltaTime);
	std::shared_ptr<UnMoveThroughAbleTower> CheckCollideTarget(GLfloat deltaTime);
	void Reset() {
		m_source.reset();
		m_target.reset();
		m_targetPosition = Vector3(0, 0, 0);
	};
protected:
	Vector3 m_targetPosition;
	BulletType m_bulletType;
	float m_damage;
	std::weak_ptr<BaseObject> m_target;
	std::weak_ptr<BaseObject> m_source;
};
