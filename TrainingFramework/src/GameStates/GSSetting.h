#pragma once
#include "GameStateBase.h"
#include <Others/GameButton.h>

class GSSetting : public GameStateBase
{
public:
	GSSetting();
	~GSSetting();

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
	std::shared_ptr<Sprite2D>				m_table;
	std::shared_ptr<Sprite2D>				m_table_2;
	std::shared_ptr<Sprite2D>				m_header;
	std::shared_ptr<Sprite2D>				m_background;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::list<std::shared_ptr<Text>>		m_listText;
};

