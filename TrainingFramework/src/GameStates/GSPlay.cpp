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
#include "Coin.h"
float EnemyPoolManager::currentTimeFindPath = 3;
GSPlay::GSPlay() :GameStateBase(StateType::STATE_PLAY), m_time(0),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<GameButton>>{})
{
}

GSPlay::~GSPlay()
{
}

void GSPlay::Init()
{

	srand(time(0));
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("AbandonedForestBackground.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(Globals::screenWidth / 2.f, Globals::screenHeight / 2.f);
	m_background->SetISize(Globals::mapWidth, Globals::mapHeight);
	// button clode
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50.f, 50.f);
	button->SetISize(50, 50);
	button->SetOnClick([]() {
		Coin::GetInstance()->Reset();
		Application::GetInstance()->GetCamera()->SetMoveCamera(-Application::GetInstance()->GetCamera()->GetPosition());
		Application::GetInstance()->GetCamera()->Update(1 / 300.f);
		Application::GetInstance()->GetCamera()->SetMoveCamera(Vector3(0, 0, 0));
		GameStateMachine::GetInstance()->PopState();
		DefensivePoolManager::GetInstance()->Clear();
		DefensivePoolManager::GetInstance()->Remove();
		EnemyPoolManager::GetInstance()->Clear();
		EnemyPoolManager::GetInstance()->Remove();
		});
	m_listButton.push_back(button);
	//
	m_mainCharacter = std::make_shared<MainCharacter>();

	DefensivePoolManager::GetInstance()->Init();
	EnemyPoolManager::GetInstance()->Init();
	Coin::GetInstance()->Init(1);
	// score
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");

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
	for (auto button : m_listButton)
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
	Coin::GetInstance()->Update();
	HandleKeyPress(deltaTime);
	Application::GetInstance()->GetCamera()->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
		it->Set2DPosition(Application::GetInstance()->GetCamera()->GetPosition().x + Globals::screenWidth - 50.f, Application::GetInstance()->GetCamera()->GetPosition().y + 50.f);
	}
	m_mainCharacter->Update(deltaTime);
	DefensivePoolManager::GetInstance()->Update(deltaTime);
	DefensivePoolManager::GetInstance()->Remove();
	BulletPoolManager::GetInstance()->Update(deltaTime);
	BulletPoolManager::GetInstance()->Remove();
	EnemyPoolManager::GetInstance()->Spawn(m_time);
	EnemyPoolManager::GetInstance()->Update(deltaTime);
	EnemyPoolManager::GetInstance()->Remove();
}

void GSPlay::Draw()
{
	m_background->Draw();
	Coin::GetInstance()->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	DefensivePoolManager::GetInstance()->Draw();
	BulletPoolManager::GetInstance()->Draw();
	EnemyPoolManager::GetInstance()->Draw();
	m_mainCharacter->Draw();
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
