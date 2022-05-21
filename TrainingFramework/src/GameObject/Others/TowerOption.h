#pragma once
#include "GameButton.h"
#include "Base/Text.h"
#define AdjustTowerOption 1.5

class GameButton;
class BaseDefensive;
class TowerOption
{
public:
	TowerOption();
	~TowerOption() {}
	std::shared_ptr<GameButton> GetListOption() { return m_mainOption; }
	std::list<std::shared_ptr<GameButton>> GetSeconlistOption() { return m_secondOptionList; };

	void SetMainOption(std::shared_ptr<GameButton> option) { m_mainOption = option; }
	void SetMainOptionPosition(float x,float y) { m_mainOption->Set3DPosition(x,y,1); }
	void SetMainOptionSize(int width,int height) { m_mainOption->SetISize(width,height); }

	void AddSecondOption(std::shared_ptr<GameButton> option) { m_secondOptionList.push_back(option); }
	void SetSecondOptionVisible(bool visible) { m_secondOptionVisible = visible; }

	void AddCostText(std::shared_ptr<Text> text) { m_costTextList.push_back(text); }
	std::list<std::shared_ptr<Text>> GetCostTextList() { return m_costTextList; }

	void Update(float deltaTime);
	void Draw();
	bool HandleTouchEvents(GLint x, GLint y, bool bIsPressed, std::shared_ptr<BaseDefensive> tower);

private:
	std::shared_ptr<GameButton> m_mainOption;
	std::list<std::shared_ptr<GameButton>> m_secondOptionList;
	std::list<std::shared_ptr<Text>> m_costTextList;
	bool m_secondOptionVisible;
};
