#include "GSShop.h"
#include "Resource/ResourceTable.h"
#include "Upgrade/Upgrade.h"

GSShop::GSShop() : GameStateBase(StateType::STATE_SHOP)
{
}

GSShop::~GSShop()
{
}

void GSShop::Init()
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
	m_table->SetISize(Globals::screenWidth * 5 / 6.f, Globals::screenHeight * 5 / 6.f);

	// header table
	texture = ResourceManagers::GetInstance()->GetTexture("UI/header_shop.tga");
	m_header = std::make_shared<Sprite2D>(model, shader, texture);
	m_header->Set2DPosition(Globals::screenWidth / 2.f, Globals::screenHeight / 8.f);
	m_header->SetISize(Globals::screenWidth / 4.f, 100.f);

	//rope
	texture = ResourceManagers::GetInstance()->GetTexture("UI/rope_big.tga");
	auto sprite = std::make_shared<Sprite2D>(model, shader, texture);
	sprite->Set2DPosition(Globals::screenWidth / 2.f - 200.f, Globals::screenHeight / 16.f);
	sprite->SetISize(30, Globals::screenHeight * 3 / 10.f);
	m_listRope.push_back(sprite);
	sprite = std::make_shared<Sprite2D>(model, shader, texture);
	sprite->Set2DPosition(Globals::screenWidth / 2.f + 200.f, Globals::screenHeight / 16.f);
	sprite->SetISize(30, Globals::screenHeight * 3 / 10.f);
	m_listRope.push_back(sprite);
	
	// button back
	texture = ResourceManagers::GetInstance()->GetTexture("UI/button_left.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth * 1 / 12.f + 12.f, Globals::screenHeight / 12.f + 12.f);
	button->SetISize(75, 75);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);
}

void GSShop::Exit()
{
}


void GSShop::Pause()
{
}

void GSShop::Resume()
{
}


void GSShop::HandleEvents()
{
}

void GSShop::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSShop::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto& button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
	Upgrade::GetInstance()->HandleTouchEvents(x, y, bIsPressed);
}

void GSShop::HandleMouseMoveEvents(int x, int y)
{
	Upgrade::GetInstance()->HandleMouseMoveEvents(x,y);
}

void GSShop::Update(float deltaTime)
{
	for (auto& button : m_listButton)
	{
		button->Update(deltaTime);
	}
	ResourceTable::GetInstance()->UpdateMiddle();
}

void GSShop::Draw()
{
	m_background->Draw();
	m_table->Draw();
	m_header->Draw();
	ResourceTable::GetInstance()->DrawMiddle();
	for (auto& rope : m_listRope)
	{
		rope->Draw();
	}
	for (auto& button : m_listButton)
	{
		button->Draw();
	}
	Upgrade::GetInstance()->Draw();

}
