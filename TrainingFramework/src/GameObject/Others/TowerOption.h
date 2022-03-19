#pragma once
#include "GameButton.h"
#define AdjustTowerOption 2

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
	void SetMainOptionPosition(float x,float y) { m_mainOption->Set2DPosition(x,y); }
	void SetMainOptionSize(int width,int height) { m_mainOption->SetISize(width,height); }

	void AddSecondOption(std::shared_ptr<GameButton> option) { m_secondOptionList.push_back(option); }
	void SetSecondOptionVisible(bool visible) { m_secondOptionVisible = visible; }
	void Update(float deltaTime);
	void Draw();
	bool HandleTouchEvents(GLint x, GLint y, bool bIsPressed, std::shared_ptr<BaseDefensive> tower);

private:
	std::shared_ptr<GameButton> m_mainOption;
	std::list<std::shared_ptr<GameButton>> m_secondOptionList;
	bool m_secondOptionVisible;
};
