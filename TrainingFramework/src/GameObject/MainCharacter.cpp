#include "MainCharacter.h"
#include "Bullet.h"
#include "Application.h"
#include "DefensiveManager.h"
#include "../../BaseEnemy.h"
#include "../Buffalo.h"
MainCharacter::MainCharacter() :Animation2D(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"),
	ResourceManagers::GetInstance()->GetShader("AnimationShader"),
	ResourceManagers::GetInstance()->GetTexture("WormMonster.tga"),
	15, 15, 0.2f, 300.f, 300.f, 30, 30, 30, 30),
	AbleToAttack(100.f, 5.f, 10), AttackAble(500.f, 500.f), MoveAble(50.f)
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
void MainCharacter::Move(GLfloat deltatime, Vector3 direction)
{
	SetDirection(direction);
	if (!CheckCollide(deltatime)) {
		Set2DPosition(m_position.x + deltatime * m_speed * m_direction.x, m_position.y + deltatime * m_speed * m_direction.y);
	}
}

void MainCharacter::Update(GLfloat deltatime)
{
	Animation2D::Update(deltatime);
	AbleToAttack::Update(deltatime);
	AttackAble::UpdateHitPointBarAndLostHitpointBarSize();
	AttackAble::UpdateHitPointBarAndLostHitpointBarPosition(m_position.x, m_position.y - m_iHeight);
}

void MainCharacter::Attack()
{
	if (CanAttack()) {
		AttackLinear();
	}
}
void MainCharacter::AttackLinear()
{
	m_currentTimeAttack = 0;
	BulletPoolManager::GetInstance()->AddBullet(
		BulletType::Linear_MainCharacter, std::dynamic_pointer_cast<BaseObject>(std::make_shared<Buffalo>()),
		m_targetPosition, shared_from_this());
}

bool MainCharacter::HandleTouchEvents(GLint x, GLint y, bool bIsPressed)
{
	bool isHandled = false;
	if (bIsPressed)
	{
		m_targetPosition = Vector3((float)x, (float)y, 0);
		Attack();
	}
	else
	{
		isHandled = true;
	}
	return isHandled;
}

bool MainCharacter::CheckCollide(GLfloat deltaTime)
{
	for (auto tower : DefensivePoolManager::GetInstance()->spotList) {
		if ((tower->GetPosition().x + tower->GetWidth() / 2 > m_position.x - m_width / 2 + deltaTime * m_speed * m_direction.x) && (tower->GetPosition().x - tower->GetWidth() / 2 < m_position.x + m_width / 2 + deltaTime * m_speed * m_direction.x)
			&& (tower->GetPosition().y + tower->GetIHeight() / 2 > m_position.y - m_height / 2 + deltaTime * m_speed * m_direction.y) && (tower->GetPosition().y + tower->GetIHeight() / 2 - tower->GetHeight() < m_position.y + m_height / 2 + deltaTime * m_speed * m_direction.y))
		{
			return true;
		}

	}
	for (auto tower : DefensivePoolManager::GetInstance()->unMoveThroughAbleTowerList) {
		if ((tower->GetPosition().x + tower->GetWidth() / 2 > m_position.x - m_width / 2 + deltaTime * m_speed * m_direction.x) && (tower->GetPosition().x - tower->GetWidth() / 2 < m_position.x + m_width / 2 + deltaTime * m_speed * m_direction.x)
			&& (tower->GetPosition().y + tower->GetIHeight() / 2 > m_position.y - m_height / 2 + deltaTime * m_speed * m_direction.y) && (tower->GetPosition().y + tower->GetIHeight() / 2 - tower->GetHeight() < m_position.y + m_height / 2 + deltaTime * m_speed * m_direction.y))
		{
			return true;
		}
	}
	return false;
}
