#include "SpotTower.h"
#include <TowerOption.h>
#include "DefensiveManager.h"
#include <GameStates/GSPlay.h>
#include "Coin.h"
#define TowerOneCost 60
#define TowerTwoCost 70

SpotTower::SpotTower() :BaseDefensive()
{}

SpotTower::SpotTower(float x, float y) : BaseDefensive(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"),
	ResourceManagers::GetInstance()->GetShader("TextureShader"),
	ResourceManagers::GetInstance()->GetTexture("SpotTower.tga"),
	x, y, 80, 60, 80, 60, 500.f, 1 / INFINITY, 0, 0, TowerType::Spot, 0, 1, 1)
{
	LocateOption();
}

SpotTower::~SpotTower()
{
	m_towerOption = nullptr;
}


void SpotTower::Reset()
{
	BaseDefensive::Reset();
}



void SpotTower::Update(GLfloat deltatime)
{
	BaseDefensive::Update(deltatime);
}

void SpotTower::LocateOption()
{
	m_towerOption = std::make_shared<TowerOption>();
	auto mainOption = std::make_shared<GameButton>(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"),
		ResourceManagers::GetInstance()->GetShader("TextureShader"),
		ResourceManagers::GetInstance()->GetTexture("AncientTree1.tga"));
	mainOption->Set2DPosition(m_position.x, m_position.y);
	mainOption->SetISize(m_iWidth / 2, m_iHeight / 2);
	mainOption->SetOnClick([]() {});
	m_towerOption->SetMainOption(mainOption);
	std::shared_ptr<GameButton> secondButton = std::make_shared<GameButton>(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"),
		ResourceManagers::GetInstance()->GetShader("TextureShader"),
		ResourceManagers::GetInstance()->GetTexture("TowerOnelvl1.tga"));
	secondButton->Set2DPosition(m_position.x - m_iWidth / 2, m_position.y - m_iHeight / 2);
	secondButton->SetISize(m_iWidth / 3, m_iHeight / 3);
	secondButton->SetOnClickTower([](std::shared_ptr<BaseDefensive> tower) {
		if (Coin::GetInstance()->Purchase(TowerOneCost)) {
			DefensivePoolManager::GetInstance()->RemoveSpot(tower);
			DefensivePoolManager::GetInstance()->Add(tower->GetPosition().x, tower->GetPosition().y, TowerType::One);
		}
		});
	m_towerOption->AddSecondOption(secondButton);
	std::shared_ptr<GameButton> secondButton2 = std::make_shared<GameButton>(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"),
		ResourceManagers::GetInstance()->GetShader("TextureShader"),
		ResourceManagers::GetInstance()->GetTexture("TowerTwolvl1.tga"));
	secondButton2->Set2DPosition(m_position.x + m_iWidth / 2, m_position.y - m_iHeight / 2);
	secondButton2->SetISize(m_iWidth / 3, m_iHeight / 3);
	secondButton2->SetOnClickTower([](std::shared_ptr<BaseDefensive> tower) {
		if (Coin::GetInstance()->Purchase(TowerTwoCost)) {
			DefensivePoolManager::GetInstance()->RemoveSpot(tower);
			DefensivePoolManager::GetInstance()->Add(tower->GetPosition().x, tower->GetPosition().y, TowerType::Two);
		}
		});
	m_towerOption->AddSecondOption(secondButton2);
}