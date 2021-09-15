#include "MainCharacter.h"
#include "Bullet.h"
ObjectPool<Bullet>* ObjectPool<Bullet>::instance = 0;

MainCharacter::MainCharacter() :Animation2D(16, 0.033f, 4, 300, 300)
{
	Init();
}

MainCharacter::~MainCharacter()
{
}

void MainCharacter::Init()
{
	SetModels(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"));
	SetTexture(ResourceManagers::GetInstance()->GetTexture("Bomb2.tga"));
	SetShaders(ResourceManagers::GetInstance()->GetShader("AnimationShader"));

	m_speed = 50;
	m_hitpoint = 500;
	m_poolTarget = ObjectPool<Bullet>::getInstance();
	std::shared_ptr<Bullet> bullet = m_poolTarget->getResource();
	m_bulletList.push_back(bullet);
	SetSize(100, 100);
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
}

