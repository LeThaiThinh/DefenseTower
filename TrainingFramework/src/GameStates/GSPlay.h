#pragma once
#include "GameStateBase.h"
#include "MainCharacter.h"
#include "BulletManager.h"
#include "MainTower.h"
#include "TowerManager.h"

class Sprite2D;
class Sprite3D;
class Text;
class GameButton;
class Bullet;
class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void	Init() override;
	void	Exit() override;

	void	Pause() override;
	void	Resume() override;

	void	HandleEvents() override;
	void	HandleKeyEvents(int key, bool bIsPressed) override;
	void	HandleTouchEvents(int x, int y, bool bIsPressed) override;
	void	HandleMouseMoveEvents(int x, int y) override;
	void	Update(float deltaTime) override;
	void	Draw() override;

	void HandleKeyPress(float deltaTime);

private:
	std::shared_ptr<Sprite2D>	m_background;
	std::shared_ptr<Text>		m_score;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::shared_ptr <MainCharacter> m_mainCharacter;
	std::shared_ptr <MainTower> m_mainTower;
	std::shared_ptr <BaseObject> m_controller;

};

