#pragma once
#include "GameStateBase.h"
#include "MainCharacter.h"
#include "../GameObject/Defensive/MainTower.h"

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
	void	HandleKeyPress(float deltaTime);

	static int win;
private:
	std::shared_ptr<Sprite2D>		m_background;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::shared_ptr <MainTower>		m_mainTower;
	std::shared_ptr <BaseObject>	m_controller;
	float							m_time;
	int								m_count;
};

