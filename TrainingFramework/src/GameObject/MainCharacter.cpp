#include "MainCharacter.h"
#include "Bullet/Bullet.h"
#include "Application.h"
#include "Defensive/DefensiveManager.h"
#include "Enemy/BaseEnemy.h"
#include "Enemy/EnemyOne.h"
MainCharacter::MainCharacter() :Animation2D(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"),
	ResourceManagers::GetInstance()->GetShader("AnimationShader"),
	ResourceManagers::GetInstance()->GetTexture("MainCharacter/main_character_walk_left.tga"),
	6, 6, 0.5f, 300.f, 300.f, 50, 50, 50, 50),
	AbleToAttack(600.f, 2.f, 10.f, 0.3f, Vector3(0, 0, 0), ResourceManagers::GetInstance()->GetTexture("MainCharacter/main_character_walk_attack_left.tga"), ResourceManagers::GetInstance()->GetTexture("MainCharacter/main_character_walk_attack_right.tga")),
	AttackAble(500.f, 500.f), 
	MoveAble(100.f, ResourceManagers::GetInstance()->GetTexture("MainCharacter/main_character_walk_left.tga"),ResourceManagers::GetInstance()->GetTexture("MainCharacter/main_character_walk_right.tga"),3,3,0.1f),
	m_isHolding(false)
{
	Init();
}

MainCharacter::~MainCharacter()
{
}

void MainCharacter::Init()
{
	m_typeObject = "Enemy";
	SetName("Witch");
	SetAvatar(ResourceManagers::GetInstance()->GetTexture("MainCharacter/main_character_avatar.tga"));
}

void MainCharacter::Move(GLfloat deltatime)
{
}
void MainCharacter::Move(GLfloat deltatime, Vector3 direction)
{
	SetDirection(direction);
	if (direction.x >= 0 && !m_isCastingAttack)
		m_pTexture = m_walkRightAnimation;
	else if (direction.x < 0&& !m_isCastingAttack)
		m_pTexture = m_walkLeftAnimation;
	if (!CheckCollide(deltatime)) {
		Set2DPosition(m_position.x + deltatime * m_speed * m_direction.x, m_position.y + deltatime * m_speed * m_direction.y);
	}
}

void MainCharacter::Update(GLfloat deltatime)
{
	Animation2D::Update(deltatime);
	AbleToAttack::Update(deltatime);
	//AttackAble::UpdateHitPointBarAndLostHitpointBarSize();
	//AttackAble::UpdateHitPointBarAndLostHitpointBarPosition(m_position.x, m_position.y - m_iHeight);
	if (m_currentTimeAttack >= m_delayAttackTime/2 && m_isCastingAttack) {
		m_isCastingAttack = false;
		SpawnBullet();
	}
	if (m_currentTimeAttack >= m_delayAttackTime ) {
		m_frameTime = 0.5f;
		if (m_pTexture == m_attackLeftAnimation) {
			m_pTexture = m_walkLeftAnimation;
		}
		else if(m_pTexture == m_attackRightAnimation) {
			m_pTexture = m_walkRightAnimation;
		}
	}
}

void MainCharacter::Attack()
{
	if (CanAttack()) {
		AttackLinear();
	}
}
void MainCharacter::SpawnBullet()
{
	if (GSMenu::sfx)
		ResourceManagers::GetInstance()->GetSound("maincharacter_attack.mp3")
		->PlaySoundFromStart(false, irrklang::vec3df((m_position.x - Application::GetInstance()->GetCamera()->GetPosition().x - Globals::mapWidth / 2) / SOUND_DISTANCE_UNIT,
			(m_position.x - Application::GetInstance()->GetCamera()->GetPosition().x - Globals::screenHeight / 2) / 200, 0));

	BulletPoolManager::GetInstance()->AddBullet(
		BulletType::Linear_MainCharacter, std::dynamic_pointer_cast<BaseEnemy>(std::make_shared<EnemyOne>()),
		m_targetPosition, shared_from_this());
	float angle;
	Vector3 bulletPosition;
	if ((m_targetPosition - m_position).Normalize().x >= 0)
		bulletPosition = m_position + m_bulletSpawner;
	else
		bulletPosition = m_position - m_bulletSpawner;
	angle = std::acos((m_targetPosition - bulletPosition).Normalize().x);
	if (Upgrade::GetInstance()->GetLevel("Upgrade Attack") >= 1) {
		if ((m_targetPosition - bulletPosition).Normalize().y >= 0) {
			angle = std::acos((m_targetPosition - bulletPosition).Normalize().x) + PI / 16;
		}
		else {
			angle = - std::acos((m_targetPosition - bulletPosition).Normalize().x ) + PI / 16;
		}
		if((m_targetPosition - bulletPosition).Normalize().x>=0)
			m_targetPosition = Vector3(bulletPosition.x + std::cos(angle) * 100, bulletPosition.y + std::sin(angle) * 100, 0);
		else
			m_targetPosition = Vector3(bulletPosition.x + std::cos(angle) * 100, bulletPosition.y + std::sin(angle) * 100, 0);
		BulletPoolManager::GetInstance()->AddBullet(
			BulletType::Linear_MainCharacter, std::dynamic_pointer_cast<BaseEnemy>(std::make_shared<EnemyOne>()),
			m_targetPosition, shared_from_this());


		if (Upgrade::GetInstance()->GetLevel("Upgrade Attack") >= 2) {
			if ((m_targetPosition - bulletPosition).Normalize().y >= 0) {
				angle = std::acos((m_targetPosition - bulletPosition).Normalize().x) - PI/8;
			}
			else {
				angle = - std::acos((m_targetPosition - bulletPosition).Normalize().x) - PI / 8;
			}
			if ((m_targetPosition - bulletPosition).Normalize().x >= 0)
				m_targetPosition = Vector3(bulletPosition.x + std::cos(angle) * 100, bulletPosition.y + std::sin(angle) * 100, 0);
			else
				m_targetPosition = Vector3(bulletPosition.x + std::cos(angle) * 100, bulletPosition.y + std::sin(angle) * 100, 0);
			BulletPoolManager::GetInstance()->AddBullet(
				BulletType::Linear_MainCharacter, std::dynamic_pointer_cast<BaseEnemy>(std::make_shared<EnemyOne>()),
				m_targetPosition, shared_from_this());
		}
	}
}
void MainCharacter::AttackLinear()
{
	m_currentTimeAttack =0;
	m_isCastingAttack = true;
	if ((m_targetPosition-m_position).x<0) {
		m_pTexture = m_attackLeftAnimation;
	}
	else {
		m_pTexture = m_attackRightAnimation;
	}
	m_frameTime = m_delayAttackTime / m_numFrames;
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

bool MainCharacter::HandleTouchHUD(GLint x, GLint y, bool bIsPressed)
{
	bool m_isHandled = false;
	if (bIsPressed)
	{
		if ((x > m_position.x - m_iWidth / 2.f) && (x < m_position.x + m_iWidth / 2.f)
			&& (y > m_position.y - m_iHeight / 2.f) && (y < m_position.y + m_iHeight / 2.f))
		{
			// The button is being pressed down
			m_isHolding = true;
		}
	}
	else
	{
		if ((x > m_position.x - m_iWidth / 2.f) && (x < m_position.x + m_iWidth / 2.f)
			&& (y > m_position.y - m_iHeight / 2.f) && (y < m_position.y + m_iHeight / 2.f)
			&& m_isHolding == true)
		{
			// Only perform click action when the same button was pressed down and released
			m_isHandled = true;
		}
		m_isHolding = false;
	}
	return m_isHandled;
}

bool MainCharacter::CheckCollide(GLfloat deltaTime)
{
	for (auto &tower : DefensivePoolManager::GetInstance()->spotList) {
		if ((tower->GetPosition().x + tower->GetWidth() / 2.f > m_position.x - m_width / 2.f + deltaTime * m_speed * m_direction.x) && (tower->GetPosition().x - tower->GetWidth() / 2.f < m_position.x + m_width / 2.f + deltaTime * m_speed * m_direction.x)
			&& (tower->GetPosition().y + tower->GetIHeight() / 2.f > m_position.y - m_height / 2.f + deltaTime * m_speed * m_direction.y) && (tower->GetPosition().y + tower->GetIHeight() / 2.f - tower->GetHeight() < m_position.y + m_height / 2.f + deltaTime * m_speed * m_direction.y))
		{
			return true;
		}

	}
	for (auto &tower : DefensivePoolManager::GetInstance()->unMoveThroughAbleTowerList) {
		if ((tower->GetPosition().x + tower->GetWidth() / 2.f > m_position.x - m_width / 2.f + deltaTime * m_speed * m_direction.x) && (tower->GetPosition().x - tower->GetWidth() / 2.f < m_position.x + m_width / 2.f + deltaTime * m_speed * m_direction.x)
			&& (tower->GetPosition().y + tower->GetIHeight() / 2.f > m_position.y - m_height / 2.f + deltaTime * m_speed * m_direction.y) && (tower->GetPosition().y + tower->GetIHeight() / 2.f - tower->GetHeight() < m_position.y + m_height / 2.f + deltaTime * m_speed * m_direction.y))
		{
			return true;
		}
	}
	return false;
}
