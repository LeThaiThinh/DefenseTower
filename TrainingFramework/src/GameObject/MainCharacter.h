#pragma once
#include "Base/Sprite2D.h"
#include "Base/Animation2D.h"
#include "Base/MoveAble.h"
#include "Base/AttackAble.h"
#include "Base/AbleToAttack.h"
#include "../GameManager/ResourceManagers.h"
#include <Bullet/BulletManager.h>
#include <Defensive/UnMoveThroughAbleTower.h>

class MainCharacter
	:public MoveAble,
	public Animation2D,
	public AttackAble,
	public AbleToAttack,
	public CSingleton<MainCharacter>
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
	bool HandleTouchHUD(GLint x, GLint y, bool bIsPressed);
	void AttackCircular() {};
	bool CheckCollide(GLfloat deltaTime);
	void Draw() { Animation2D::Draw(); AttackAble::Draw(); };
private:
	Vector3 m_targetPosition;
	bool m_isHolding;
};
