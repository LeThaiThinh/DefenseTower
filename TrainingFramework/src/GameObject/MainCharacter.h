#pragma once
#include "Sprite2D.h"
#include "Animation2D.h"
#include "MoveAble.h"
#include "AttackAble.h"
#include "AbleToAttack.h"
#include "ResourceManagers.h"
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
	void Move(GLfloat deltatime, Vector3 vector);
	void Update(GLfloat deltatime);
	void Attack() override;
	void SpawnBullet();
	void AttackLinear();
	bool HandleTouchEvents(GLint x, GLint y, bool bIsPressed);
	void AttackCircular() {};
	bool CheckCollide(GLfloat deltaTime);
	void Draw() { Animation2D::Draw(); AttackAble::Draw(); };
private:
	Vector3 m_targetPosition;
};
