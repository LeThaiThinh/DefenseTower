#pragma once
#include "GameStateBase.h"
#include <Others/GameButton.h>

class GSTutorial : public GameStateBase
{
public:
	GSTutorial();
	~GSTutorial();

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

private:
	std::shared_ptr<Sprite2D>	m_background;
	std::shared_ptr<Sprite2D>				m_table;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::list<std::list<std::shared_ptr<Text>>>		m_listTexts;

};

