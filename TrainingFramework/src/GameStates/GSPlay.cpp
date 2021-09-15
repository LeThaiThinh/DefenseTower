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

BulletPool<Bullet>* BulletPool<Bullet>::instance = 0;

GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
}


void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play1.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// button clode
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50.f, 50.f);
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);
	//
	m_mainCharacter = std::make_shared<MainCharacter>();
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
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}

}

void GSPlay::HandleMouseMoveEvents(int x, int y)
{
	if (keyPressed & KEY_SPACE) {
		m_mainCharacter->ShootLinear(Vector2(x,y));
	}
}

void GSPlay::Update(float deltaTime)
{
	HandleKeyPress(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	m_mainCharacter->Update(deltaTime);
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