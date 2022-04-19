#include "GSPlay.h"
#include "Base/Shader.h"
#include "Base/Texture.h"
#include "Base/Model.h"
#include "Base/Camera.h"
#include "Base/Font.h"
#include "Base/Sprite2D.h"
#include "Base/Sprite3D.h"
#include "Base/Text.h"
#include "Others/GameButton.h"
#include "Bullet/Bullet.h"
#include <Application.h>
#include "CheckCollision.h"
#include "Enemy/EnemyManager.h"
#include "Resource/ResourceTable.h"
#include "BackgroundMusic.h"
#include "Pathing/ObstacleManager.h"
#include "Pathing/FloydWarshall.h"
#include "HUD/HUD.h"
#include "GameObject/Timer.h"
float EnemyPoolManager::currentTimeFindPath = 3;
int GSPlay::win = -1;
GSPlay::GSPlay() :GameStateBase(StateType::STATE_PLAY), m_time(0),m_count(0),
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
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("UI/bg_land.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	// background
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
	HUD::GetInstance()->HandleTouchEvents((int)Application::GetInstance()->GetCamera()->GetPosition().x + x, (int)Application::GetInstance()->GetCamera()->GetPosition().y + y, bIsPressed);
	if(DefensivePoolManager::GetInstance()->HandleTouchEvents((int)Application::GetInstance()->GetCamera()->GetPosition().x + x, (int)Application::GetInstance()->GetCamera()->GetPosition().y + y, bIsPressed)) {
		return;
	}
	MainCharacter::GetInstance()->HandleTouchEvents((int)Application::GetInstance()->GetCamera()->GetPosition().x + x, (int)Application::GetInstance()->GetCamera()->GetPosition().y + y, bIsPressed);
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
	//std::cout << deltaTime << std::endl;
	if (deltaTime > 0) {
		m_time += deltaTime;
		m_count++;
	}

	HandleKeyPress(deltaTime);
	Application::GetInstance()->GetCamera()->Update(deltaTime);
	ResourceTable::GetInstance()->Update();
	for (auto &it : m_listButton)
	{
		it->Update(deltaTime);
		it->Set2DStaticPosition();
	}
	MainCharacter::GetInstance()->Update(deltaTime);
	DefensivePoolManager::GetInstance()->Update(deltaTime);
	DefensivePoolManager::GetInstance()->Remove();
	EnemyPoolManager::GetInstance()->Spawn(m_time);
	EnemyPoolManager::GetInstance()->Update(deltaTime);
	EnemyPoolManager::GetInstance()->Remove();
	BulletPoolManager::GetInstance()->Update(deltaTime);
	BulletPoolManager::GetInstance()->Remove();
	HUD::GetInstance()->Update();
	/*Timer::GetInstance()->EndAddTimeOperationPerCircle("GroundEnemy25");
	Timer::GetInstance()->EndAddTimeOperationPerCircle("GroundEnemyConnect25");
	Timer::GetInstance()->EndAddTimeOperationPerCircle("GroundEnemy50");
	Timer::GetInstance()->EndAddTimeOperationPerCircle("GroundEnemyConnect50");
	Timer::GetInstance()->EndAddTimeOperationPerCircle("GroundEnemy100");
	Timer::GetInstance()->EndAddTimeOperationPerCircle("GroundEnemyConnect100");*/
	if (win == 1 || win == 0) {
		Application::GetInstance()->GetCamera()->SetMoveCamera(-Application::GetInstance()->GetCamera()->GetPosition());
		Application::GetInstance()->GetCamera()->Update(1 / 300.f);
		Application::GetInstance()->GetCamera()->SetMoveCamera(Vector3(0, 0, 0));
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU_AFTER_GAME);
		Coin::GetInstance()->Reset();
		MainCharacter::FreeInstance();
		DefensivePoolManager::GetInstance()->Clear();
		DefensivePoolManager::GetInstance()->Remove();
		FloydWarshall::GetInstance()->Clear();
		EnemyPoolManager::GetInstance()->Clear();
		EnemyPoolManager::GetInstance()->Remove();
		BulletPoolManager::GetInstance()->Clear();
		BulletPoolManager::GetInstance()->Remove();
		BackgroundMusic::GetInstance()->StopBGMIngame();
		std::cout << "average:"<<std::to_string(m_time/(float)m_count);
		/*Timer::GetInstance()->EndAddTimeOperationPerGame("GroundEnemy25");
		Timer::GetInstance()->EndAddTimeOperationPerGame("GroundEnemyConnect25");
		Timer::GetInstance()->EndAddTimeOperationPerGame("GroundEnemy50");
		Timer::GetInstance()->EndAddTimeOperationPerGame("GroundEnemyConnect50");
		Timer::GetInstance()->EndAddTimeOperationPerGame("GroundEnemy100");
		Timer::GetInstance()->EndAddTimeOperationPerGame("GroundEnemyConnect100");*/
		if (win) {
			if (GSMenu::sfx)
				ResourceManagers::GetInstance()->GetSound("win.wav")->PlaySoundFromStart2D(false);
			if(GSSelectStage::choosenLevel == GSSelectStage::currentLevel)
				GSSelectStage::currentLevel++;
		}
		else if (GSMenu::sfx) {
			ResourceManagers::GetInstance()->GetSound("lose.wav")->PlaySoundFromStart2D(false);
		}
	}
}

void GSPlay::Draw()
{
	m_background->Draw();
	EnemyPoolManager::GetInstance()->Draw();
	DefensivePoolManager::GetInstance()->Draw();
	ObstacleManager::GetInstance()->Draw();
	BulletPoolManager::GetInstance()->Draw();
	MainCharacter::GetInstance()->Draw();
	for (auto& it : m_listButton)
	{
		it->Draw();
	}
	ResourceTable::GetInstance()->Draw();
	HUD::GetInstance()->Draw();
}

void GSPlay::HandleKeyPress(float deltaTime) {
	if (keyPressed & KEY_MOVE_LEFT) {
		MainCharacter::GetInstance()->Move(deltaTime, Vector3(-1, 0, 0));
	}
	if (keyPressed & KEY_MOVE_RIGHT) {
		MainCharacter::GetInstance()->Move(deltaTime, Vector3(1, 0, 0));
	}
	if (keyPressed & KEY_MOVE_FORWARD) {
		MainCharacter::GetInstance()->Move(deltaTime, Vector3(0, -1, 0));
	}
	if (keyPressed & KEY_MOVE_BACKWARD) {
		MainCharacter::GetInstance()->Move(deltaTime, Vector3(0, 1, 0));
	}
}

void GSPlay::Exit() {}

void GSPlay::Pause() {}

void GSPlay::Resume() {}
