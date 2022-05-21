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
	x, y, 120, 100, 120, 100, 300, 1.5, 2,0,Vector3(0,0,0),nullptr,nullptr, 300.f, 0, TowerType::One, 3)
{
	SetName("Brown Tower");
	LocateOption();
	Upgrade();
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
		SetAvatar(ResourceManagers::GetInstance()->GetTexture("TowerOnelvl1.tga"));
		SetISize(120, 100);
		m_totalCost = TowerOneCost;
		m_costUpgrade = 50;
		m_range = 300;
		m_attackSpeed = 1.5f;
		m_damage = 2.f;
		m_hitpoint = 300.f;
		m_maxHitPoint = 300.f;
		break;
	case 2:
		SetTexture(ResourceManagers::GetInstance()->GetTexture("TowerOnelvl2.tga"));
		SetAvatar(ResourceManagers::GetInstance()->GetTexture("TowerOnelvl2.tga"));
		SetISize(126, 105);
		m_totalCost += m_costUpgrade;
		m_costUpgrade = 100;
		m_range = 400.f;
		m_attackSpeed = 2.5f;
		m_damage = 4.5f;
		m_maxHitPoint = m_maxHitPoint + 200;
		break;
	case 3:
		SetTexture(ResourceManagers::GetInstance()->GetTexture("TowerOnelvl3.tga"));
		SetAvatar(ResourceManagers::GetInstance()->GetTexture("TowerOnelvl3.tga"));
		SetISize(132, 110);
		m_totalCost += m_costUpgrade;
		m_costUpgrade = 0;
		m_range = 500.f;
		m_attackSpeed = 3.5f;
		m_damage = 7.f;
		m_maxHitPoint = m_maxHitPoint + 200;
		break;
	default:
		break;
	}
	m_towerOption->GetCostTextList().front()->SetText(std::to_string((int)(m_totalCost * RefundRatio)));
	if (m_level < m_maxlevel)
		m_towerOption->GetCostTextList().back()->SetText(std::to_string(m_costUpgrade));
	else
		m_towerOption->GetCostTextList().back()->SetText("max");
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

	auto shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Triangle.ttf");
	auto 	text = std::make_shared< Text>(shader, font, std::to_string((int)(TowerOneCost * RefundRatio)), Vector4(1.0f, 0.6f, 0.f, 1.0f), 0.6f);
	text->Set2DPositionDynamic(Vector2(m_position.x - m_iWidth / 2.f , m_position.y - m_iHeight / 4.f - AdjustTowerOption));
	m_towerOption->AddCostText(text);
	text = std::make_shared< Text>(shader, font, std::to_string(TowerOneCost), Vector4(1.0f, 0.6f, 0.f, 1.0f), 0.6f);
	text->Set2DPositionDynamic(Vector2(m_position.x + m_iWidth / 2.f + AdjustTowerOption, m_position.y - m_iHeight / 4.f - AdjustTowerOption));
	m_towerOption->AddCostText(text);
}

void TowerOne::Update(GLfloat deltatime)
{
	UnMoveThroughAbleTower::Update(deltatime);
}
