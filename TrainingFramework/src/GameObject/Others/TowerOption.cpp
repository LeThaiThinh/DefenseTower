#include "TowerOption.h"
#include "ResourceManagers.h"
#include "HUD/HUD.h"
#define BORDER_OPTION_TOWER 1.5f
TowerOption::TowerOption() :m_secondOptionVisible(false) {
	m_mainOption = std::make_shared<GameButton>(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"),
		ResourceManagers::GetInstance()->GetShader("TextureShader"),
		ResourceManagers::GetInstance()->GetTexture("UI/tower_upgrade.tga"));
	m_mainOption->SetOnClick([]() {});
}
void TowerOption::Update(float deltaTime)
{

}

void TowerOption::Draw()
{
	if (m_secondOptionVisible) {
		m_mainOption->Draw();
		for (auto &m_secondOption : m_secondOptionList) {
			m_secondOption->Draw();
		}
	}
}
bool TowerOption::HandleTouchEvents(GLint x, GLint y, bool bIsPressed, std::shared_ptr<BaseDefensive> tower)
{
	if (m_secondOptionVisible)
		for (auto &m_secondOption : m_secondOptionList) {
			if (m_secondOption->HandleTouchEventsTower(x, y, bIsPressed, tower)) {
				m_secondOptionVisible = !m_secondOptionVisible;
				m_mainOption->SetISize(m_mainOption->GetIWidth() / BORDER_OPTION_TOWER, m_mainOption->GetIHeight() / BORDER_OPTION_TOWER);
				return true;
			}
			else if (m_secondOption->IsHolding()) {
				return true;
			}
		}
	if (m_mainOption->HandleTouchEvents(x, y, bIsPressed)) {
		m_secondOptionVisible = !m_secondOptionVisible;
		if (m_secondOptionVisible)
			m_mainOption->SetISize(m_mainOption->GetIWidth() * BORDER_OPTION_TOWER, m_mainOption->GetIHeight() * BORDER_OPTION_TOWER);
		else
			m_mainOption->SetISize(m_mainOption->GetIWidth() / BORDER_OPTION_TOWER, m_mainOption->GetIHeight() / BORDER_OPTION_TOWER);
		return true;
	}
	else if (m_mainOption->IsHolding()) {
		return true;
	}
	return false;
}



