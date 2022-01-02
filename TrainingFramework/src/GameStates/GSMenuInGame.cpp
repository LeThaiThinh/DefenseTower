#include "GSMenuInGame.h"
#include "GSPlay.h"
#include <Application.h>
#include "CheckCollision.h"
#include "Coin.h"
#include "EnemyManager.h"
#include "BackgroundMusic.h"
GSMenuInGame::GSMenuInGame() : GameStateBase(StateType::STATE_MENU_IN_GAME)
{
}


GSMenuInGame::~GSMenuInGame()
{
}


void GSMenuInGame::Init()
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
	if (GSPlay::win == 1)
		texture = ResourceManagers::GetInstance()->GetTexture("UI/header_win.tga");
	else
		texture = ResourceManagers::GetInstance()->GetTexture("UI/header_failed.tga");
	m_header = std::make_shared<Sprite2D>(model, shader, texture);
	m_header->Set2DPosition(Globals::screenWidth / 2.f, Globals::screenHeight / 5.f);
	m_header->SetISize(Globals::screenWidth / 4.f, 100.f);

	// button left
	texture = ResourceManagers::GetInstance()->GetTexture("UI/button_left.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth * 1.75 / 6.f, Globals::screenHeight * 5 / 6.f - 25.f);
	button->SetISize(125, 125);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	// button restart
	texture = ResourceManagers::GetInstance()->GetTexture("UI/button_restart.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth * 3 / 6.f, Globals::screenHeight * 5 / 6.f - 25.f);
	button->SetISize(125, 125);
	button->SetOnClick([]() {
		DefensivePoolManager::GetInstance()->Clear();
		DefensivePoolManager::GetInstance()->Remove();
		EnemyPoolManager::GetInstance()->Clear();
		EnemyPoolManager::GetInstance()->Remove();
		BulletPoolManager::GetInstance()->Clear();
		BulletPoolManager::GetInstance()->Remove();
		Coin::GetInstance()->Reset();
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		BackgroundMusic::GetInstance()->StopBGMIngame();
		});
	m_listButton.push_back(button);


	//button right
	texture = ResourceManagers::GetInstance()->GetTexture("UI/button_right.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth * 4.25 / 6.f, Globals::screenHeight * 5 / 6.f - 25.f);
	button->SetISize(125, 125);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->PopState();
		DefensivePoolManager::GetInstance()->Clear();
		DefensivePoolManager::GetInstance()->Remove();
		EnemyPoolManager::GetInstance()->Clear();
		EnemyPoolManager::GetInstance()->Remove();
		BulletPoolManager::GetInstance()->Clear();
		BulletPoolManager::GetInstance()->Remove();
		Coin::GetInstance()->Reset();
		if (GSMenu::backgroundMusic)
			BackgroundMusic::GetInstance()->PlayBGMMenu();
		});
	m_listButton.push_back(button);

	//button music
	if (GSMenu::backgroundMusic == 0)
		texture = ResourceManagers::GetInstance()->GetTexture("UI/button_music_off.tga");
	else if (GSMenu::backgroundMusic == 1)
		texture = ResourceManagers::GetInstance()->GetTexture("UI/button_music.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2.f + 200, Globals::screenHeight * 4.5 / 10.f);
	button->SetISize(100, 100);
	button->SetOnClickTexture([](std::shared_ptr<GameButton> button) {
		GSMenu::backgroundMusic = !GSMenu::backgroundMusic;
		if (GSMenu::backgroundMusic == 0) {
			button->SetTexture(ResourceManagers::GetInstance()->GetTexture("UI/button_music_off.tga"));
			BackgroundMusic::GetInstance()->StopBGMIngame();
		}
		else if (GSMenu::backgroundMusic == 1) {
			button->SetTexture(ResourceManagers::GetInstance()->GetTexture("UI/button_music.tga"));
			BackgroundMusic::GetInstance()->PlayBGMIngame();
		}
		});
	m_listButton.push_back(button);

	//button vfx sound
	if (GSMenu::vfxSound == 0)
		texture = ResourceManagers::GetInstance()->GetTexture("UI/button_sound_off.tga");
	else if (GSMenu::vfxSound == 1)
		texture = ResourceManagers::GetInstance()->GetTexture("UI/button_sound.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2.f + 200.f, Globals::screenHeight * 5.5 / 10.f);
	button->SetISize(100, 100);
	button->SetOnClickTexture([](std::shared_ptr<GameButton> button) {
		GSMenu::vfxSound = !GSMenu::vfxSound;
		if (GSMenu::vfxSound == 0)
			button->SetTexture(ResourceManagers::GetInstance()->GetTexture("UI/button_sound_off.tga"));
		else if (GSMenu::vfxSound == 1)
			button->SetTexture(ResourceManagers::GetInstance()->GetTexture("UI/button_sound.tga"));
		});
	m_listButton.push_back(button);

	// text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Rot.ttf");
	std::shared_ptr<Text> text = std::make_shared< Text>(shader, font, "Background music", Vector4(1.f, 0.6f, 0.f, 1.0f), 1.5f);
	text->Set2DPosition(Vector2(350.f, Globals::screenHeight * 4.5 / 10.f + 15.f));
	m_listText.push_back(text);

	text = std::make_shared< Text>(shader, font, "VFX Sound", Vector4(1.f, 0.6f, 0.f, 1.0f), 1.5f);
	text->Set2DPosition(Vector2(350.f, Globals::screenHeight * 5.5 / 10.f + 15.f));
	m_listText.push_back(text);
}

void GSMenuInGame::Exit()
{
}


void GSMenuInGame::Pause()
{
}

void GSMenuInGame::Resume()
{
}


void GSMenuInGame::HandleEvents()
{
}

void GSMenuInGame::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSMenuInGame::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto& button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSMenuInGame::HandleMouseMoveEvents(int x, int y)
{
}

void GSMenuInGame::Update(float deltaTime)
{
	for (auto& button : m_listButton)
	{
		button->Update(deltaTime);
	}
}

void GSMenuInGame::Draw()
{
	m_background->Draw();
	m_table->Draw();
	m_table_2->Draw();
	m_header->Draw();
	for (auto& button : m_listButton)
	{
		button->Draw();
	}
	for (auto& text : m_listText) {
		text->Draw();
	}
}
