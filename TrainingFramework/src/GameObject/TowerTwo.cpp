#include "TowerTwo.h"
TowerTwo::TowerTwo() :UnMoveThroughAbleTower(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"),
	ResourceManagers::GetInstance()->GetShader("TextureShader"),
	ResourceManagers::GetInstance()->GetTexture("AncientTree1.tga"),
	0, 0, 150, 200, 500, 1, 1000, 0) {}

TowerTwo::TowerTwo(float x, float y) :UnMoveThroughAbleTower(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"),
	ResourceManagers::GetInstance()->GetShader("TextureShader"),
	ResourceManagers::GetInstance()->GetTexture("AncientTree1.tga"),
	x,y, 100, 100, 500, 1, 1000,0){}

void TowerTwo::Attack()
{
}

void TowerTwo::Reset()
{
	m_level = 0;
	m_disposable = false;
	SetModels(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"));
	SetTexture(ResourceManagers::GetInstance()->GetTexture("AncientTree1.tga"));
	SetShaders(ResourceManagers::GetInstance()->GetShader("TextureShader"));
	SetSize(150, 200);
	SetRange(200);
	SetAttackSpeed(1);
	m_currentTimeAttack = GetAttackSpeed();
	SetHitPoint(500.f);
}

void TowerTwo::Update(GLfloat deltatime)
{
}
