#pragma once
#include "GameStateBase.h"
#include "Others/GameButton.h"

class GSMenu :
	public GameStateBase
{
public:
	GSMenu();
	~GSMenu();

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

	static bool vfxSound;
	static bool backgroundMusic;
	static int	difficulty;
	static int	diamond;
private:
	std::shared_ptr<Sprite2D>				m_background;
	std::shared_ptr<Sprite2D>				m_titleTable;
	//std::shared_ptr<Sprite2D>				m_background;
	//std::shared_ptr<Sprite2D>				m_background;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::list<std::shared_ptr<Text>>		m_listText;
	std::list<std::shared_ptr<Sprite2D>>	m_listRope;
};

