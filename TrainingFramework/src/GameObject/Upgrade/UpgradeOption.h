#pragma once
#include "Others/GameButton.h"
#include <Base/Text.h>
#define UpgradeButtonSize 200
class UpgradeOption
{
public:
	UpgradeOption();
	UpgradeOption(float x, float y, std::shared_ptr<Texture> texture, std::string name);
	~UpgradeOption(){};
	bool HandleMouseMoveEvents(int x, int y);
	bool HandleTouchEvents(int x, int y, bool bIsPressed);
	void Draw();
	void DrawDes();
	void Update();

	int GetLevel() {
		return m_level;
	}
	void SetLevel(int level) {
		m_level = level;
		m_textLevel->SetText("level " +std::to_string(m_level));
	}
	void SetTextListAndCostList(std::vector<std::string> textList, std::vector<int> costList) {
		m_textList = textList;
		m_costList = costList;
	}
private:
	std::shared_ptr<GameButton> m_button;
	std::shared_ptr<Text> m_textLevel;
	std::shared_ptr<Sprite2D> m_containTextLevel;
	std::shared_ptr<Sprite2D> m_diamondCost;
	int m_level;
	std::vector<std::string> m_textList;
	std::vector<int> m_costList;
	std::shared_ptr<Text> m_textDesCurrent;
	std::shared_ptr<Text> m_textDesNext;
	std::shared_ptr<Text> m_textDesName;
	std::shared_ptr<Text> m_textDesCost;
	std::string m_name;
};

