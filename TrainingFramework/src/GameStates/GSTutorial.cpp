#include "GSTutorial.h"
#include "Base/Sprite2D.h"

int GSTutorial::page = 0;
GSTutorial::GSTutorial() : GameStateBase(StateType::STATE_TUTORIAL)
{
}


GSTutorial::~GSTutorial()
{
}


void GSTutorial::Init()
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

	//button close
	texture = ResourceManagers::GetInstance()->GetTexture("UI/button_close_2.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth * 5 / 6.f - 25.f, Globals::screenHeight / 6.f + 25.f);
	button->SetISize(75, 75);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		page == 0;
		});
	m_listButton.push_back(button);
	//button left
	texture = ResourceManagers::GetInstance()->GetTexture("UI/yellow_arrow_left.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth * 1 / 6.f + 25.f, Globals::screenHeight / 2.f);
	button->SetISize(100, 100);
	button->SetOnClick([]() {
			page--;
			if (page < 0)
				page += MAXPAGE;
		});
	m_listButton.push_back(button);
	//button right
	texture = ResourceManagers::GetInstance()->GetTexture("UI/yellow_arrow.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth * 5 / 6.f - 25.f, Globals::screenHeight / 2.f);
	button->SetISize(100, 100);
	button->SetOnClick([]() {
			page++;
			if (page >= MAXPAGE)
				page -= MAXPAGE;
		});
	m_listButton.push_back(button);
	//image
	texture = ResourceManagers::GetInstance()->GetTexture("UI/tutorial_control_character.tga");
	auto image = std::make_shared<Sprite2D>(model, shader, texture);
	image->Set2DPosition(Globals::screenWidth  / 2.f, Globals::screenHeight / 2.f - 50);
	image->SetISize(400, 400);
	m_listImage.push_back(image);

	texture = ResourceManagers::GetInstance()->GetTexture("UI/tutorial_kill_and_earn.tga");
	image = std::make_shared<Sprite2D>(model, shader, texture);
	image->Set2DPosition(Globals::screenWidth / 2.f, Globals::screenHeight / 2.f - 50);
	image->SetISize(500, 300);
	m_listImage.push_back(image);

	texture = ResourceManagers::GetInstance()->GetTexture("UI/tutorial_buy_and_upgrade.tga");
	image = std::make_shared<Sprite2D>(model, shader, texture);
	image->Set2DPosition(Globals::screenWidth / 2.f, Globals::screenHeight / 2.f - 50);
	image->SetISize(200, 300);
	m_listImage.push_back(image);
	//text
	std::list<std::shared_ptr<Text>> texts;
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Triangle.ttf");
	std::shared_ptr<Text> text = std::make_shared< Text>(shader, font, "Control your Character:", Vector4(1.0f, 0.6f, 0.f, 1.0f), 2.5f);
	text->Set2DPosition(Vector2(Globals::screenWidth * 2 / 9+50 , Globals::screenHeight * 7.f / 10 + 25.f));
	texts.push_back(text);
	text = std::make_shared< Text>(shader, font, "W-A-S-D and left mouse", Vector4(1.0f, 0.6f, 0.f, 1.0f), 2.5f);
	text->Set2DPosition(Vector2(Globals::screenWidth * 2 / 9 + 50, Globals::screenHeight * 7.7f / 10 + 25.f));
	texts.push_back(text);
	m_listTexts.push_back(texts);

	texts.clear();
	text = std::make_shared< Text>(shader, font, "Killing enemy and get coin", Vector4(1.0f, 0.6f, 0.f, 1.0f), 2.5f);
	text->Set2DPosition(Vector2(Globals::screenWidth * 2 / 9+25, Globals::screenHeight * 7.f / 10 + 25.f));
	texts.push_back(text);
	m_listTexts.push_back(texts);

	texts.clear();
	text = std::make_shared< Text>(shader, font, "Use collected coin", Vector4(1.0f, 0.6f, 0.f, 1.0f), 2.5f);
	text->Set2DPosition(Vector2(Globals::screenWidth * 2 / 9 + 125, Globals::screenHeight * 7.f / 10 + 25.f));
	texts.push_back(text);
	text = std::make_shared< Text>(shader, font, "To buy or upgrade Tower", Vector4(1.0f, 0.6f, 0.f, 1.0f), 2.5f);
	text->Set2DPosition(Vector2(Globals::screenWidth * 2 / 9 + 50, Globals::screenHeight * 7.7f / 10 + 25.f));
	texts.push_back(text);
	m_listTexts.push_back(texts);


}

void GSTutorial::Exit()
{
}


void GSTutorial::Pause()
{
}

void GSTutorial::Resume()
{
}


void GSTutorial::HandleEvents()
{
}

void GSTutorial::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSTutorial::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto& button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSTutorial::HandleMouseMoveEvents(int x, int y)
{
}

void GSTutorial::Update(float deltaTime)
{
	for (auto& button : m_listButton)
	{
		button->Update(deltaTime);
	}
}

void GSTutorial::Draw()
{
	m_background->Draw();
	m_table->Draw();
	for (auto& button : m_listButton)
	{
		button->Draw();
	}
	m_listImage[page]->Draw();
	for (auto& text: m_listTexts[page]) {
		text->Draw();
	}
}
