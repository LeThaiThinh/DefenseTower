#pragma once
#include "GameStateBase.h"
#include <Others/GameButton.h>
#include "Base/Text.h"
#include "Base/Sprite2D.h"
#define MAXPAGE 3
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
	static	int		page;
private:
	std::shared_ptr<Sprite2D>	m_background;
	std::shared_ptr<Sprite2D>				m_table;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::vector<std::shared_ptr<Sprite2D>>		m_listImage;
	std::vector<std::list<std::shared_ptr<Text>>>		m_listTexts;
	
};

