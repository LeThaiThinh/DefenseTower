#include "MainTower.h"


MainTower::MainTower()
	:UnMoveThroughAbleTower(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"),
		ResourceManagers::GetInstance()->GetShader("TextureShader"),
		ResourceManagers::GetInstance()->GetTexture("AncientTree2.tga"), 
		Globals::screenWidth/2, Globals::screenHeight/2, 250, 320, 500, 1, 1000,0)
{
}

void MainTower::Attack()
{
}

void MainTower::Reset()
{
}

void MainTower::Update(GLfloat deltatime)
{
	UnMoveThroughAbleTower::Update(deltatime);
}
