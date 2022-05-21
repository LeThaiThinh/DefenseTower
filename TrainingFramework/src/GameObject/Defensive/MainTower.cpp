#include "MainTower.h"
#include <Others/TowerOption.h>
#include "Resource/Coin.h"
#define MainTowerCost 60

MainTower::MainTower()
	:UnMoveThroughAbleTower()
{
}

MainTower::MainTower(float x, float y)
	: UnMoveThroughAbleTower(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"),
		ResourceManagers::GetInstance()->GetShader("TextureShader"),ResourceManagers::GetInstance()->GetTexture("Tower/main_tower_1.tga"),
		x, y, 198, 165, 180,150 , 100, 1, 0, 0.2f,Vector3(0,0,0),
		ResourceManagers::GetInstance()->GetTexture("Tower/main_tower_1.tga"), ResourceManagers::GetInstance()->GetTexture("Tower/main_tower_1.tga"), 
	5000, 1, TowerType::Main, 3)
{
	SetName("Main tower");
	SetAvatar(ResourceManagers::GetInstance()->GetTexture("Tower/main_tower_1.tga"));
	LocateOption();
}

void MainTower::Attack()
{
}

void MainTower::LocateOption()
{
	m_towerOption = std::make_shared<TowerOption>();
	m_towerOption->SetMainOptionPosition(m_position.x,m_position.y);
	m_towerOption->SetMainOptionSize(m_iWidth/2+m_iHeight/2, m_iWidth / 2 + m_iHeight / 2);
	std::shared_ptr<GameButton> secondButton = std::make_shared<GameButton>(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"),
		ResourceManagers::GetInstance()->GetShader("TextureShader"),
		ResourceManagers::GetInstance()->GetTexture("Tower/upgrade_tower.tga"));
	secondButton->Set2DPosition(m_position.x - m_iWidth / 2.f, m_position.y - m_iHeight / 2.f);
	secondButton->SetISize(m_iWidth / 3.f, m_iHeight / 3.f);
	secondButton->SetOnClickTower([](std::shared_ptr<BaseDefensive> tower) {
		tower->Upgrade();
		});
	m_towerOption->AddSecondOption(secondButton);

	auto shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Triangle.ttf");
	auto text = std::make_shared< Text>(shader, font, std::to_string(MainTowerCost), Vector4(1.0f, 0.6f, 0.f, 1.0f), 0.8f);
	text->Set2DPositionDynamic(Vector2(m_position.x - m_iWidth / 2.f - AdjustTowerOption, m_position.y - m_iHeight  / 3.f - AdjustTowerOption*2));
	m_towerOption->AddCostText(text);
}

void MainTower::Reset()
{
	UnMoveThroughAbleTower::Reset();
	LocateOption();
	Upgrade();
}

void MainTower::Update(GLfloat deltatime)
{
	UnMoveThroughAbleTower::Update(deltatime);
}

void MainTower::Upgrade()
{
	UnMoveThroughAbleTower::Upgrade();
	float previosMaxHitpoint = m_maxHitPoint;
	switch (m_level)
	{
	case 1:
		SetTexture(ResourceManagers::GetInstance()->GetTexture("Tower/main_tower_1.tga"));
		SetAvatar(ResourceManagers::GetInstance()->GetTexture("Tower/main_tower_1.tga"));
		SetISize(198, 165);
		m_totalCost = MainTowerCost;
		m_costUpgrade = 200;
		m_range = 200;
		m_attackSpeed = 1;
		m_currentTimeAttack = GetAttackSpeed();
		m_hitpoint = 5000.f;
		m_maxHitPoint = 5000.f;
		break;
	case 2:
		SetTexture(ResourceManagers::GetInstance()->GetTexture("Tower/main_tower_2.tga"));
		SetAvatar(ResourceManagers::GetInstance()->GetTexture("Tower/main_tower_2.tga"));
		SetISize(204, 170);
		m_costUpgrade = 250;
		m_range = 200;
		m_attackSpeed = 1;
		m_currentTimeAttack = GetAttackSpeed();
		m_maxHitPoint = m_maxHitPoint + 500;
		break;
	case 3:
		SetTexture(ResourceManagers::GetInstance()->GetTexture("Tower/main_tower_3.tga"));
		SetAvatar(ResourceManagers::GetInstance()->GetTexture("Tower/main_tower_3.tga"));
		SetISize(210, 175);
		m_costUpgrade = 0;
		m_range = 200;
		m_attackSpeed = 1;
		m_currentTimeAttack = GetAttackSpeed();
		m_maxHitPoint = m_maxHitPoint + 500;
		break;
	default:
		break;
	}
	if (m_level < m_maxlevel)
		m_towerOption->GetCostTextList().back()->SetText(std::to_string(m_costUpgrade));
	else
		m_towerOption->GetCostTextList().back()->SetText("max");
	if (m_level >= 2) {
		m_hitpoint = m_hitpoint / previosMaxHitpoint * m_maxHitPoint;
	}
}
