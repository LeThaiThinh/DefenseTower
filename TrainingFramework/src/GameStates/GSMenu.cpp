#include "GSMenu.h"
#include "Base/Camera.h"
#include "ResourceManagers.h"
#include "GSSelectStage.h"
#include <Resource/ResourceTable.h>
#include "BackgroundMusic.h"
bool GSMenu::backgroundMusic = true;
bool GSMenu::vfxSound = true;
int	GSMenu::difficulty = 0;
int GSMenu::diamond = 0;

GSMenu::GSMenu() : GameStateBase(StateType::STATE_MENU),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<GameButton>>{}), m_listText(std::list<std::shared_ptr<Text>>{})
{
}


GSMenu::~GSMenu()
{
}



void GSMenu::Init()
{
	BackgroundMusic::GetInstance()->PlayBGMMenu();

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("UI/bg_2.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(Globals::screenWidth / 2.f, Globals::screenHeight / 2.f);
	m_background->SetISize(Globals::screenWidth, Globals::screenHeight);

	// title table
	texture= ResourceManagers::GetInstance()->GetTexture("UI/table.tga");
	m_titleTable = std::make_shared<Sprite2D>(model, shader, texture);
	m_titleTable->Set2DPosition(Globals::screenWidth / 2.f, Globals::screenHeight * 2.25 / 10.f);
	m_titleTable->SetISize(Globals::screenWidth * 2 / 3.f , Globals::screenHeight / 8.f);

	// continue button
	texture = ResourceManagers::GetInstance()->GetTexture("UI/table.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2.f, Globals::screenHeight * 5 / 10.f);
	button->SetISize(Globals::screenWidth / 3.f, Globals::screenHeight / 10.f);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PushState(StateType::STATE_SELECT_STAGE);
		});
	m_listButton.push_back(button);

	// new game button
	texture = ResourceManagers::GetInstance()->GetTexture("UI/table.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2.f, Globals::screenHeight * 6.33 / 10.f);
	button->SetISize(Globals::screenWidth / 3.f, Globals::screenHeight / 10.f);
	button->SetOnClick([]() {
		GSSelectStage::currentLevel = 1;
		GameStateMachine::GetInstance()->PushState(StateType::STATE_SELECT_STAGE);
		});
	m_listButton.push_back(button);

	// tutorial button
	texture = ResourceManagers::GetInstance()->GetTexture("UI/table.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2.f, Globals::screenHeight * 7.66 / 10.f);
	button->SetISize(Globals::screenWidth / 3.f, Globals::screenHeight / 10.f);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PushState(StateType::STATE_TUTORIAL);
		});
	m_listButton.push_back(button);

	// credit button
	texture = ResourceManagers::GetInstance()->GetTexture("UI/table.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2.f, Globals::screenHeight * 9 / 10.f);
	button->SetISize(Globals::screenWidth / 3.f, Globals::screenHeight / 10.f);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PushState(StateType::STATE_CREDIT);
		});
	m_listButton.push_back(button);

	// exit button
	texture = ResourceManagers::GetInstance()->GetTexture("UI/button_close_2.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 100.f, 100.f);
	button->SetISize(100, 100);
	button->SetOnClick([]() {
		exit(0);
		});
	m_listButton.push_back(button);

	// setting button
	texture = ResourceManagers::GetInstance()->GetTexture("UI/button_settings.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(100.f, 100.f);
	button->SetISize(100, 100);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PushState(StateType::STATE_SETTING);
		});
	m_listButton.push_back(button);


	// rope
	//texture = ResourceManagers::GetInstance()->GetTexture("UI/rope_small.tga");
	auto sprite = std::make_shared<Sprite2D>(model, shader, texture);
	/*sprite->Set2DPosition(Globals::screenWidth - 100.f, 50.f);
	sprite->SetISize(10, 100);
	m_listRope.push_back(sprite);
	sprite = std::make_shared<Sprite2D>(model, shader, texture);
	sprite->Set2DPosition(100.f, 50.f);
	sprite->SetISize(10, 100);
	m_listRope.push_back(sprite);*/
	texture = ResourceManagers::GetInstance()->GetTexture("UI/rope_big.tga");
	sprite = std::make_shared<Sprite2D>(model, shader, texture);
	sprite->Set2DPosition(Globals::screenWidth/2.f - 150.f, Globals::screenHeight/8.f);
	sprite->SetISize(15, Globals::screenHeight * 3 / 10.f);
	m_listRope.push_back(sprite);
	sprite = std::make_shared<Sprite2D>(model, shader, texture);
	sprite->Set2DPosition(Globals::screenWidth/2.f + 150.f, Globals::screenHeight/8.f);
	sprite->SetISize(30, Globals::screenHeight * 3 / 10.f);
	m_listRope.push_back(sprite);
	sprite = std::make_shared<Sprite2D>(model, shader, texture);
	sprite->Set2DPosition(Globals::screenWidth / 2.f - 150.f, Globals::screenHeight*3/8.f);
	sprite->SetISize(30, Globals::screenHeight * 3 / 10.f);
	m_listRope.push_back(sprite);
	sprite = std::make_shared<Sprite2D>(model, shader, texture);
	sprite->Set2DPosition(Globals::screenWidth / 2.f + 150.f, Globals::screenHeight*3 / 8.f);
	sprite->SetISize(30, Globals::screenHeight * 3 / 10.f);
	m_listRope.push_back(sprite);
	sprite = std::make_shared<Sprite2D>(model, shader, texture);
	sprite->Set2DPosition(Globals::screenWidth / 2.f - 150.f, Globals::screenHeight*5 / 8.f);
	sprite->SetISize(30, Globals::screenHeight * 5 / 10.f);
	m_listRope.push_back(sprite);
	sprite = std::make_shared<Sprite2D>(model, shader, texture);
	sprite->Set2DPosition(Globals::screenWidth / 2.f + 150.f, Globals::screenHeight*5 / 8.f);
	sprite->SetISize(30, Globals::screenHeight * 5 / 10.f);
	m_listRope.push_back(sprite);

	// game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Rot.ttf");
	std::shared_ptr<Text> m_textInMenu = std::make_shared< Text>(shader, font, "Territory Conquest", Vector4(1.0f, 0.6f, 0.f, 1.0f), 3.0f);
	m_textInMenu->Set2DPosition(Vector2(240.f, Globals::screenHeight * 2.25 / 10.f + 25));
	m_listText.push_back(m_textInMenu);

	//continue text
	 m_textInMenu = std::make_shared< Text>(shader, font, "Continue", Vector4(1.f, 0.6f, 0.f, 1.0f), 2.0f);
	m_textInMenu->Set2DPosition(Vector2(495.f, Globals::screenHeight * 5 / 10.f+15.f));
	m_listText.push_back(m_textInMenu);

	//new game text
	m_textInMenu = std::make_shared< Text>(shader, font, "New game", Vector4(1.f, 0.6f, 0.f, 1.0f), 2.0f);
	m_textInMenu->Set2DPosition(Vector2(490.f, Globals::screenHeight * 6.33 / 10.f+15.f));
	m_listText.push_back(m_textInMenu);

	//tutorial text
	m_textInMenu = std::make_shared< Text>(shader, font, "Tutorial", Vector4(1.0f, 0.6f, 0.f, 1.0f), 2.0f);
	m_textInMenu->Set2DPosition(Vector2(500.f, Globals::screenHeight * 7.66 / 10.f + 15.f));
	m_listText.push_back(m_textInMenu);

	//credit text
	m_textInMenu = std::make_shared< Text>(shader, font, "Credit", Vector4(1.0f, 0.6f, 0.f, 1.0f), 2.0f);
	m_textInMenu->Set2DPosition(Vector2(525.f, Globals::screenHeight * 9 / 10.f+15.f));
	m_listText.push_back(m_textInMenu);
}

void GSMenu::Exit()
{
}


void GSMenu::Pause()
{
}

void GSMenu::Resume()
{
}


void GSMenu::HandleEvents()
{
}

void GSMenu::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSMenu::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto &button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSMenu::HandleMouseMoveEvents(int x, int y)
{
}

void GSMenu::Update(float deltaTime)
{
	for (auto &button : m_listButton)
	{
		button->Update(deltaTime);
	}
}

void GSMenu::Draw()
{
	m_background->Draw();
	for (auto& rope : m_listRope)
	{
		rope->Draw();
	}
	m_titleTable->Draw();
	for (auto &button : m_listButton)
	{
		button->Draw();
	}
	for (auto& text : m_listText) {
		text->Draw();
	}

}
