#include "MainCharacter.h"
#include "Bullet.h"

MainCharacter::MainCharacter() :Animation2D(15, 15, 0.1f,  300, 300),AttackAble(),BeAttackAble(),MoveAble()
{
	Init();
}

MainCharacter::~MainCharacter()
{
}

void MainCharacter::Init()
{
	SetModels(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"));
	SetTexture(ResourceManagers::GetInstance()->GetTexture("WormMonster.tga"));
	SetShaders(ResourceManagers::GetInstance()->GetShader("AnimationShader"));

	m_range = 100.f;
	m_attackSpeed = 5.f;
	m_speed = 200.f;
	m_hitpoint = 500.f;
	SetSize(50, 50);
	Set2DPosition(Globals::screenWidth / 2.f, Globals::screenWidth / 3.f);

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
	AttackAble::Update(deltatime);
}

void MainCharacter::AttackLinear(Vector2 targetPosition)
{
	if (CanAttack()) {
		m_timeAttack = 0;
		auto bullet= BulletPoolManager::GetInstance()->AddBullet(Vector2(m_position.x,m_position.y),targetPosition,BulletType::MainCharacter);
		bullet->SetDirection(Vector2(targetPosition.x - m_position.x, targetPosition.y - m_position.y).Normalize());

	}
}


bool MainCharacter::HandleTouchEvents(GLint x, GLint y, bool bIsPressed)
{
	bool isHandled = false;
	if (bIsPressed)
	{
		AttackLinear(Vector2((float)x, (float)y));
	}
	else
	{
		isHandled = true;
	}
	return isHandled;
}