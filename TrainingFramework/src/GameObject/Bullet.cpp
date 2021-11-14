#include "Bullet.h"
#include "../../BaseEnemy.h"
#include "BulletManager.h"
#include "EnemyManager.h"
#include "DefensiveManager.h"
Bullet::Bullet() :SelfDestructable(), MoveAble(), Animation2D(), m_damage(0)
{
}

Bullet::Bullet(BulletType bulletType, std::shared_ptr<BaseObject> target, Vector3 targetPosition, std::shared_ptr<BaseObject> source)
{
	Init(bulletType, target, targetPosition, source);
}


Bullet::Bullet(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int numFrame, int numFramesInLine, float frameTime, float x, float y, int iwidth, int iheight, int width, int height, Vector3 targetPosition, BulletType bulletType, std::weak_ptr<BaseObject> source)
	:Animation2D(model, shader, texture, numFrame, numFramesInLine, frameTime, x, y, iwidth, iheight, width, height), m_targetPosition(targetPosition), m_source(source)
	, SelfDestructable(), MoveAble()
{
}

Bullet::Bullet(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int numFrame, int numFramesInLine, float frameTime, float x, float y, int iwidth, int iheight, int width, int height, std::weak_ptr<BaseObject> target, BulletType bulletType, std::weak_ptr<BaseObject> source)
	: Animation2D(model, shader, texture, numFrame, numFramesInLine, frameTime, x, y, iwidth, iheight, width, height), m_target(target), m_bulletType(bulletType), m_source(source)
{
}

Bullet::~Bullet()
{
}

void Bullet::Move(GLfloat deltatime)
{
	switch (m_bulletType)
	{
	case BulletType::Linear_MainCharacter:
	{
		std::shared_ptr<BaseEnemy> groundEnemy = CheckCollideGroundEnemy(deltatime);
		std::shared_ptr<BaseEnemy> flyEnemy = CheckCollideFlyEnemy(deltatime);
		if (!groundEnemy && !flyEnemy) {
			Set2DPosition(m_position.x + deltatime * m_speed * m_direction.x, m_position.y + deltatime * m_speed * m_direction.y);
		}
		else if (groundEnemy) {
			groundEnemy->TakeDamage(m_damage);
			if (groundEnemy->GetHitPoint() <= 0) {
				EnemyPoolManager::GetInstance()->RemoveGroundInstant(groundEnemy);
			}
			BulletPoolManager::GetInstance()->RemoveBullet(std::dynamic_pointer_cast<Bullet>(shared_from_this()));
		}
		else if (flyEnemy) {
			flyEnemy->TakeDamage(m_damage);
			if (flyEnemy->GetHitPoint() <= 0) {
				EnemyPoolManager::GetInstance()->RemoveFlyInstant(flyEnemy);
			}
			BulletPoolManager::GetInstance()->RemoveBullet(std::dynamic_pointer_cast<Bullet>(shared_from_this()));
		}
	}
	break;
	case BulletType::Target_TowerOne:
	{
		std::shared_ptr<BaseEnemy> groundEnemy = CheckCollideGroundEnemy(deltatime);
		std::shared_ptr<BaseEnemy> flyEnemy = CheckCollideFlyEnemy(deltatime);
		if (!groundEnemy && !flyEnemy) {
			if (m_target.lock())
				SetDirection((m_target.lock()->GetPosition() - m_source.lock()->GetPosition()).Normalize());
			Set2DPosition(m_position.x + deltatime * m_speed * m_direction.x, m_position.y + deltatime * m_speed * m_direction.y);
		}
		else if (groundEnemy) {
			groundEnemy->TakeDamage(m_damage);
			if (groundEnemy->GetHitPoint() <= 0) {
				EnemyPoolManager::GetInstance()->RemoveGroundInstant(groundEnemy);
			}
			BulletPoolManager::GetInstance()->RemoveBullet(std::dynamic_pointer_cast<Bullet>(shared_from_this()));
		}
		else if (flyEnemy) {
			flyEnemy->TakeDamage(m_damage);
			if (flyEnemy->GetHitPoint() <= 0) {
				EnemyPoolManager::GetInstance()->RemoveFlyInstant(flyEnemy);
			}
			BulletPoolManager::GetInstance()->RemoveBullet(std::dynamic_pointer_cast<Bullet>(shared_from_this()));
		}
	}
	break;
	case BulletType::TowerTwo:
		break;
	case BulletType::TowerThree:
		break;
	case BulletType::Chain:
		break;
	case BulletType::Target_Enemy:
	{
		std::shared_ptr<UnMoveThroughAbleTower> tower = CheckCollideTower(deltatime);
		if (!tower) {
			if (m_target.lock())
				SetDirection((m_target.lock()->GetPosition() - m_source.lock()->GetPosition()).Normalize());
			Set2DPosition(m_position.x + deltatime * m_speed * m_direction.x, m_position.y + deltatime * m_speed * m_direction.y);
		}
		else if (tower) {
			tower->TakeDamage(m_damage);
			if (tower->GetHitPoint() <= 0) {
				DefensivePoolManager::GetInstance()->Add(m_target.lock()->GetPosition().x, m_target.lock()->GetPosition().y, TowerType::Spot);
				DefensivePoolManager::GetInstance()->RemoveUnmoveInstant(tower);
			}
			BulletPoolManager::GetInstance()->RemoveBullet(std::dynamic_pointer_cast<Bullet>(shared_from_this()));
		}
	}
	break;
	default:
		break;
	}
}



void Bullet::Init(BulletType bulletType, std::shared_ptr<BaseObject> target, Vector3 targetPosition, std::shared_ptr<BaseObject> source)
{
	m_currentTimeExist = 0.f;
	m_currentFrame = 0;
	m_currentFrameTime = 0.f;
	m_bulletType = bulletType;
	m_damage = std::dynamic_pointer_cast<AbleToAttack>(source)->GetDamage();
	switch (bulletType)
	{
	case BulletType::Linear_MainCharacter:
	{
		SetModels(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"));
		SetTexture(ResourceManagers::GetInstance()->GetTexture("ElectricBullet.tga"));
		SetShaders(ResourceManagers::GetInstance()->GetShader("AnimationShader"));
		m_numFrames = 6;
		m_numFramesInLine = 6;
		m_frameTime = 0.1f;

		m_source = source;
		m_targetPosition = targetPosition;
		SetDirection((targetPosition - m_source.lock()->GetPosition()).Normalize());
		m_speed = 300.f;
		m_timeExist = 3.f;
		SetISize(20, 20);
		SetSize(20, 20);
		SetPosition(source->GetPosition());
	}
	break;
	case BulletType::Target_TowerOne:
	{
		SetModels(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"));
		SetTexture(ResourceManagers::GetInstance()->GetTexture("ElectricBullet.tga"));
		SetShaders(ResourceManagers::GetInstance()->GetShader("AnimationShader"));
		m_numFrames = 6;
		m_numFramesInLine = 6;
		m_frameTime = 0.1f;

		m_source = source;
		m_target = target;
		m_speed = 300.f;
		m_timeExist = 2.f;
		SetISize(20, 20);
		SetSize(20, 20);
		SetPosition(source->GetPosition());
	}
	break;
	case BulletType::Target_Enemy:
	{
		SetModels(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"));
		SetTexture(ResourceManagers::GetInstance()->GetTexture("ElectricBullet.tga"));
		SetShaders(ResourceManagers::GetInstance()->GetShader("AnimationShader"));
		m_numFrames = 6;
		m_numFramesInLine = 6;
		m_frameTime = 0.1f;

		m_source = source;
		m_target = target;
		m_speed = 300.f;
		m_timeExist = 2.f;
		SetISize(20, 20);
		SetSize(20, 20);
		SetPosition(source->GetPosition());
	}
	break;
	default:
		break;
	}

}


void Bullet::Update(float deltaTime)
{
	Animation2D::Update(deltaTime);
	SelfDestructable::Update(deltaTime);
}

std::shared_ptr<BaseEnemy> Bullet::CheckCollideGroundEnemy(GLfloat deltaTime)
{
	for (auto groundEnemy : EnemyPoolManager::GetInstance()->groundEnemyList) {
		if ((groundEnemy->GetCenterPosition().x + groundEnemy->GetWidth() / 3 > m_position.x - m_width / 3 + deltaTime * m_speed * m_direction.x) && (groundEnemy->GetCenterPosition().x - groundEnemy->GetWidth() / 3 < m_position.x + m_width / 3 + deltaTime * m_speed * m_direction.x)
			&& (groundEnemy->GetCenterPosition().y + groundEnemy->GetIHeight() / 3 > m_position.y - m_height / 3 + deltaTime * m_speed * m_direction.y) && (groundEnemy->GetCenterPosition().y - groundEnemy->GetHeight() / 3 < m_position.y + m_height / 3 + deltaTime * m_speed * m_direction.y))
		{
			return groundEnemy;
		}
	}
	return nullptr;
}
std::shared_ptr<BaseEnemy> Bullet::CheckCollideFlyEnemy(GLfloat deltaTime)
{
	for (auto flyEnemy : EnemyPoolManager::GetInstance()->flyEnemyList) {
		if ((flyEnemy->GetCenterPosition().x + flyEnemy->GetWidth() / 3 > m_position.x - m_width / 3 + deltaTime * m_speed * m_direction.x) && (flyEnemy->GetCenterPosition().x - flyEnemy->GetWidth() / 3 < m_position.x + m_width / 3 + deltaTime * m_speed * m_direction.x)
			&& (flyEnemy->GetCenterPosition().y + flyEnemy->GetIHeight() / 3 > m_position.y - m_height / 3 + deltaTime * m_speed * m_direction.y) && (flyEnemy->GetCenterPosition().y - flyEnemy->GetHeight() / 3 < m_position.y + m_height / 3 + deltaTime * m_speed * m_direction.y))
		{
			return flyEnemy;
		}
	}
	return nullptr;
}

std::shared_ptr<UnMoveThroughAbleTower> Bullet::CheckCollideTower(GLfloat deltaTime)
{
	for (auto tower : DefensivePoolManager::GetInstance()->unMoveThroughAbleTowerList) {
		if ((tower->GetCenterPosition().x + tower->GetWidth() / 3 > m_position.x - m_width / 3 + deltaTime * m_speed * m_direction.x) && (tower->GetCenterPosition().x - tower->GetWidth() / 3 < m_position.x + m_width / 3 + deltaTime * m_speed * m_direction.x)
			&& (tower->GetCenterPosition().y + tower->GetIHeight() / 3 > m_position.y - m_height / 3 + deltaTime * m_speed * m_direction.y) && (tower->GetCenterPosition().y - tower->GetHeight() / 3 < m_position.y + m_height / 3 + deltaTime * m_speed * m_direction.y))
		{
			return std::dynamic_pointer_cast<UnMoveThroughAbleTower>(tower);
		}
	}
	return nullptr;
}