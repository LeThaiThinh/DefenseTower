#pragma once
#include "Sprite2D.h"
#include "Animation2D.h"
#include "MoveAble.h"
#include "../GameObject/AttackAble.h"
#include "../GameObject/AbleToAttack.h"
#include "../GameManager/ResourceManagers.h"
#include <BulletManager.h>
#include <UnMoveThroughAbleTower.h>

class MainCharacter
	:public MoveAble,
	public Animation2D,
	public AttackAble,
	public AbleToAttack
{
public:

	MainCharacter();
	~MainCharacter();
	void Init();
	void Move(GLfloat deltatime);
	void Move(GLfloat deltatime, Vector2 vector2);
	void Update(GLfloat deltatime);
	void Attack() override;
	void AttackLinear();
	bool HandleTouchEvents(GLint x, GLint y, bool bIsPressed);
	void AttackCircular() {};
	bool CheckCollide(GLfloat deltaTime);
private:
	Vector2 m_targetPosition;
};
