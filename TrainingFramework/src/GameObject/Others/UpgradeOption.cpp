#include "UpgradeOption.h"
#include "Resource/Diamond.h"
#include "CheckCollision.h"
#include "DescriptionUpgradeTable.h"
UpgradeOption::UpgradeOption()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("UI/button_close.tga");
	m_button=std::make_shared<GameButton>(model, shader, texture);
	m_button->SetISize(UpgradeButtonSize, UpgradeButtonSize);
	m_level = 0;
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Triangle.ttf");
	m_textDesCurrent= std::make_shared< Text>(shader, font, "", Vector4(1.f, 0.6f, 0.f, 1.0f), 2.0f);
	m_textDesNext= std::make_shared< Text>(shader, font, "", Vector4(1.f, 0.6f, 0.f, 1.0f), 2.0f);
	m_textLevel = std::make_shared< Text>(shader, font, "", Vector4(1.f, 0.6f, 0.f, 1.0f), 2.0f);
}

UpgradeOption::UpgradeOption(float x, float y,std::shared_ptr<Texture> texture, std::string name)
{
	m_name = name;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_button = std::make_shared<GameButton>(model, shader, texture);
	m_button->Set2DPosition(x, y);
	m_button->SetISize(UpgradeButtonSize, UpgradeButtonSize);
	m_button->SetOnClick([]{});
	m_level = 0;
	texture= ResourceManagers::GetInstance()->GetTexture("UI/btton_empty.tga");
	m_containTextLevel= std::make_shared<Sprite2D>(model, shader, texture);
	m_containTextLevel->Set2DPosition(x , y - UpgradeButtonSize / 2 - 10);
	m_containTextLevel->SetISize(100,30);
	texture= ResourceManagers::GetInstance()->GetTexture("UI/crystal.tga");
	m_diamondCost = std::make_shared<Sprite2D>(model, shader, texture);
	m_diamondCost->Set2DPosition(Globals::screenWidth / 2.f, DesTableY - DesTableHeight / 2 + 15);
	m_diamondCost->SetISize(30, 30);
	//text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Triangle.ttf");
	m_textDesCurrent = std::make_shared< Text>(shader, font, "", Vector4(1.f, 0.6f, 0.f, 1.0f), 1.0f);
	m_textDesCurrent->Set2DPosition(Globals::screenWidth / 2.f - DesTableWidth , DesTableY + 5);
	m_textDesNext = std::make_shared< Text>(shader, font, "", Vector4(1.f, 0.6f, 0.f, 1.0f), 1.0f);
	m_textDesNext->Set2DPosition(Globals::screenWidth / 2.f  , DesTableY + 5);
	m_textDesName = std::make_shared< Text>(shader, font, "", Vector4(1.f, 0.6f, 0.f, 1.0f), 1.0f);
	m_textDesName->Set2DPosition(Globals::screenWidth / 2.f, DesTableY - DesTableHeight / 2 - 10 );
	m_textDesCost = std::make_shared< Text>(shader, font, "", Vector4(1.f, 0.6f, 0.f, 1.0f), 1.0f);
	m_textDesCost->Set2DPosition(Globals::screenWidth / 2.f - 5, DesTableY - DesTableHeight / 2 + 20);
	m_textLevel = std::make_shared< Text>(shader, font, "level 0", Vector4(1.f, 0.6f, 0.f, 1.0f), 1.0f);
	m_textLevel->Set2DPosition(x-30, y - UpgradeButtonSize  / 2 - 3);

}

bool UpgradeOption::HandleMouseMoveEvents(int x, int y)
{
	if (CheckCollision::PointInRectI(Vector3(x,y,0), m_button)) {
		m_textDesCurrent->SetText(m_textList[m_level]);
		if (m_level < m_textList.size() - 1)
			m_textDesNext->SetText(m_textList[m_level + 1]);
		else
			m_textDesNext->SetText("Max Level");
		m_textDesName->SetText(m_name);
		m_textDesName->Set2DPosition(Globals::screenWidth / 2 - m_textDesName->GetText().length() * 5, DesTableY - DesTableHeight / 2 - 10);
		m_textDesCost->SetText(std::to_string(m_costList[m_level]));
		m_textDesCost->Set2DPosition(Globals::screenWidth / 2 - m_textDesCost->GetText().length() * 5 - 5, DesTableY - DesTableHeight / 2 + 20);
		m_diamondCost->Set2DPosition(Globals::screenWidth / 2 + 20, DesTableY - DesTableHeight / 2 + 15);
		m_textDesNext->Set2DPosition(Globals::screenWidth / 2 + DesTableWidth / 2 - m_textDesNext->GetText().length() * 5, DesTableY + 5);
		m_textDesCurrent->Set2DPosition(Globals::screenWidth / 2 - DesTableWidth / 2 - m_textDesCurrent->GetText().length() * 5, DesTableY + 5);

		return true;
	}
}

bool UpgradeOption::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	if (m_button->HandleTouchEvents(x, y, bIsPressed)) {
		if (m_level < m_textList.size()-1) {
			if (Diamond::GetInstance()->Purchase(m_costList[m_level])) {
				m_level++;
				m_textLevel->SetText("level "+std::to_string(m_level));
				m_textDesCurrent->SetText(m_textList[m_level]);
				if (m_level < m_textList.size() - 1)
					m_textDesNext->SetText(m_textList[m_level + 1]);
				else
					m_textDesNext->SetText("Max Level");
				m_textDesName->SetText(m_name);
				m_textDesName->Set2DPosition(Globals::screenWidth / 2 - m_textDesName->GetText().length() * 5, DesTableY - DesTableHeight / 2 - 10);
				m_textDesCost->SetText(std::to_string(m_costList[m_level]));
				m_textDesCost->Set2DPosition(Globals::screenWidth / 2 - m_textDesCost->GetText().length() * 5 - 5, DesTableY - DesTableHeight / 2 + 20);
				m_diamondCost->Set2DPosition(Globals::screenWidth / 2 + 20, DesTableY - DesTableHeight / 2 + 15);
				m_textDesNext->Set2DPosition(Globals::screenWidth / 2 + DesTableWidth / 2 - m_textDesNext->GetText().length() * 5, DesTableY + 5);
				m_textDesCurrent->Set2DPosition(Globals::screenWidth / 2 - DesTableWidth / 2 - m_textDesCurrent->GetText().length() * 5, DesTableY + 5);
			}
		}
		return true;
	}
}

void UpgradeOption::Draw()
{
	m_button->Draw();
	m_containTextLevel->Draw();
	m_textLevel->Draw();
}
void UpgradeOption::DrawDes()
{
	m_button->Draw();
	m_containTextLevel->Draw();
	m_textLevel->Draw();
	m_textDesCurrent->Draw();
	m_textDesNext->Draw();
	m_textDesName->Draw();
	m_textDesCost->Draw();
	m_diamondCost->Draw();
}
void UpgradeOption::Update()
{
}
