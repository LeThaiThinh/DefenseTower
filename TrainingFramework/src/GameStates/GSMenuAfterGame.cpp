#include "GSMenuAfterGame.h"
#include "GSPlay.h"
#include "BackgroundMusic.h"
#include <GameStates/GSMenu.h>
#include "GSSelectStage.h"
#include "Resource/ResourceTable.h"
GSMenuAfterGame::GSMenuAfterGame() : GameStateBase(StateType::STATE_MENU_AFTER_GAME)
{
}


GSMenuAfterGame::~GSMenuAfterGame()
{
}


void GSMenuAfterGame::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("UI/bg_2.tga");

	// background
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(Globals::screenWidth / 2.f, Globals::screenHeight / 2.f);
	m_background->SetISize(Globals::mapWidth, Globals::mapHeight);

	// title table
	texture = ResourceManagers::GetInstance()->GetTexture("UI/table.tga");
	m_table = std::make_shared<Sprite2D>(model, shader, texture);
	m_table->Set2DPosition(Globals::screenWidth / 2.f, Globals::screenHeight / 2.f);
	m_table->SetISize(Globals::screenWidth * 2 / 3.f, Globals::screenHeight * 2 / 3.f);

	texture = ResourceManagers::GetInstance()->GetTexture("UI/window_1.tga");
	m_table_2 = std::make_shared<Sprite2D>(model, shader, texture);
	m_table_2->Set2DPosition(Globals::screenWidth / 2.f, Globals::screenHeight / 2.f);
	m_table_2->SetISize(Globals::screenWidth * 1 / 2.f, Globals::screenHeight * 1 / 3.f);

	// header table
	if(GSPlay::win==1)
		texture = ResourceManagers::GetInstance()->GetTexture("UI/header_win.tga");
	else
		texture = ResourceManagers::GetInstance()->GetTexture("UI/header_failed.tga");
	m_header = std::make_shared<Sprite2D>(model, shader, texture);
	m_header->Set2DPosition(Globals::screenWidth / 2.f, Globals::screenHeight / 5.f);
	m_header->SetISize(Globals::screenWidth / 4.f, 100.f);
	//diamond
	texture = ResourceManagers::GetInstance()->GetTexture("UI/crystal.tga");
	m_diamond = std::make_shared<Sprite2D>(model, shader, texture);
	m_diamond->Set2DPosition(Globals::screenWidth / 2.f+20, Globals::screenHeight / 2.f);
	m_diamond->SetISize(50.f, 50.f);

	// button right
	texture = ResourceManagers::GetInstance()->GetTexture("UI/button_right.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth * 3.75 / 6.f, Globals::screenHeight *5 / 6.f - 25.f);
	button->SetISize(125, 125);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_SELECT_STAGE);
		GSPlay::win = -1;
		if (GSMenu::backgroundMusic)
			BackgroundMusic::GetInstance()->PlayBGMMenu();
		});
	m_listButton.push_back(button);

	// button restart
	texture = ResourceManagers::GetInstance()->GetTexture("UI/button_restart.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth * 2.25f / 6.f, Globals::screenHeight * 5.f / 6.f - 25.f);
	button->SetISize(125, 125);
	button->SetOnClick([]() {
		GSPlay::win = -1;
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_LOAD_GAME);
		});
	m_listButton.push_back(button);

	int reward = 0;
	switch (GSSelectStage::choosenLevel)
	{
	case 1:
		if(GSPlay::win==0)
			reward = 1;
		else {
			reward = 5;
		}
		break;
	case 2:
		if (GSPlay::win == 0)
			reward = 1;
		else {
			reward = 7;
		}
		break;
	case 3:
		if (GSPlay::win == 0)
			reward = 2;
		else {
			reward = 9;
		}
		break;
	case 4:
		if (GSPlay::win == 0)
			reward = 2;
		else {
			reward = 11;
		}
		break;
	case 5:
		if (GSPlay::win == 0)
			reward = 3;
		else {
			reward = 13;
		}
		break;
	case 6:
		if (GSPlay::win == 0)
			reward = 3;
		else {
			reward = 15;
		}
		break;
	default:
		break;
	}
	Diamond::GetInstance()->Bounty(reward);
	// text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Triangle.ttf");
	std::shared_ptr<Text> text;
	if (GSPlay::win == 0) {
		text = std::make_shared< Text>(shader, font, "Try again", Vector4(1.f, 0.6f, 0.f, 1.0f), 2.0f);
		text->Set2DPosition(Vector2(520.f, Globals::screenHeight * 4 / 10.f + 15.f));
		m_listText.push_back(text);
	}
	else {
		std::shared_ptr<Text> text = std::make_shared< Text>(shader, font, "Congratulation", Vector4(1.f, 0.6f, 0.f, 1.0f), 2.0f);
		text->Set2DPosition(Vector2(475.f, Globals::screenHeight * 4 / 10.f + 15.f));
		m_listText.push_back(text);
	}

	text = std::make_shared< Text>(shader, font, std::to_string(reward), Vector4(1.f, 0.6f, 0.f, 1.0f), 2.0f);
	text->Set2DPosition(Vector2(Globals::screenWidth/2-20, Globals::screenHeight * 5 / 10.f +15.f));
	m_listText.push_back(text);

	text = std::make_shared< Text>(shader, font, "Your reward", Vector4(1.f, 0.6f, 0.f, 1.0f), 2.0f);
	text->Set2DPosition(Vector2(500.f, Globals::screenHeight * 6 / 10.f + 15.f));
	m_listText.push_back(text);

}

void GSMenuAfterGame::Exit()
{
}


void GSMenuAfterGame::Pause()
{
}

void GSMenuAfterGame::Resume()
{
}


void GSMenuAfterGame::HandleEvents()
{
}

void GSMenuAfterGame::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSMenuAfterGame::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto& button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSMenuAfterGame::HandleMouseMoveEvents(int x, int y)
{
}

void GSMenuAfterGame::Update(float deltaTime)
{
	for (auto& button : m_listButton)
	{
		button->Update(deltaTime);
	}
}

void GSMenuAfterGame::Draw()
{
	m_background->Draw();
	m_table->Draw();
	m_table_2->Draw();
	m_header->Draw();
	m_diamond->Draw();
	for (auto& button : m_listButton)
	{
		button->Draw();
	}
	for (auto& text : m_listText) {
		text->Draw();
	}
}
