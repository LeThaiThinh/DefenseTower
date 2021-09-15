#pragma once
#include "Sprite2D.h"
#include "Animation2D.h"
#include "MoveAble.h"
#include "BeAttackAble.h"
#include "ShootAble.h"
#include "../GameManager/ResourceManagers.h"
#include <BulletManager.h>

class MainCharacter
	:public MoveAble,
	public Animation2D,
	public BeAttackAble,
	public AttackAble
{
public:

	MainCharacter();
	~MainCharacter();
	void Init();
	void Move(GLfloat deltatime);
	void Move(GLfloat deltatime, Vector2 vector2);
	void Update(GLfloat deltatime);
	void AttackLinear(Vector2 targetPosition) override;
	bool HandleTouchEvents(GLint x, GLint y, bool bIsPressed);
	void AttackCircular() {};

private:
};
