#include "Bullet.h"

Bullet::Bullet():SelfDestructable(),MoveAble(),Animation2D()
{
	Init(BulletType::MainCharacter);
}

Bullet::Bullet(BulletType bulletType)
{
	m_bulletType = bulletType;
	Init(bulletType);
}

Bullet::Bullet(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int numFrame, int numFramesInLine, float frameTime, float x, float y, float width, float height, Vector2 targetPosition, BulletType bulletType)
	:Animation2D(model, shader, texture, numFrame, numFramesInLine, frameTime, x, y,width,height), m_targetPosition(targetPosition), m_bulletType(bulletType)
	, SelfDestructable(), MoveAble()
{
}

Bullet::Bullet(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int numFrame, int numFramesInLine, float frameTime, float x, float y, float width, float height, std::weak_ptr<BaseObject> target, BulletType bulletType)
	: Animation2D(model, shader, texture, numFrame, numFramesInLine, frameTime, x, y, width, height), m_target(target),m_bulletType(bulletType)
{
}

Bullet::~Bullet()
{
}

void Bullet::Move(GLfloat deltatime)
{
	Set2DPosition(m_position.x + deltatime * m_speed * m_direction.x, m_position.y + deltatime * m_speed * m_direction.y);
}

void Bullet::SetType(BulletType bulletType)
{
	m_bulletType = bulletType; 
	Init(bulletType);
}

void Bullet::Init(BulletType bulletType)
{
	m_currentTimeExist = 0.f;
	m_currentFrame = 0;
	m_currentFrameTime = 0;
	switch (bulletType)
	{
	case BulletType::MainCharacter:
		SetModels(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"));
		SetTexture(ResourceManagers::GetInstance()->GetTexture("WormMonster.tga"));
		SetShaders(ResourceManagers::GetInstance()->GetShader("AnimationShader"));
		m_numFrames = 15;
		m_numFramesInLine = 15;
		m_frameTime = 0.1f;

		m_speed = 700.f;
		m_timeExist = 4.f;
		SetSize(20, 20);
		Set2DPosition(200.f, 200.f);
		break;
	default:
		break;
	}
	
}


void Bullet::Update(float deltaTime)
{
	Animation2D::Update(deltaTime);
	SelfDestructable::Update(deltaTime);
	//std::cout<<"(" << m_position.x << "-" << m_position.y <<")"<< "(" << m_targetPosition.x << "-" << m_targetPosition.y << ")" << std::endl;
}


