#include "TowerOne.h"

TowerOne::TowerOne() :UnMoveThroughAbleTower(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"),
	ResourceManagers::GetInstance()->GetShader("TextureShader"),
	ResourceManagers::GetInstance()->GetTexture("AncientTree1.tga"),
	0, 0, 150, 150, 500, 1, 1000, 0)
{

}

TowerOne::TowerOne(float x, float y):UnMoveThroughAbleTower(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"),
	ResourceManagers::GetInstance()->GetShader("TextureShader"),
	ResourceManagers::GetInstance()->GetTexture("AncientTree2.tga"),
	x, y, 150, 150, 500, 1, 1000,0)
{

}

void TowerOne::Attack()
{
}

void TowerOne::Reset()
{
	m_level=0;
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

void TowerOne::Update(GLfloat deltatime)
{
}
