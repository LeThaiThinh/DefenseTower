#include "TowerTwo.h"
#include "DefensiveManager.h"
#include <EnemyManager.h>
#include "Coin.h"
#define TowerOneCost 70

TowerTwo::TowerTwo() :UnMoveThroughAbleTower() {}

TowerTwo::TowerTwo(float x, float y) : UnMoveThroughAbleTower(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"),
	ResourceManagers::GetInstance()->GetShader("TextureShader"),
	ResourceManagers::GetInstance()->GetTexture("TowerTwolvl1.tga"),
	x, y, 60, 60, 60, 60, 500, 1, 100, 1000, 1, TowerType::Two, 3)
{
	LocateOption();
}

void TowerTwo::Attack()
{
}

void TowerTwo::Reset()
{
	UnMoveThroughAbleTower::Reset();
	Upgrade();
}

void TowerTwo::LocateOption()
{
	EnemyPoolManager::ResetFindPath();
	m_towerOption = std::make_shared<TowerOption>();
	auto mainOption = std::make_shared<GameButton>(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"),
		ResourceManagers::GetInstance()->GetShader("TextureShader"),
		ResourceManagers::GetInstance()->GetTexture("AncientTree1.tga"));
	mainOption->Set2DPosition(m_position.x, m_position.y);
	mainOption->SetISize(m_iWidth / 2, m_iHeight / 2);
	mainOption->SetOnClick([]() {});
	m_towerOption->SetMainOption(mainOption);

	std::shared_ptr<GameButton> secondButton1 = std::make_shared<GameButton>(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"),
		ResourceManagers::GetInstance()->GetShader("TextureShader"),
		ResourceManagers::GetInstance()->GetTexture("AncientTree1.tga"));
	secondButton1->Set2DPosition(m_position.x - m_iWidth / 2, m_position.y - m_iHeight / 2);
	secondButton1->SetISize(m_iWidth / 3, m_iHeight / 3);
	secondButton1->SetOnClickTower([](std::shared_ptr<BaseDefensive> tower) {
		Coin::GetInstance()->Refund(tower->GetTotalCost() * 0.4);
		DefensivePoolManager::GetInstance()->RemoveUnmove(tower);
		DefensivePoolManager::GetInstance()->Add(tower->GetPosition().x, tower->GetPosition().y, TowerType::Spot);
		EnemyPoolManager::ResetFindPath();
		});
	m_towerOption->AddSecondOption(secondButton1);

	std::shared_ptr<GameButton> secondButton2 = std::make_shared<GameButton>(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"),
		ResourceManagers::GetInstance()->GetShader("TextureShader"),
		ResourceManagers::GetInstance()->GetTexture("AncientTree1.tga"));
	secondButton2->Set2DPosition(m_position.x + m_iWidth / 2, m_position.y - m_iHeight / 2);
	secondButton2->SetISize(m_iWidth / 3, m_iHeight / 3);
	secondButton2->SetOnClickTower([](std::shared_ptr<BaseDefensive> tower) {
		if (Coin::GetInstance()->Purchase(tower->GetNextCost()));
		tower->Upgrade();
		});
	m_towerOption->AddSecondOption(secondButton2);
}

void TowerTwo::Update(GLfloat deltatime)
{
	UnMoveThroughAbleTower::Update(deltatime);
}

void TowerTwo::Upgrade()
{
	UnMoveThroughAbleTower::Upgrade();
	switch (m_level)
	{
	case 1:
		SetTexture(ResourceManagers::GetInstance()->GetTexture("TowerTwolvl1.tga"));
		SetISize(60, 60);
		SetSize(60, 60);
		m_range = 200;
		m_attackSpeed = 1;
		m_currentTimeAttack = 1;
		m_hitpoint = 500.f;
		m_maxHitPoint = 500.f;
		break;
	case 2:
		SetTexture(ResourceManagers::GetInstance()->GetTexture("TowerTwolvl2.tga"));
		SetISize(80, 80);
		SetSize(80, 80);
		m_range = 200;
		m_attackSpeed = 1;
		m_currentTimeAttack = 1;
		m_hitpoint = 500.f;
		m_maxHitPoint = 500.f;
		break;
	case 3:
		SetTexture(ResourceManagers::GetInstance()->GetTexture("TowerTwolvl3.tga"));
		SetISize(100, 100);
		SetSize(100, 100);
		m_range = 200;
		m_attackSpeed = 1;
		m_currentTimeAttack = 1;
		m_hitpoint = 500.f;
		m_maxHitPoint = 500.f;
		break;
	default:
		break;
	}

}
