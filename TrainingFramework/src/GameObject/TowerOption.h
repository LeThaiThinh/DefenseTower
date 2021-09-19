#pragma once
#include "GameButton.h"
#include "../../BaseTower.h"
class TowerOption
{
public:
	TowerOption(){}
	TowerOption(TowerType type,std::shared_ptr<BaseTower>tower);
	~TowerOption(){}
	std::shared_ptr<GameButton> GetListOption() { return m_mainOption; }
	std::list<std::shared_ptr<GameButton>> GetSeconlistOption() { return m_secondOptionList; };
	void SetListOption(std::shared_ptr<GameButton> option) { m_mainOption = option; }
	void AddSecondOption(std::shared_ptr<GameButton> option) { m_secondOptionList .push_back(option); }
	void Update(float deltaTime);
	void Draw();
	void HandleTouchEvents(GLint x, GLint y, bool bIsPressed);
private:
	std::shared_ptr<GameButton> m_mainOption;
	std::list<std::shared_ptr<GameButton>> m_secondOptionList;
	bool m_secondOptionVisible;
};
