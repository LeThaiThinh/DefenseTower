#include "GSSelectStage.h"
#include "Resource/ResourceTable.h"
#include "GSLoadGame.h"
#include "Enemy/EnemyManager.h"
#include "Resource/ResourceTable.h"
#include "Pathing/FloydWarshall.h"
#include "HUD/HUD.h"
#include "GameObject/Timer.h"

GSLoadGame::GSLoadGame() : GameStateBase(StateType::STATE_LOAD_GAME), m_loadPercentage(0.0f), m_loadBar(nullptr), m_loadBackGround(nullptr),m_time(0.0f), m_wait(false)
{
}

GSLoadGame::~GSLoadGame()
{
}

void GSLoadGame::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("UI/bg_2.tga");

	// background
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(Globals::screenWidth / 2.f, Globals::screenHeight / 2.f);
	m_background->SetISize(Globals::screenWidth, Globals::screenHeight);
	// load bar background
	texture=ResourceManagers::GetInstance()->GetTexture("UI/bar_bg.tga");
	m_loadBackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_loadBackGround->Set2DPosition(Globals::screenWidth / 2.f, Globals::screenHeight / 2.f);
	m_loadBackGround->SetISize(LOAD_BACKGROUND_WIDTH, LOAD_BACKGROUND_HEIGHT);
	// load bar
	texture = ResourceManagers::GetInstance()->GetTexture("UI/bar_1.tga");
	m_loadBar = std::make_shared<Sprite2D>(model, shader, texture);
	m_loadBar->Set2DPosition(Globals::screenWidth / 2.f, Globals::screenHeight / 2.f);
	m_loadBar->SetISize(0, 0);

	Timer::GetInstance()->AddTimeOperation("LoadGame");
	MainCharacter::GetInstance()->Init();
	DefensivePoolManager::GetInstance()->Init();
	EnemyPoolManager::GetInstance()->Init();
	ResourceTable::GetInstance()->Init();
	ResourceTable::GetInstance()->UpdateMiddle();
	HUD::GetInstance()->Init();
	SetLoadPercentage(0.1f);
	Timer::GetInstance()->EndOperation("LoadGame");
	Timer::GetInstance()->EndAddTimeOperationPerCircle("LoadGame");
}

void GSLoadGame::Exit()
{
}


void GSLoadGame::Pause()
{
}

void GSLoadGame::Resume()
{
}


void GSLoadGame::HandleEvents()
{
}

void GSLoadGame::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSLoadGame::HandleTouchEvents(int x, int y, bool bIsPressed)
{

}

void GSLoadGame::HandleMouseMoveEvents(int x, int y)
{
}

void GSLoadGame::Update(float deltaTime)
{
	m_time += deltaTime;
	if (m_wait) {
		m_time = 0;
	}
	if (m_loadPercentage == 0.1f)
	{
		m_wait = false;
		if (m_time > 0.05) {
			Timer::GetInstance()->AddTimeOperation("LoadGame");
			ObstacleManager::GetInstance()->Init25();
			SetLoadPercentage(0.15f);
			m_wait = true;
		}
	}
	else if (m_loadPercentage == 0.15f)
	{
		m_wait = false;
		if (m_time > 0.05) {
			ObstacleManager::GetInstance()->Init50();
			SetLoadPercentage(0.2f);
			m_wait = true;
		}
	}
	else if (m_loadPercentage == 0.2f)
	{
		m_wait = false;
		if (m_time > 0.05) {
			ObstacleManager::GetInstance()->Init100();
			SetLoadPercentage(0.25f);
			m_wait = true;
		}
	}
	else if (m_loadPercentage == 0.25f)
	{
		m_wait = false;
		if (m_time > 0.05) {
			FloydWarshall::GetInstance()->Init25();
			SetLoadPercentage(0.35f);
			m_wait = true;
		}
	}
	else if (m_loadPercentage == 0.35f)
	{
		m_wait = false;
		if (m_time > 0.05) {
			FloydWarshall::GetInstance()->floydWarshall25();
			SetLoadPercentage(0.5f);
			m_wait = true;
		}
	}
	else if (m_loadPercentage == 0.5f)
	{
		m_wait = false;
		if (m_time > 0.05) {
			FloydWarshall::GetInstance()->Init50();
			SetLoadPercentage(0.6f);
			m_wait = true;
		}
	}
	else if (m_loadPercentage == 0.6f)
	{
		m_wait = false;
		if (m_time > 0.05) {
			FloydWarshall::GetInstance()->floydWarshall50();
			SetLoadPercentage(0.75f);
			m_wait = true;

		}
	}
	else if (m_loadPercentage == 0.75f)
	{
		m_wait = false;
		if (m_time > 0.05) {
			FloydWarshall::GetInstance()->Init100();
			SetLoadPercentage(0.85f);
			m_wait = true;

		}
	}
	else if (m_loadPercentage == 0.85f)
	{
		m_wait = false;
		if (m_time > 0.05) {
			FloydWarshall::GetInstance()->floydWarshall100();
			SetLoadPercentage(1.f);
			m_wait = true;

		}
	}
	else if (m_loadPercentage == 1.f)
	{
		m_wait = false;
		if (m_time > 0.05) {
			Timer::GetInstance()->EndOperation("LoadGame");
			Timer::GetInstance()->EndAddTimeOperationPerCircle("LoadGame");
			GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		}
	}
}

void GSLoadGame::Draw()
{
	m_background->Draw();
	m_loadBackGround->Draw();
	m_loadBar->Draw();
	ResourceTable::GetInstance()->DrawMiddle();
}

