#include "GSTutorial.h"

GSTutorial::GSTutorial() : GameStateBase(StateType::STATE_TUTORIAL)
{
}


GSTutorial::~GSTutorial()
{
}


void GSTutorial::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("UI/bg_2.tga");

	// background
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(Globals::screenWidth / 2.f, Globals::screenHeight / 2.f);
	m_background->SetISize(Globals::mapWidth, Globals::mapHeight);

	// table
	texture = ResourceManagers::GetInstance()->GetTexture("UI/table.tga");
	m_table = std::make_shared<Sprite2D>(model, shader, texture);
	m_table->Set2DPosition(Globals::screenWidth / 2.f, Globals::screenHeight / 2.f);
	m_table->SetISize(Globals::screenWidth * 2 / 3.f, Globals::screenHeight * 2 / 3.f);

	//button close
	texture = ResourceManagers::GetInstance()->GetTexture("UI/button_close_2.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth * 5 / 6.f - 25.f, Globals::screenHeight / 6.f + 25.f);
	button->SetISize(75, 75);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);
}

void GSTutorial::Exit()
{
}


void GSTutorial::Pause()
{
}

void GSTutorial::Resume()
{
}


void GSTutorial::HandleEvents()
{
}

void GSTutorial::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSTutorial::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto& button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSTutorial::HandleMouseMoveEvents(int x, int y)
{
}

void GSTutorial::Update(float deltaTime)
{
	for (auto& button : m_listButton)
	{
		button->Update(deltaTime);
	}
}

void GSTutorial::Draw()
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
