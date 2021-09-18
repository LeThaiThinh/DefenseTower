#include "MainTower.h"


MainTower::MainTower()
	:UnMoveThroughAbleTower(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"),
		ResourceManagers::GetInstance()->GetShader("TextureShader"),
		ResourceManagers::GetInstance()->GetTexture("AncientTree1.tga"), 
		Globals::screenWidth/2, Globals::screenHeight/2, 250, 300, 500, 1, 1000)
{
	printf("qweqwe");
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
