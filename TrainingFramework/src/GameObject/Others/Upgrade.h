#pragma once
#include "DescriptionUpgradeTable.h"
class Upgrade:public CSingleton<Upgrade>
{
public:
	Upgrade() {
		isShowDes = false;
		desTable = std::make_shared<DescriptionUpgradeTable>();
		std::vector<std::string> textList;
		std::vector<int> costList;
		std::shared_ptr<UpgradeOption> upgrade = std::make_shared<UpgradeOption>(Globals::screenWidth/3.f, Globals::screenHeight/3.f,ResourceManagers::GetInstance()->GetTexture("UI/attack_upgrade_icon.tga"), "Upgrade Attack");
		textList.push_back("Witch cast 1 projectile");
		textList.push_back("Witch cast 2 projectile");
		textList.push_back("Witch cast 3 projectile");
		costList.push_back(10);
		costList.push_back(15);
		costList.push_back(20);
		upgrade->SetTextListAndCostList(textList, costList);
		textList.clear();
		costList.clear();
		upgradeList.insert(std::pair<std::string, std::shared_ptr<UpgradeOption>>("Upgrade Attack", upgrade));
		upgrade = std::make_shared<UpgradeOption>(Globals::screenWidth *2 / 3.f, Globals::screenHeight / 3.f, ResourceManagers::GetInstance()->GetTexture("UI/health_upgrade_icon.tga"), "Upgrade Health");
		textList.push_back("All tower increase 0 hitpoint");
		textList.push_back("All tower increase 200 hitpoint");
		textList.push_back("All tower increase 400 hitpoint");
		costList.push_back(10);
		costList.push_back(15);
		costList.push_back(20);
		upgrade->SetTextListAndCostList(textList, costList);
		textList.clear();
		costList.clear();
		upgradeList.insert(std::pair<std::string, std::shared_ptr<UpgradeOption>>("Upgrade Health", upgrade));
		upgrade = std::make_shared<UpgradeOption>(Globals::screenWidth / 3.f, Globals::screenHeight *2 / 3.f-50, ResourceManagers::GetInstance()->GetTexture("UI/regen_upgrade_icon.tga"), "Upgrade Regen");
		textList.push_back("All tower's regeneration increased 0");
		textList.push_back("All tower's regeneration increased 5");
		textList.push_back("All tower's regeneration increased 10");
		costList.push_back(10);
		costList.push_back(15);
		costList.push_back(20);
		upgrade->SetTextListAndCostList(textList, costList);
		textList.clear();
		costList.clear();
		upgradeList.insert(std::pair<std::string, std::shared_ptr<UpgradeOption>>("Upgrade Regen", upgrade));
		upgrade = std::make_shared<UpgradeOption>(Globals::screenWidth *2 / 3.f, Globals::screenHeight*2 / 3.f-50, ResourceManagers::GetInstance()->GetTexture("UI/resource_upgrade_icon.tga"), "Upgrade Resource");
		textList.push_back("Kill Enemy gain more 0 coin");
		textList.push_back("Kill Enemy gain more 1 coin");
		textList.push_back("Kill Enemy gain more 2 coin");
		costList.push_back(10);
		costList.push_back(15);
		costList.push_back(20);
		upgrade->SetTextListAndCostList(textList, costList);
		textList.clear();
		costList.clear();
		upgradeList.insert(std::pair<std::string, std::shared_ptr<UpgradeOption>>("Upgrade Resource", upgrade));
	};
	~Upgrade(){};

	bool HandleMouseMoveEvents(int x, int y) {
		for (auto& upgrade : upgradeList) {
			if (upgrade.second->HandleMouseMoveEvents(x, y)) {
				currentShowDes = upgrade.second;
				isShowDes = true;
				return true;
			}
		}
		return false;
	}
	bool HandleTouchEvents(int x, int y, bool bIsPressed) {
		for (auto& upgrade : upgradeList) {
			if (upgrade.second->HandleTouchEvents(x, y, bIsPressed)) {
				return true;
			}
		}
		return false;
	}
	void Draw() {
		if (isShowDes) {
			desTable->Draw(currentShowDes);
		}
		else {
			desTable->Draw();
		}
		for (auto& upgrade : upgradeList) {
			upgrade.second->Draw();
		}
	}

	std::map<std::string,std::shared_ptr<UpgradeOption>> upgradeList;
	std::shared_ptr<DescriptionUpgradeTable> desTable;
	std::shared_ptr<UpgradeOption> currentShowDes;
	bool isShowDes;
};
