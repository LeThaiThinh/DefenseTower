#pragma once
#include "MoveAble.h"
#include "SelfDestructable.h"
#include "Animation2D.h"
#include "../GameManager/ResourceManagers.h"
enum class BulletType
{
	MainCharacter
};
class Bullet :public MoveAble,public SelfDestructable,public Animation2D
{
	
public:
	Bullet();
	Bullet(BulletType bulletType);
	Bullet(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int numFrame, int numFramesInLine, float frameTime, float x, float y,Vector2 targetPosition);
	~Bullet();
	void Move(GLfloat deltatime) override;
	void SetTargetPosition(Vector2 targetPosition) { m_targetPosition = targetPosition; }
	void SetType(BulletType bulletType);
	void Init(BulletType bulletType);
	void Reset();
	void Update(float deltaTime);

protected:
	Vector2 m_targetPosition;
	BulletType m_bulletType;
	ObjectType m_targetType;
};
