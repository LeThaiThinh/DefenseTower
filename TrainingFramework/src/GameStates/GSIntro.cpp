#include "GSIntro.h"
#include "GameStateMachine.h"
#include <GameStates/Record.h>
#include "irrKlang.h"
#include "Upgrade/Upgrade.h"
#include "GSMenu.h"
GSIntro::GSIntro() : GameStateBase(StateType::STATE_INTRO), m_time(0.0f)
{
}


GSIntro::~GSIntro()
{
}


void GSIntro::Init()
{
	srand(time(0));
	Record::GetInstance()->ReadAll();
	if(GSMenu::sfx)
		ResourceManagers::GetInstance()->GetSound("intro.mp3")->PlaySoundFromStart2D(false);
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("UI/logo.tga");

	m_logo = std::make_shared<Sprite2D>(model, shader, texture);
	m_logo->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_logo->SetISize(300, 225);

	ResourceManagers::GetInstance()->AddFont("Brightly Crush Shine.otf");
	ResourceManagers::GetInstance()->AddFont("arialbd.ttf");
	ResourceManagers::GetInstance()->AddShader("TextShader");
	ResourceManagers::GetInstance()->AddShader("AnimationShader");
	//UI
	ResourceManagers::GetInstance()->AddTexture("UI/bg.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/bg_2.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/table.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/button_empty.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/btton_empty.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/button_close_2.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/button_settings.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/button_left.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/button_right.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/button_music.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/button_music_off.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/button_sound.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/button_sound_off.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/rope_big.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/num_0.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/num_1.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/num_2.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/num_3.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/num_4.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/num_5.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/num_6.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/num_7.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/num_8.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/num_9.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/bar_1.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/bar_2.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/bar_3.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/bar_4.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/bar_bg.tga");
	ResourceManagers::GetInstance()->AddTexture("UI/bg_bar.tga");

	//sound
	ResourceManagers::GetInstance()->AddSound("epic.mp3");
	ResourceManagers::GetInstance()->AddSound("maincharacter_attack.mp3");
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
	if (m_time > 5.5f)
	{
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		m_time = 0;
	}
}

void GSIntro::Draw()
{
	m_logo->Draw();
}
