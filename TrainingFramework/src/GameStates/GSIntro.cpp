#include "GSIntro.h"

GSIntro::GSIntro() : GameStateBase(StateType::STATE_INTRO), m_time(0.0f)
{
}


GSIntro::~GSIntro()
{
}


void GSIntro::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("logo.tga");

	m_logo = std::make_shared<Sprite2D>(model, shader, texture);
	m_logo->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_logo->SetSize(150, 150);
	ResourceManagers::GetInstance()->AddShader("AnimationShader");
	ResourceManagers::GetInstance()->AddTexture("explosion.tga");
	ResourceManagers::GetInstance()->AddTexture("Bomb2.tga");
	ResourceManagers::GetInstance()->AddTexture("bg_play1.tga");
	ResourceManagers::GetInstance()->AddTexture("HellBackground.tga");
	ResourceManagers::GetInstance()->AddTexture("SnowBackground.tga");
	ResourceManagers::GetInstance()->AddTexture("AbandonedForestBackground.tga");
	ResourceManagers::GetInstance()->AddTexture("UndeadBackground.tga");

	/*ResourceManagers::GetInstance()->AddTexture();
	ResourceManagers::GetInstance()->AddTexture();
	ResourceManagers::GetInstance()->AddTexture();*/

}

void GSIntro::Exit()
{
}


void GSIntro::Pause()
{
}

void GSIntro::Resume()
{
}


void GSIntro::HandleEvents()
{
}

void GSIntro::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSIntro::HandleTouchEvents(int x, int y, bool bIsPressed)
{
}

void GSIntro::HandleMouseMoveEvents(int x, int y)
{
}

void GSIntro::Update(float deltaTime)
{
	m_time += deltaTime;
	if (m_time > 1.5)
	{
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		m_time = 0;
	}
}

void GSIntro::Draw()
{
	m_logo->Draw();
}
