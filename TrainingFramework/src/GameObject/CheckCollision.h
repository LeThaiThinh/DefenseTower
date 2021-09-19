#pragma once
#include "MainCharacter.h"
#include "TowerManager.h"
class CheckCollision
{
public:
	CheckCollision();
	~CheckCollision();

	static bool MainCharacterCollideTower(std::shared_ptr<MainCharacter> character,std::list<std::shared_ptr<UnMoveThroughAbleTower>>);
private:

};
