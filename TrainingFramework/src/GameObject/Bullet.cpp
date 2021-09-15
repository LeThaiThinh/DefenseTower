#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::Bullet(BulletType bulletType)
{
	m_bulletType = bulletType;
	Init(bulletType);
}

Bullet::Bullet(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int numFrame, int numFramesInLine, float frameTime, float x, float y, Vector2 targetPosition)
	:Animation2D(model, shader, texture, numFrame, numFramesInLine, frameTime, x, y), m_targetPosition(targetPosition)
	, SelfDestructable(), MoveAble()
{
}

Bullet::~Bullet()
{
}

void Bullet::Move(GLfloat deltatime)
{
}

void Bullet::SetType(BulletType bulletType)
{
	m_bulletType = bulletType; 
	Init(bulletType);
}

void Bullet::Init(BulletType bulletType)
{
	printf("shoot");
	switch (bulletType)
	{
	case BulletType::MainCharacter:
		SetModels(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"));
		SetTexture(ResourceManagers::GetInstance()->GetTexture("Bomb2.tga"));
		SetShaders(ResourceManagers::GetInstance()->GetShader("AnimationShader"));

		m_speed = 50;
		m_timeExist = 4;
		SetSize(25, 25);
		break;
	default:
		break;
	}
	
}


