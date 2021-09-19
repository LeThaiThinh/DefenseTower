#include "SpotTower.h"

SpotTower::SpotTower() :BaseTower(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"),
	ResourceManagers::GetInstance()->GetShader("TextureShader"),
	ResourceManagers::GetInstance()->GetTexture("AncientTree1.tga"),
	0.f, 0.f, 100, 100, 500.f, 1.f, 0)
{
}

void SpotTower::Update(GLfloat deltatime)
{
}
