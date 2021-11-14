#include "MainTower.h"
#include "DefensiveManager.h"

MainTower::MainTower()
	:UnMoveThroughAbleTower()
{
}

MainTower::MainTower(float x, float y)
	: UnMoveThroughAbleTower(ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg"),
		ResourceManagers::GetInstance()->GetShader("TextureShader"),
		ResourceManagers::GetInstance()->GetTexture("MainTowerlvl1.tga"),
		x, y, 126, 126, 72, 72, 500, 1, 0, 500, 1, TowerType::Main, 6)
{

}

void MainTower::Attack()
{
}

void MainTower::LocateOption()
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
		ResourceManagers::GetInstance()->GetTexture("AncientTree1.tga"));
	secondButton->Set2DPosition(m_position.x - m_iWidth / 2, m_position.y - m_iHeight / 2);
	secondButton->SetISize(m_iWidth / 3, m_iHeight / 3);
	secondButton->SetOnClickTower([](std::shared_ptr<BaseDefensive> tower) {
		tower->Upgrade();
		});
	m_towerOption->AddSecondOption(secondButton);
}

void MainTower::Reset()
{
	UnMoveThroughAbleTower::Reset();
	Upgrade();
}

void MainTower::Update(GLfloat deltatime)
{
	UnMoveThroughAbleTower::Update(deltatime);
}

void MainTower::Upgrade()
{
	UnMoveThroughAbleTower::Upgrade();
	std::cout << m_level << std::endl;
	switch (m_level)
	{
	case 1:
		SetTexture(ResourceManagers::GetInstance()->GetTexture("MainTowerlvl1.tga"));
		SetISize(126, 126);
		SetSize(72, 72);
		m_range = 200;
		m_attackSpeed = 1;
		m_currentTimeAttack = GetAttackSpeed();
		m_hitpoint = 500.f;
		m_maxHitPoint = 500.f;
		break;
	case 2:
		SetTexture(ResourceManagers::GetInstance()->GetTexture("MainTowerlvl2.tga"));
		SetISize(140, 140);
		SetSize(80, 80);
		m_range = 200;
		m_attackSpeed = 1;
		m_currentTimeAttack = GetAttackSpeed();
		m_hitpoint = 500.f;
		m_maxHitPoint = 500.f;
		break;
	case 3:
		SetTexture(ResourceManagers::GetInstance()->GetTexture("MainTowerlvl3.tga"));
		SetISize(154, 154);
		SetSize(88, 88);
		m_range = 200;
		m_attackSpeed = 1;
		m_currentTimeAttack = GetAttackSpeed();
		m_hitpoint = 500.f;
		m_maxHitPoint = 500.f;
		break;
	case 4:
		SetTexture(ResourceManagers::GetInstance()->GetTexture("MainTowerlvl4.tga"));
		SetISize(168, 168);
		SetSize(96, 96);
		m_range = 200;
		m_attackSpeed = 1;
		m_currentTimeAttack = GetAttackSpeed();
		m_hitpoint = 500.f;
		m_maxHitPoint = 500.f;
		break;
	case 5:
		SetTexture(ResourceManagers::GetInstance()->GetTexture("MainTowerlvl5.tga"));
		SetISize(182, 182);
		SetSize(104, 104);
		m_range = 200;
		m_attackSpeed = 1;
		m_currentTimeAttack = 1;
		m_hitpoint = 500.f;
		m_maxHitPoint = 500.f;
		break;
	case 6:
		SetTexture(ResourceManagers::GetInstance()->GetTexture("MainTowerlvl6.tga"));
		SetISize(196, 196);
		SetSize(112, 112);
		m_range = 200;
		m_attackSpeed = 1;
		m_currentTimeAttack = GetAttackSpeed();
		m_hitpoint = 500.f;
		m_maxHitPoint = 500.f;
		break;
	default:
		break;
	}
}
