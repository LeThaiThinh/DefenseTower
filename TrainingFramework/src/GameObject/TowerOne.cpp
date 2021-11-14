#include "TowerOne.h"
#include "DefensiveManager.h"
#include "BulletManager.h"
#include "../BaseEnemy.h"
#include <EnemyManager.h>
#include <GameStates/GSPlay.h>
#include "Coin.h"
#define TowerOneCost 60

TowerOne::TowerOne() :UnMoveThroughAbleTower() {}

TowerOne::TowerOne(float x, float y) : UnMoveThroughAbleTower(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"),
	ResourceManagers::GetInstance()->GetShader("TextureShader"),
	ResourceManagers::GetInstance()->GetTexture("TowerOnelvl1.tga"),
	x, y, 50, 60, 50, 60, 300, 1.5, 2, 300.0f, 0, TowerType::One, 3)
{
	Upgrade();
	LocateOption();
}

void TowerOne::Attack()
{
	UnMoveThroughAbleTower::Attack();
	BulletPoolManager::GetInstance()->AddBullet(
		BulletType::Target_TowerOne, std::dynamic_pointer_cast<BaseObject>(m_target),
		Vector3(0, 0, 0), shared_from_this());
}

void TowerOne::Reset()
{
	UnMoveThroughAbleTower::Reset();
	Upgrade();
}

void TowerOne::Upgrade()
{
	UnMoveThroughAbleTower::Upgrade();
	switch (m_level)
	{
	case 1:
		SetTexture(ResourceManagers::GetInstance()->GetTexture("TowerOnelvl1.tga"));
		SetISize(55, 66);
		SetSize(65, 66);
		m_totalCost = TowerOneCost;
		m_costUpgrade = 100;
		m_range = 300;
		m_attackSpeed = 1.5f;
		m_damage = 2.f;
		m_currentTimeAttack = 1 / m_attackSpeed;
		m_hitpoint = 300.f;
		m_maxHitPoint = 300.f;
		break;
	case 2:
		SetTexture(ResourceManagers::GetInstance()->GetTexture("TowerOnelvl2.tga"));
		SetISize(60, 72);
		SetSize(60, 72);
		m_totalCost += m_costUpgrade;
		m_costUpgrade = 140;
		m_range = 330.f;
		m_attackSpeed = 2.5f;
		m_damage = 2.5f;
		m_currentTimeAttack = 1 / m_attackSpeed;
		m_hitpoint = 400.f;
		m_maxHitPoint = 400.f;
		break;
	case 3:
		SetTexture(ResourceManagers::GetInstance()->GetTexture("TowerOnelvl3.tga"));
		SetISize(65, 78);
		SetSize(65, 78);
		m_totalCost += m_costUpgrade;
		m_costUpgrade = 0;
		m_range = 360.f;
		m_attackSpeed = 3.5f;
		m_damage = 3.f;
		m_currentTimeAttack = 1 / m_attackSpeed;
		m_hitpoint = 500.f;
		m_maxHitPoint = 500.f;
		break;
	default:
		break;
	}
}

void TowerOne::LocateOption()
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
	std::shared_ptr<GameButton> secondButton = std::make_shared<GameButton>(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"),
		ResourceManagers::GetInstance()->GetShader("TextureShader"),
		ResourceManagers::GetInstance()->GetTexture("AncientTree1.tga"));
	secondButton->Set2DPosition(m_position.x - m_iWidth / 2, m_position.y - m_iHeight / 2);
	secondButton->SetISize(m_iWidth / 3, m_iHeight / 3);
	secondButton->SetOnClickTower([](std::shared_ptr<BaseDefensive> tower) {
		Coin::GetInstance()->Refund(tower->GetTotalCost() * 0.5);
		DefensivePoolManager::GetInstance()->RemoveUnmove(tower);
		DefensivePoolManager::GetInstance()->Add(tower->GetPosition().x, tower->GetPosition().y, TowerType::Spot);
		EnemyPoolManager::ResetFindPath();
		});
	m_towerOption->AddSecondOption(secondButton);
	std::shared_ptr<GameButton> secondButton2 = std::make_shared<GameButton>(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"),
		ResourceManagers::GetInstance()->GetShader("TextureShader"),
		ResourceManagers::GetInstance()->GetTexture("AncientTree1.tga"));
	secondButton2->Set2DPosition(m_position.x + m_iWidth / 2, m_position.y - m_iHeight / 2);
	secondButton2->SetISize(m_iWidth / 3, m_iHeight / 3);
	secondButton2->SetOnClickTower([](std::shared_ptr<BaseDefensive> tower) {
		if (Coin::GetInstance()->Purchase(tower->GetNextCost()))
			tower->Upgrade();
		});
	m_towerOption->AddSecondOption(secondButton2);
}

void TowerOne::Update(GLfloat deltatime)
{
	UnMoveThroughAbleTower::Update(deltatime);
}
