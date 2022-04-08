#include "GSSelectStage.h"
#include "Resource/ResourceTable.h"
int GSSelectStage::choosenLevel = 0;
int GSSelectStage::currentLevel = 0;
GSSelectStage::GSSelectStage() : GameStateBase(StateType::STATE_SELECT_STAGE)
{
}

GSSelectStage::~GSSelectStage()
{
}

void GSSelectStage::Init()
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

	// header table
	texture = ResourceManagers::GetInstance()->GetTexture("UI/header_levels.tga");
	m_header = std::make_shared<Sprite2D>(model, shader, texture);
	m_header->Set2DPosition(Globals::screenWidth / 2.f, Globals::screenHeight / 5.f);
	m_header->SetISize(Globals::screenWidth / 4.f, 100.f);

	//rope
	texture = ResourceManagers::GetInstance()->GetTexture("UI/rope_big.tga");
	auto sprite = std::make_shared<Sprite2D>(model, shader, texture);
	sprite->Set2DPosition(Globals::screenWidth / 2.f - 200.f, Globals::screenHeight / 8.f);
	sprite->SetISize(30, Globals::screenHeight * 3 / 10.f);
	m_listRope.push_back(sprite);
	sprite = std::make_shared<Sprite2D>(model, shader, texture);
	sprite->Set2DPosition(Globals::screenWidth / 2.f + 200.f, Globals::screenHeight / 8.f);
	sprite->SetISize(30, Globals::screenHeight * 3 / 10.f);
	m_listRope.push_back(sprite);
	//level number
	{
		if (currentLevel >= 1)
			texture = ResourceManagers::GetInstance()->GetTexture("UI/num_1.tga");
		else
			texture = ResourceManagers::GetInstance()->GetTexture("UI/lock.tga");
		sprite = std::make_shared<Sprite2D>(model, shader, texture);
		sprite->Set2DPosition(Globals::screenWidth * 2 / 6.f - 5, Globals::screenHeight * 2.25 / 6.f);
		sprite->SetISize(50, 75);
		m_listLevelNumber.push_back(sprite);

		if (currentLevel >= 2)
			texture = ResourceManagers::GetInstance()->GetTexture("UI/num_2.tga");
		else
			texture = ResourceManagers::GetInstance()->GetTexture("UI/lock.tga");
		sprite = std::make_shared<Sprite2D>(model, shader, texture);
		sprite->Set2DPosition(Globals::screenWidth * 3 / 6.f, Globals::screenHeight * 2.25 / 6.f);
		sprite->SetISize(60, 75);
		m_listLevelNumber.push_back(sprite);

		if (currentLevel >= 3)
			texture = ResourceManagers::GetInstance()->GetTexture("UI/num_3.tga");
		else
			texture = ResourceManagers::GetInstance()->GetTexture("UI/lock.tga");
		sprite = std::make_shared<Sprite2D>(model, shader, texture);
		sprite->Set2DPosition(Globals::screenWidth * 4 / 6.f, Globals::screenHeight * 2.25 / 6.f);
		sprite->SetISize(60, 75);
		m_listLevelNumber.push_back(sprite);

		if (currentLevel >= 4)
			texture = ResourceManagers::GetInstance()->GetTexture("UI/num_4.tga");
		else
			texture = ResourceManagers::GetInstance()->GetTexture("UI/lock.tga");
		sprite = std::make_shared<Sprite2D>(model, shader, texture);
		sprite->Set2DPosition(Globals::screenWidth * 2 / 6.f, Globals::screenHeight * 3.75 / 6.f);
		sprite->SetISize(60, 75);
		m_listLevelNumber.push_back(sprite);

		if (currentLevel >= 5)
			texture = ResourceManagers::GetInstance()->GetTexture("UI/num_5.tga");
		else
			texture = ResourceManagers::GetInstance()->GetTexture("UI/lock.tga");
		sprite = std::make_shared<Sprite2D>(model, shader, texture);
		sprite->Set2DPosition(Globals::screenWidth * 3 / 6.f, Globals::screenHeight * 3.75 / 6.f);
		sprite->SetISize(60, 75);
		m_listLevelNumber.push_back(sprite);

		if (currentLevel >= 6)
			texture = ResourceManagers::GetInstance()->GetTexture("UI/num_6.tga");
		else
			texture = ResourceManagers::GetInstance()->GetTexture("UI/lock.tga");
		sprite = std::make_shared<Sprite2D>(model, shader, texture);
		sprite->Set2DPosition(Globals::screenWidth * 4 / 6.f, Globals::screenHeight * 3.75 / 6.f);
		sprite->SetISize(60, 75);
		m_listLevelNumber.push_back(sprite);
	}
	//button 
	{
		// button back
		texture = ResourceManagers::GetInstance()->GetTexture("UI/button_close_2.tga");
		std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
		button->Set2DPosition(Globals::screenWidth * 5 / 6.f - 25.f, Globals::screenHeight / 6.f + 25.f);
		button->SetISize(75, 75);
		button->SetOnClick([]() {
			GameStateMachine::GetInstance()->PopState();
			});
		m_listButton.push_back(button);
		// button shop
		texture = ResourceManagers::GetInstance()->GetTexture("UI/button_shop.tga");
		button = std::make_shared<GameButton>(model, shader, texture);
		button->Set2DPosition(Globals::screenWidth * 1 / 6.f + 25.f, Globals::screenHeight / 6.f + 25.f);
		button->SetISize(75, 75);
		button->SetOnClick([]() {
			GameStateMachine::GetInstance()->PushState(StateType::STATE_SHOP);
			});
		m_listButton.push_back(button);
		//button level
		texture = ResourceManagers::GetInstance()->GetTexture("UI/btton_empty.tga");
		button = std::make_shared<GameButton>(model, shader, texture);
		button->Set2DPosition(Globals::screenWidth * 2 / 6.f, Globals::screenHeight * 2.25 / 6.f);
		button->SetISize(150, 150);
		if (currentLevel >= 1) {
			button->SetOnClick([]() {
				GSSelectStage::choosenLevel = 1;
				GameStateMachine::GetInstance()->PushState(StateType::STATE_LOAD_GAME);
				});
		}
		else {
			button->SetOnClick([]() {});
		}
		m_listButton.push_back(button);

		texture = ResourceManagers::GetInstance()->GetTexture("UI/btton_empty.tga");
		button = std::make_shared<GameButton>(model, shader, texture);
		button->Set2DPosition(Globals::screenWidth * 3 / 6.f, Globals::screenHeight * 2.25 / 6.f);
		button->SetISize(150, 150);
		if (currentLevel >= 2) {
			button->SetOnClick([]() {
				GSSelectStage::choosenLevel = 2;
				GameStateMachine::GetInstance()->PushState(StateType::STATE_LOAD_GAME);
				});
		}
		else {
			button->SetOnClick([]() {});
		}
		m_listButton.push_back(button);

		texture = ResourceManagers::GetInstance()->GetTexture("UI/btton_empty.tga");
		button = std::make_shared<GameButton>(model, shader, texture);
		button->Set2DPosition(Globals::screenWidth * 4 / 6.f, Globals::screenHeight * 2.25 / 6.f);
		button->SetISize(150, 150);
		if (currentLevel >= 3) {
			button->SetOnClick([]() {
				GSSelectStage::choosenLevel = 3;
				GameStateMachine::GetInstance()->PushState(StateType::STATE_LOAD_GAME);
				});
		}
		else {
			button->SetOnClick([]() {});
		}
		m_listButton.push_back(button);

		texture = ResourceManagers::GetInstance()->GetTexture("UI/btton_empty.tga");
		button = std::make_shared<GameButton>(model, shader, texture);
		button->Set2DPosition(Globals::screenWidth * 2 / 6.f, Globals::screenHeight * 3.75 / 6.f);
		button->SetISize(150, 150);
		if (currentLevel >= 4) {
			button->SetOnClick([]() {
				GSSelectStage::choosenLevel = 4;
				GameStateMachine::GetInstance()->PushState(StateType::STATE_LOAD_GAME);
				});
		}
		else {
			button->SetOnClick([]() {});
		}
		m_listButton.push_back(button);

		texture = ResourceManagers::GetInstance()->GetTexture("UI/btton_empty.tga");
		button = std::make_shared<GameButton>(model, shader, texture);
		button->Set2DPosition(Globals::screenWidth * 3 / 6.f, Globals::screenHeight * 3.75 / 6.f);
		button->SetISize(150, 150);
		if (currentLevel >= 5) {
			button->SetOnClick([]() {
				GSSelectStage::choosenLevel = 5;
				GameStateMachine::GetInstance()->PushState(StateType::STATE_LOAD_GAME);
				});
		}
		else {
			button->SetOnClick([]() {});
		}
		m_listButton.push_back(button);

		texture = ResourceManagers::GetInstance()->GetTexture("UI/btton_empty.tga");
		button = std::make_shared<GameButton>(model, shader, texture);
		button->Set2DPosition(Globals::screenWidth * 4 / 6.f, Globals::screenHeight * 3.75 / 6.f);
		button->SetISize(150, 150);
		if (currentLevel >= 6) {
			button->SetOnClick([]() {
				GSSelectStage::choosenLevel = 6;
				GameStateMachine::GetInstance()->PushState(StateType::STATE_LOAD_GAME);
				});
		}
		else {
			button->SetOnClick([]() {});
		}
		m_listButton.push_back(button);
	}

	ResourceTable::GetInstance()->Init();
	
}

void GSSelectStage::Exit()
{
}


void GSSelectStage::Pause()
{
}

void GSSelectStage::Resume()
{
}


void GSSelectStage::HandleEvents()
{
}

void GSSelectStage::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSSelectStage::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto& button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSSelectStage::HandleMouseMoveEvents(int x, int y)
{
}

void GSSelectStage::Update(float deltaTime)
{
	for (auto& button : m_listButton)
	{
		button->Update(deltaTime);
	}
	ResourceTable::GetInstance()->UpdateMiddle();
}

void GSSelectStage::Draw()
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
	for (auto& number : m_listLevelNumber)
	{
		number->Draw();
	}
}
