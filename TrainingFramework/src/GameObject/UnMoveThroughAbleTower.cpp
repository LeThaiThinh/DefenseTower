#include "UnMoveThroughAbleTower.h"
#include "../Application.h"
void UnMoveThroughAbleTower::Attack()
{
}

void UnMoveThroughAbleTower::Update(GLfloat deltatime)
{
	Sprite2D::Update(deltatime);
	AbleToAttack::Update(deltatime);
	SetDisposable(IsDestroyed());
}
