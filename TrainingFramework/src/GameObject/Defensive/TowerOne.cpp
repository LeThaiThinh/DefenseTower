#include "TowerOne.h"
#include "DefensiveManager.h"
#include "Bullet/BulletManager.h"
#include <Enemy/EnemyManager.h>
#include "Resource/Coin.h"
#define TowerOneCost 60

TowerOne::TowerOne() :UnMoveThroughAbleTower() {}

TowerOne::TowerOne(float x, float y) : UnMoveThroughAbleTower(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"),
	ResourceManagers::GetInstance()->GetShader("TextureShader"),
	ResourceManagers::GetInstance()->GetTexture("TowerOnelvl1.tga"),
	x, y, 80, 60, 80, 60, 300, 1.5, 2,0,Vector3(0,0,0),nullptr,nullptr, 300.0f, 0, TowerType::One, 3)
{
	Upgrade();
	LocateOption();
}

void TowerOne::Attack()
{
	UnMoveThroughAbleTower::Attack();
	BulletPoolManager::GetInstance()->AddBullet(
		BulletType::Target_Tower_One, std::dynamic_pointer_cast<BaseObject>(m_target),
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
	float previosMaxHitpoint = m_maxHitPoint;
	switch (m_level)
	{
	case 1:
		SetTexture(ResourceManagers::GetInstance()->GetTexture("TowerOnelvl1.tga"));
		SetISize(80, 60);
		m_totalCost = TowerOneCost;
		m_costUpgrade = 100;
		m_range = 300;
		m_attackSpeed = 1.5f;
		m_damage = 2.f;
		m_hitpoint = 300.f;
		m_maxHitPoint = 300.f;
		break;
	case 2:
		SetTexture(ResourceManagers::GetInstance()->GetTexture("TowerOnelvl2.tga"));
		SetISize(80, 60);
		m_totalCost += m_costUpgrade;
		m_costUpgrade = 140;
		m_range = 330.f;
		m_attackSpeed = 2.5f;
		m_damage = 2.5f;
		m_maxHitPoint = 400.f;
		break;
	case 3:
		SetTexture(ResourceManagers::GetInstance()->GetTexture("TowerOnelvl3.tga"));
		SetISize(80, 60);
		m_totalCost += m_costUpgrade;
		m_costUpgrade = 0;
		m_range = 360.f;
		m_attackSpeed = 3.5f;
		m_damage = 3.f;
		m_maxHitPoint = 500.f;
		break;
	default:
		break;
	}
	m_currentTimeAttack = 1 / m_attackSpeed;
	if (m_level >= 2) {
		m_hitpoint = m_hitpoint / previosMaxHitpoint * m_maxHitPoint;
	}
}

void TowerOne::LocateOption()
{
	EnemyPoolManager::ResetFindPath();
	m_towerOption = std::make_shared<TowerOption>();
	m_towerOption->SetMainOptionPosition(m_position.x, m_position.y);
	m_towerOption->SetMainOptionSize(m_iWidth , m_iHeight );
	std::shared_ptr<GameButton> secondButton = std::make_shared<GameButton>(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"),
		ResourceManagers::GetInstance()->GetShader("TextureShader"),
		ResourceManagers::GetInstance()->GetTexture("Tower/remove_tower.tga"));
	secondButton->Set2DPosition(m_position.x - m_iWidth / 2.f - AdjustTowerOption, m_position.y - m_iHeight / 2.f - AdjustTowerOption);
	secondButton->SetISize(m_iWidth / 2, m_iHeight / 2);
	secondButton->SetOnClickTower([](std::shared_ptr<BaseDefensive> tower) {
		Coin::GetInstance()->Refund(tower->GetTotalCost() * RefundRatio);
		DefensivePoolManager::GetInstance()->RemoveUnmove(tower);
		DefensivePoolManager::GetInstance()->Add(tower->GetPosition().x, tower->GetPosition().y, TowerType::Spot);
		EnemyPoolManager::ResetFindPath();
		});
	m_towerOption->AddSecondOption(secondButton);
	std::shared_ptr<GameButton> secondButton2 = std::make_shared<GameButton>(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"),
		ResourceManagers::GetInstance()->GetShader("TextureShader"),
		ResourceManagers::GetInstance()->GetTexture("Tower/upgrade_tower.tga"));
	secondButton2->Set2DPosition(m_position.x + m_iWidth / 2.f + AdjustTowerOption, m_position.y - m_iHeight / 2.f - AdjustTowerOption);
	secondButton2->SetISize(m_iWidth / 2, m_iHeight / 2);
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
