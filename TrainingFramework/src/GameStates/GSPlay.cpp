#include "GSPlay.h"
#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "GameButton.h"
#include "Bullet.h"
#include <Application.h>
#include "CheckCollision.h"
#include "EnemyManager.h"
#include "ResourceTable.h"
#include "BackgroundMusic.h"
float EnemyPoolManager::currentTimeFindPath = 3;
int GSPlay::win = -1;
GSPlay::GSPlay() :GameStateBase(StateType::STATE_PLAY), m_time(0),m_mainCharacter(std::make_shared<MainCharacter>()),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<GameButton>>{})
{
}

GSPlay::~GSPlay()
{
}

void GSPlay::Init()
{
	if(GSMenu::backgroundMusic)
		BackgroundMusic::GetInstance()->PlayBGMIngame();
	srand(time(0));
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("UI/bg_land.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(Globals::screenWidth / 2.f, Globals::screenHeight / 2.f);
	m_background->SetISize(Globals::mapWidth, Globals::mapHeight);
	// button menu
	texture = ResourceManagers::GetInstance()->GetTexture("UI/button_menu.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DStaticPosition(Globals::screenWidth - 50.f, 50.f);
	button->SetISize(75, 75);
	button->SetOnClick([]() {
		Application::GetInstance()->GetCamera()->SetMoveCamera(-Application::GetInstance()->GetCamera()->GetPosition());
		Application::GetInstance()->GetCamera()->Update(1 / 300.f);
		Application::GetInstance()->GetCamera()->SetMoveCamera(Vector3(0, 0, 0));
		GameStateMachine::GetInstance()->PushState(StateType::STATE_MENU_IN_GAME);
		});
	m_listButton.push_back(button);
	// init
	DefensivePoolManager::GetInstance()->Init();
	EnemyPoolManager::GetInstance()->Init();
	ResourceTable::GetInstance()->Init();
}

void GSPlay::HandleEvents()
{
}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	if (bIsPressed == true) {
		switch (key)
		{
		case 'A':
			keyPressed |= KEY_MOVE_LEFT;
			break;
		case 'D':
			keyPressed |= KEY_MOVE_RIGHT;
			break;
		case 'W':
			keyPressed |= KEY_MOVE_FORWARD;
			break;
		case 'S':
			keyPressed |= KEY_MOVE_BACKWARD;
			break;
		case VK_SPACE:
			keyPressed |= KEY_SPACE;
			break;
		default:
			break;
		}
	}
	else {
		switch (key) {
		case 'A':
			keyPressed ^= KEY_MOVE_LEFT;
			break;
		case 'D':
			keyPressed ^= KEY_MOVE_RIGHT;
			break;
		case 'W':
			keyPressed ^= KEY_MOVE_FORWARD;
			break;
		case 'S':
			keyPressed ^= KEY_MOVE_BACKWARD;
			break;
		case VK_SPACE:
			keyPressed ^= KEY_SPACE;
			break;
		default:
			break;
		}
	}
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto &button : m_listButton)
	{
		if (button->HandleTouchEvents((int)Application::GetInstance()->GetCamera()->GetPosition().x + x, (int)Application::GetInstance()->GetCamera()->GetPosition().y + y, bIsPressed))
		{
			return;
		}
	}
	DefensivePoolManager::GetInstance()->HandleTouchEvents((int)Application::GetInstance()->GetCamera()->GetPosition().x + x, (int)Application::GetInstance()->GetCamera()->GetPosition().y + y, bIsPressed);
	m_mainCharacter->HandleTouchEvents((int)Application::GetInstance()->GetCamera()->GetPosition().x + x, (int)Application::GetInstance()->GetCamera()->GetPosition().y + y, bIsPressed);
}

void GSPlay::HandleMouseMoveEvents(int x, int y)
{
	if (Application::GetInstance()->GetCamera()->GetMoveCamera().x == 0) {
		if (x >= Globals::screenWidth - Globals::borderMoveCam) {
			Application::GetInstance()->GetCamera()->SetMoveCamera(Vector3(1, 0, 0));
		}
		if (x <= Globals::borderMoveCam) {
			Application::GetInstance()->GetCamera()->SetMoveCamera(Vector3(-1, 0, 0));
		}
	}
	else
		if (Application::GetInstance()->GetCamera()->GetMoveCamera().x != 0 && x <= Globals::screenWidth - Globals::borderMoveCam && x >= Globals::borderMoveCam) {
			Application::GetInstance()->GetCamera()->SetMoveCamera(Vector3(0, 0, 0));
		}

	if (Application::GetInstance()->GetCamera()->GetMoveCamera().y == 0) {
		if (y <= Globals::borderMoveCam)
		{
			Application::GetInstance()->GetCamera()->SetMoveCamera(Vector3(0, -1, 0));
		}
		if (y >= Globals::screenHeight - Globals::borderMoveCam)
		{
			Application::GetInstance()->GetCamera()->SetMoveCamera(Vector3(0, 1, 0));
		}
	}
	else
		if (Application::GetInstance()->GetCamera()->GetMoveCamera().y != 0 && y >= Globals::borderMoveCam && y <= Globals::screenHeight - Globals::borderMoveCam) {
			Application::GetInstance()->GetCamera()->SetMoveCamera(Vector3(0, 0, 0));
		}
}

void GSPlay::Update(float deltaTime)
{
	m_time += deltaTime;
	HandleKeyPress(deltaTime);
	Application::GetInstance()->GetCamera()->Update(deltaTime);
	ResourceTable::GetInstance()->Update();
	for (auto &it : m_listButton)
	{
		it->Update(deltaTime);
		it->Set2DStaticPosition();
	}
	m_mainCharacter->Update(deltaTime);
	DefensivePoolManager::GetInstance()->Update(deltaTime);
	DefensivePoolManager::GetInstance()->Remove();
	EnemyPoolManager::GetInstance()->Spawn(m_time);
	EnemyPoolManager::GetInstance()->Update(deltaTime);
	EnemyPoolManager::GetInstance()->Remove();
	BulletPoolManager::GetInstance()->Update(deltaTime);
	BulletPoolManager::GetInstance()->Remove();
	if (win == 1 || win == 0) {
		Application::GetInstance()->GetCamera()->SetMoveCamera(-Application::GetInstance()->GetCamera()->GetPosition());
		Application::GetInstance()->GetCamera()->Update(1 / 300.f);
		Application::GetInstance()->GetCamera()->SetMoveCamera(Vector3(0, 0, 0));
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU_AFTER_GAME);
		Coin::GetInstance()->Reset();
		DefensivePoolManager::GetInstance()->Clear();
		DefensivePoolManager::GetInstance()->Remove();
		EnemyPoolManager::GetInstance()->Clear();
		EnemyPoolManager::GetInstance()->Remove();
		BulletPoolManager::GetInstance()->Clear();
		BulletPoolManager::GetInstance()->Remove();
		BackgroundMusic::GetInstance()->StopBGMIngame();
		if (win) {
			ResourceManagers::GetInstance()->GetSound("win.wav")->PlaySoundFromStart2D(false);
			if(GSSelectStage::choosenLevel == GSSelectStage::currentLevel)
				GSSelectStage::currentLevel++;
		}
		else {
			ResourceManagers::GetInstance()->GetSound("lose.wav")->PlaySoundFromStart2D(false);
		}
	}
}

void GSPlay::Draw()
{
	m_background->Draw();
	EnemyPoolManager::GetInstance()->Draw();
	DefensivePoolManager::GetInstance()->Draw();
	BulletPoolManager::GetInstance()->Draw();
	m_mainCharacter->Draw();
	for (auto& it : m_listButton)
	{
		it->Draw();
	}
	ResourceTable::GetInstance()->Draw();
}

void GSPlay::HandleKeyPress(float deltaTime) {
	if (keyPressed & KEY_MOVE_LEFT) {
		m_mainCharacter->Move(deltaTime, Vector3(-1, 0, 0));
	}
	if (keyPressed & KEY_MOVE_RIGHT) {
		m_mainCharacter->Move(deltaTime, Vector3(1, 0, 0));
	}
	if (keyPressed & KEY_MOVE_FORWARD) {
		m_mainCharacter->Move(deltaTime, Vector3(0, -1, 0));
	}
	if (keyPressed & KEY_MOVE_BACKWARD) {
		m_mainCharacter->Move(deltaTime, Vector3(0, 1, 0));
	}
}

void GSPlay::Exit() {}

void GSPlay::Pause() {}

void GSPlay::Resume() {}
