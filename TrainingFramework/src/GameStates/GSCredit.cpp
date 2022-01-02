#include "GSCredit.h"

GSCredit::GSCredit() : GameStateBase(StateType::STATE_CREDIT)
{
}


GSCredit::~GSCredit()
{
}


void GSCredit::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("UI/bg_2.tga");

	// background
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(Globals::screenWidth / 2.f, Globals::screenHeight / 2.f);
	m_background->SetISize(Globals::mapWidth, Globals::mapHeight);

	//button close
	texture = ResourceManagers::GetInstance()->GetTexture("UI/button_close_2.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth * 5 / 6.f - 25.f, Globals::screenHeight / 6.f + 25.f);
	button->SetISize(75, 75);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);


	// title table
	texture = ResourceManagers::GetInstance()->GetTexture("UI/table.tga");
	m_table = std::make_shared<Sprite2D>(model, shader, texture);
	m_table->Set2DPosition(Globals::screenWidth / 2.f, Globals::screenHeight / 2.f);
	m_table->SetISize(Globals::screenWidth * 2 / 3.f, Globals::screenHeight * 2 / 3.f);

	// credit
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Rot.ttf");
	std::shared_ptr<Text> m_textInMenu = std::make_shared< Text>(shader, font, "Credit", Vector4(1.0f, 0.6f, 0.f, 1.0f), 3.0f);
	m_textInMenu->Set2DPosition(Vector2(480.f, Globals::screenHeight * 2.5 / 10.f + 25));
	m_listText.push_back(m_textInMenu);

	m_textInMenu = std::make_shared< Text>(shader, font, "Designer - Le Thai Thinh", Vector4(1.f, 0.6f, 0.f, 1.0f), 2.0f);
	m_textInMenu->Set2DPosition(Vector2(310.f, Globals::screenHeight * 4 / 10.f + 15.f));
	m_listText.push_back(m_textInMenu);

	m_textInMenu = std::make_shared< Text>(shader, font, "Programmer - Le Thai Thinh", Vector4(1.f, 0.6f, 0.f, 1.0f), 2.0f);
	m_textInMenu->Set2DPosition(Vector2(280.f, Globals::screenHeight * 5 / 10.f + 15.f));
	m_listText.push_back(m_textInMenu);

	m_textInMenu = std::make_shared< Text>(shader, font, "Donor - Le Thai Thinh", Vector4(1.f, 0.6f, 0.f, 1.0f), 2.0f);
	m_textInMenu->Set2DPosition(Vector2(355.f, Globals::screenHeight * 6 / 10.f + 15.f));
	m_listText.push_back(m_textInMenu);

	m_textInMenu = std::make_shared< Text>(shader, font, "Producer - Le Thai Thinh", Vector4(1.f, 0.6f, 0.f, 1.0f), 2.0f);
	m_textInMenu->Set2DPosition(Vector2(310.f, Globals::screenHeight * 7 / 10.f + 15.f));
	m_listText.push_back(m_textInMenu);
}

void GSCredit::Exit()
{
}


void GSCredit::Pause()
{
}

void GSCredit::Resume()
{
}


void GSCredit::HandleEvents()
{
}

void GSCredit::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSCredit::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto& button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSCredit::HandleMouseMoveEvents(int x, int y)
{
}

void GSCredit::Update(float deltaTime)
{
	for (auto& button : m_listButton)
	{
		button->Update(deltaTime);
	}
}

void GSCredit::Draw()
{
	m_background->Draw();
	m_table->Draw();
	for (auto& button : m_listButton)
	{
		button->Draw();
	}
	for (auto& text : m_listText) {
		text->Draw();
	}
}
