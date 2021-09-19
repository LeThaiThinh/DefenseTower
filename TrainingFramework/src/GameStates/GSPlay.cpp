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


GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
}


void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Fortress.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(Globals::screenWidth / 2.f, Globals::screenHeight / 2.f);
	m_background->SetSize(Globals::mapWidth, Globals::mapHeight);
	// button clode
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50.f, 50.f);
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		Application::GetInstance()->GetCamera()->SetMoveCamera(-Application::GetInstance()->GetCamera()->GetPosition());
		Application::GetInstance()->GetCamera()->Update(1/300.f);
		Application::GetInstance()->GetCamera()->SetMoveCamera(Vector3(0, 0, 0));
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);
	//
	m_mainCharacter = std::make_shared<MainCharacter>();
	TowerPoolManager::GetInstance()->GetInstance()->Add(Globals::screenWidth / 2.f, Globals::screenHeight / 2.f, TowerType::Main);
	TowerPoolManager::GetInstance()->GetInstance()->Add(20,20,TowerType::Spot);
	TowerPoolManager::GetInstance()->GetInstance()->Add(500, 20, TowerType::Spot);
	// score
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_score = std::make_shared< Text>(shader, font, "score: 10", TextColor::RED, 1.0f);
	m_score->Set2DPosition(Vector2(5, 25));
	
}

void GSPlay::Exit()
{
}


void GSPlay::Pause()
{
}

void GSPlay::Resume()
{
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
		if (button->HandleTouchEvents(Application::GetInstance()->GetCamera()->GetPosition().x+x, Application::GetInstance()->GetCamera()->GetPosition().y+ y, bIsPressed))
		{
			break;
		}
	}
	m_mainCharacter->HandleTouchEvents(Application::GetInstance()->GetCamera()->GetPosition().x+x,Application::GetInstance()->GetCamera()->GetPosition().y + y, bIsPressed);
}

void GSPlay::HandleMouseMoveEvents(int x, int y)
{
	if (Application::GetInstance()->GetCamera()->GetMoveCamera().x == 0) {
		if (x >= Globals::screenWidth  - Globals::borderMoveCam) {
			Application::GetInstance()->GetCamera()->SetMoveCamera(Vector3(1, 0, 0));
		}
		if (x <= Globals::borderMoveCam) {
			Application::GetInstance()->GetCamera()->SetMoveCamera(Vector3(-1, 0, 0));
		}
	} else
		if (Application::GetInstance()->GetCamera()->GetMoveCamera().x != 0 && x <= Globals::screenWidth - Globals::borderMoveCam && x >= Globals::borderMoveCam) {
			Application::GetInstance()->GetCamera()->SetMoveCamera(Vector3(0, 0, 0));
		}
	
	if (Application::GetInstance()->GetCamera()->GetMoveCamera().y == 0) {
		if (y <= Globals::borderMoveCam)
		{
			Application::GetInstance()->GetCamera()->SetMoveCamera(Vector3(0, -1, 0));
		}
		if (y >= Globals::screenHeight  - Globals::borderMoveCam)
		{
			Application::GetInstance()->GetCamera()->SetMoveCamera(Vector3(0, 1, 0));
		}
	} else
		if ( Application::GetInstance()->GetCamera()->GetMoveCamera().y != 0 && y >= Globals::borderMoveCam && y <= Globals::screenHeight - Globals::borderMoveCam) {
			Application::GetInstance()->GetCamera()->SetMoveCamera(Vector3(0, 0, 0));
		}
}

void GSPlay::Update(float deltaTime)
{

	HandleKeyPress(deltaTime);
	Application::GetInstance()->GetCamera()->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
		it->Set2DPosition(Application::GetInstance()->GetCamera()->GetPosition().x+ Globals::screenWidth - 50.f, Application::GetInstance()->GetCamera()->GetPosition().y + 50.f);
	}
	m_mainCharacter->Update(deltaTime);
	TowerPoolManager::GetInstance()->Update(deltaTime);
	TowerPoolManager::GetInstance()->Remove();
	BulletPoolManager::GetInstance()->Update(deltaTime);
	BulletPoolManager::GetInstance()->RemoveBullet();
}

void GSPlay::Draw()
{
	m_background->Draw();
	m_score->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_mainCharacter->Draw();
	TowerPoolManager::GetInstance()->Draw();
	BulletPoolManager::GetInstance()->Draw();
}

void GSPlay::HandleKeyPress(float deltaTime) {
	if (keyPressed & KEY_MOVE_LEFT) {	
		m_mainCharacter->Move(deltaTime, Vector2(-1, 0));
	}
	if (keyPressed & KEY_MOVE_RIGHT) {
		m_mainCharacter->Move(deltaTime, Vector2(1, 0));
	}
	if (keyPressed & KEY_MOVE_FORWARD) {
		m_mainCharacter->Move(deltaTime, Vector2(0, -1));
	}
	if (keyPressed & KEY_MOVE_BACKWARD) {
		m_mainCharacter->Move(deltaTime, Vector2(0, 1));
	}
}