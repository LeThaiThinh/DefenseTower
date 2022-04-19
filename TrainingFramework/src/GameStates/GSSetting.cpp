#include "GSSetting.h"
#include "GSMenu.h"
#include <GameStates/Record.h>
#include "BackgroundMusic.h"
GSSetting::GSSetting() : GameStateBase(StateType::STATE_SETTING)
{
}


GSSetting::~GSSetting()
{
}


void GSSetting::Init()
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
	m_table_2->SetISize(Globals::screenWidth * 1 / 2.f +50 , Globals::screenHeight * 1 / 2.f);

	// header table
	texture = ResourceManagers::GetInstance()->GetTexture("UI/header_settings.tga");
	m_header = std::make_shared<Sprite2D>(model, shader, texture);
	m_header->Set2DPosition(Globals::screenWidth / 2.f, Globals::screenHeight / 5.f);
	m_header->SetISize(Globals::screenWidth / 4.f, 100.f);

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("UI/button_close_2.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth * 5 / 6.f - 25.f, Globals::screenHeight / 6.f + 25.f);
	button->SetISize(75, 75);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	//button difficulty
	if (GSMenu::difficulty == 0)
		texture=ResourceManagers::GetInstance()->GetTexture("UI/button_easy.tga");
	else if (GSMenu::difficulty == 1)
		texture = ResourceManagers::GetInstance()->GetTexture("UI/button_normal.tga");
	else if (GSMenu::difficulty == 2)
		texture = ResourceManagers::GetInstance()->GetTexture("UI/button_hard.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2.f + 220, Globals::screenHeight * 3.5 / 10.f);
	button->SetISize(150, 100);
	button->SetOnClickTexture([](std::shared_ptr<GameButton> button) {
		GSMenu::difficulty = (GSMenu::difficulty + 1) % 3;
		if(GSMenu::difficulty==0)
			button->SetTexture(ResourceManagers::GetInstance()->GetTexture("UI/button_easy.tga"));
		else if(GSMenu::difficulty == 1)
			button->SetTexture(ResourceManagers::GetInstance()->GetTexture("UI/button_normal.tga"));
		else if (GSMenu::difficulty == 2)
			button->SetTexture(ResourceManagers::GetInstance()->GetTexture("UI/button_hard.tga"));
		});
	m_listButton.push_back(button);

	//button music
	if (GSMenu::backgroundMusic == 0)
		texture = ResourceManagers::GetInstance()->GetTexture("UI/button_music_off.tga");
	else if (GSMenu::backgroundMusic == 1)
		texture = ResourceManagers::GetInstance()->GetTexture("UI/button_music.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2.f + 220, Globals::screenHeight * 5 / 10.f);
	button->SetISize(100, 100);
	button->SetOnClickTexture([](std::shared_ptr<GameButton> button) {
		GSMenu::backgroundMusic = !GSMenu::backgroundMusic;
		if (GSMenu::backgroundMusic == 0) {
			button->SetTexture(ResourceManagers::GetInstance()->GetTexture("UI/button_music_off.tga"));
			BackgroundMusic::GetInstance()->StopBGMMenu();
		}
		else if (GSMenu::backgroundMusic == 1) {
			button->SetTexture(ResourceManagers::GetInstance()->GetTexture("UI/button_music.tga"));
			BackgroundMusic::GetInstance()->PlayBGMMenu();

		}
		});
	m_listButton.push_back(button);

	//button vfx sound
	if (GSMenu::sfx == 0)
		texture = ResourceManagers::GetInstance()->GetTexture("UI/button_sound_off.tga");
	else if (GSMenu::sfx == 1)
		texture = ResourceManagers::GetInstance()->GetTexture("UI/button_sound.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth/2.f + 220.f, Globals::screenHeight * 6.5 / 10.f);
	button->SetISize(100, 100);
	button->SetOnClickTexture([](std::shared_ptr<GameButton> button) {
		GSMenu::sfx = !GSMenu::sfx;
		if (GSMenu::sfx == 0)
			button->SetTexture(ResourceManagers::GetInstance()->GetTexture("UI/button_sound_off.tga"));
		else if (GSMenu::sfx == 1)
			button->SetTexture(ResourceManagers::GetInstance()->GetTexture("UI/button_sound.tga"));
		});
	m_listButton.push_back(button);

	// text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Rot.ttf");
	std::shared_ptr<Text> m_textInMenu = std::make_shared< Text>(shader, font, "Difficulty", Vector4(1.f, 0.6f, 0.f, 1.0f), 1.7f);
	m_textInMenu->Set2DPosition(Vector2(320.f, Globals::screenHeight * 3.5 / 10.f + 15.f));
	m_listText.push_back(m_textInMenu);

	m_textInMenu = std::make_shared< Text>(shader, font, "Background Music", Vector4(1.f, 0.6f, 0.f, 1.0f), 1.7f);
	m_textInMenu->Set2DPosition(Vector2(320.f, Globals::screenHeight * 5 / 10.f + 15.f));
	m_listText.push_back(m_textInMenu);

	m_textInMenu = std::make_shared< Text>(shader, font, "VFX Sound", Vector4(1.f, 0.6f, 0.f, 1.0f), 1.7f);
	m_textInMenu->Set2DPosition(Vector2(320.f, Globals::screenHeight * 6.5 / 10.f + 15.f));
	m_listText.push_back(m_textInMenu);

}

void GSSetting::Exit()
{
}


void GSSetting::Pause()
{
}

void GSSetting::Resume()
{
}


void GSSetting::HandleEvents()
{
}

void GSSetting::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSSetting::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto& button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSSetting::HandleMouseMoveEvents(int x, int y)
{
}

void GSSetting::Update(float deltaTime)
{
	for (auto& button : m_listButton)
	{
		button->Update(deltaTime);
	}
}

void GSSetting::Draw()
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
