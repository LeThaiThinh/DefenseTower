#include "TowerOption.h"


TowerOption::TowerOption(TowerType type, std::shared_ptr<BaseTower> tower)
{
	m_mainOption = std::make_shared<GameButton>(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"),
		ResourceManagers::GetInstance()->GetShader("TextureShader"),
		ResourceManagers::GetInstance()->GetTexture("AncientTree1.tga"));
	m_mainOption->Set2DPosition(tower->GetPosition().x, tower->GetPosition().y);
	m_mainOption->SetSize(tower->GetWidtd(), tower->GetHeight());
	std::shared_ptr<GameButton> secondButton= std::make_shared<GameButton>(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"),
		ResourceManagers::GetInstance()->GetShader("TextureShader"),
		ResourceManagers::GetInstance()->GetTexture("AncientTree1.tga"));
	secondButton->Set2DPosition(tower->GetPosition().x, tower->GetPosition().y - tower->GetWidtd());
	secondButton->SetSize(tower->GetWidtd()/3, tower->GetHeight()/3);
}

void TowerOption::Update(float deltaTime)
{
	if (m_mainOption->IsHandled() && m_mainOption->IsHolding()) {
		m_secondOptionVisible = !m_secondOptionVisible;
	}
}

void TowerOption::Draw()
{
	m_mainOption->Draw();
	if (m_secondOptionVisible)
		for (auto m_secondOption : m_secondOptionList) {
			m_secondOption->Draw();
		}
}
void TowerOption::HandleTouchEvents(GLint x, GLint y, bool bIsPressed) {
	m_mainOption->HandleTouchEvents(x, y, bIsPressed);
	if (m_secondOptionVisible)
		for (auto m_secondOption : m_secondOptionList) {
			m_secondOption->HandleTouchEvents(x, y, bIsPressed);
		}
}


