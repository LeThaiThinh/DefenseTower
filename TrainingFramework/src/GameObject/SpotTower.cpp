#include "SpotTower.h"
#include <TowerOption.h>
#include "DefensiveManager.h"
#include "Coin.h"
#define TowerOneCost 60
#define TowerTwoCost 70
SpotTower::SpotTower() :BaseDefensive()
{}

SpotTower::SpotTower(float x, float y) : BaseDefensive(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"),
	ResourceManagers::GetInstance()->GetShader("TextureShader"),
	ResourceManagers::GetInstance()->GetTexture("Tower/spot_tower.tga"),
	x, y, 80, 60, 80, 60, 500.f, 1 / INFINITY, 0,0,Vector3(0,0,0),nullptr,nullptr, 0, TowerType::Spot, 0)
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
	m_towerOption->SetMainOptionPosition(m_position.x, m_position.y);
	m_towerOption->SetMainOptionSize(m_iWidth , m_iHeight );
	std::shared_ptr<GameButton> secondButton = std::make_shared<GameButton>(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"),
		ResourceManagers::GetInstance()->GetShader("TextureShader"),
		ResourceManagers::GetInstance()->GetTexture("Tower/upgrade_tower_one.tga"));
	secondButton->Set2DPosition(m_position.x - m_iWidth / 2.f - AdjustTowerOption, m_position.y - m_iHeight / 2.f - AdjustTowerOption);
	secondButton->SetISize(m_iWidth / 2, m_iHeight / 2);
	secondButton->SetOnClickTower([](std::shared_ptr<BaseDefensive> tower) {
		if (Coin::GetInstance()->Purchase(TowerOneCost)) {
			DefensivePoolManager::GetInstance()->RemoveSpot(tower);
			DefensivePoolManager::GetInstance()->Add(tower->GetPosition().x, tower->GetPosition().y, TowerType::One);
		}
		});
	m_towerOption->AddSecondOption(secondButton);
	std::shared_ptr<GameButton> secondButton2 = std::make_shared<GameButton>(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"),
		ResourceManagers::GetInstance()->GetShader("TextureShader"),
		ResourceManagers::GetInstance()->GetTexture("Tower/upgrade_tower_two.tga"));
	secondButton2->Set2DPosition(m_position.x + m_iWidth / 2.f + AdjustTowerOption, m_position.y - m_iHeight / 2.f - AdjustTowerOption);
	secondButton2->SetISize(m_iWidth / 2, m_iHeight / 2);
	secondButton2->SetOnClickTower([](std::shared_ptr<BaseDefensive> tower) {
		if (Coin::GetInstance()->Purchase(TowerTwoCost)) {
			DefensivePoolManager::GetInstance()->RemoveSpot(tower);
			DefensivePoolManager::GetInstance()->Add(tower->GetPosition().x, tower->GetPosition().y, TowerType::Two);
		}
		});
	m_towerOption->AddSecondOption(secondButton2);
}