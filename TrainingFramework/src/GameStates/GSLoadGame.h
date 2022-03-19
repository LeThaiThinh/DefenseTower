#pragma once
#include "GameStateBase.h"
#include <Others/GameButton.h>
#define LOAD_BACKGROUND_WIDTH 500
#define LOAD_BACKGROUND_HEIGHT 50

class GSLoadGame : public GameStateBase
{
public:
	GSLoadGame();
	~GSLoadGame();

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

	void	SetLoadPercentage(float loadPercentage) {
		m_loadPercentage = loadPercentage;
		m_loadBar->SetISize(LOAD_BACKGROUND_WIDTH* loadPercentage, LOAD_BACKGROUND_HEIGHT-6);
		m_loadBar->Set2DPosition(Globals::screenWidth / 2.f-(1-loadPercentage)/2* LOAD_BACKGROUND_WIDTH, Globals::screenHeight/2.f-5);
	}

private:
	float m_time;
	bool m_wait;
	float m_loadPercentage;
	std::shared_ptr<Sprite2D>	m_loadBar;
	std::shared_ptr<Sprite2D>	m_background;
	std::shared_ptr<Sprite2D>	m_loadBackGround;
};

