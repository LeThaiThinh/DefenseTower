#pragma once
#include "Animation2D.h"
#include "MoveAble.h"
#include "AbleToAttack.h"
#include "AttackAble.h"
#include "BaseObject.h"
class BaseObject;
class BaseEnemy:
	public Animation2D,
	public MoveAble,
	public AbleToAttack,
	public AttackAble
{
public:
	BaseEnemy():m_currentTimeFindTarget(0), m_target(nullptr){}
	BaseEnemy(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int numFrame, int numFramesInLine, float frameTime,
		float x, float y, float width, float height,float speed , float range, float attackSpeed , float hitPoint, float timeFindTarget)
		:Animation2D(model,shader,texture,numFrame,numFramesInLine,frameTime,x,y,width,height),
		MoveAble(speed),AttackAble(hitPoint),AbleToAttack(range,attackSpeed) , m_currentTimeFindTarget(0), m_target(nullptr) {}
	~BaseEnemy(){}
	virtual std::shared_ptr<BaseObject> FindTarget()=0;
	virtual void Move()=0;
	virtual void Attack()=0;
	virtual void Update()=0;
	static float timeFindTarget;

protected:
	float m_currentTimeFindTarget;
	std::shared_ptr<BaseObject> m_target;
};
float BaseEnemy::timeFindTarget = 4;
