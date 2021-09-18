#include "MainCharacter.h"
#include "Bullet.h"
#include "Application.h"
MainCharacter::MainCharacter() :Animation2D(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"), 
	ResourceManagers::GetInstance()->GetShader("AnimationShader"),
	ResourceManagers::GetInstance()->GetTexture("WormMonster.tga"),
	15, 15, 0.2f,  300.f, 300.f,50.f,50.f),
	AbleToAttack(100.f,5.f),AttackAble(500.f),MoveAble(200.f)
{
	Init();
}

MainCharacter::~MainCharacter()
{
}

void MainCharacter::Init()
{
}

void MainCharacter::Move(GLfloat deltatime)
{
}
void MainCharacter::Move(GLfloat deltatime, Vector2 direction)
{
	SetDirection(direction);
	Set2DPosition(m_position.x + deltatime * m_speed * m_direction.x, m_position.y + deltatime * m_speed * m_direction.y);
}

void MainCharacter::Update(GLfloat deltatime)
{
	Animation2D::Update(deltatime);
	AbleToAttack::Update(deltatime);
}

void MainCharacter::Attack()
{
	if (CanAttack()) {
		AttackLinear();
	}
}
void MainCharacter::AttackLinear()
{
	m_timeAttack = 0;
	auto bullet = BulletPoolManager::GetInstance()->AddBullet(BulletType::MainCharacter);
	bullet->SetDirection(Vector2(m_targetPosition.x - m_position.x, m_targetPosition.y - m_position.y).Normalize());
	bullet->SetTargetPosition(m_targetPosition);
	bullet->Set2DPosition(m_position.x, m_position.y);
}

bool MainCharacter::HandleTouchEvents(GLint x, GLint y, bool bIsPressed)
{
	bool isHandled = false;
	if (bIsPressed)
	{
		m_targetPosition = Vector2((float)x, (float)y);
		Attack();
	}
	else
	{
		isHandled = true;
	}
	return isHandled;
}