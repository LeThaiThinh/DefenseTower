#include "HUD.h"
#include <Base/AttackAble.h>
#include <Base/AbleToAttack.h>
#include "Defensive/DefensiveManager.h"
#include "Enemy/EnemyManager.h"
#include "Base/Sprite2D.h"
#include <ft2build.h>

HUD::HUD()
{
}

HUD::~HUD()
{
}

void HUD::Init()
{
	m_subj = MainCharacter::GetInstance();
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("UI/table.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	//table
	m_table = std::make_shared<Sprite2D>(model, shader, texture);
	m_table->Set2DStaticPosition(Globals::screenWidth / 2.f, Globals::screenHeight * 5.25 / 6.f);
	m_table->SetISize(Globals::screenWidth/2, Globals::screenHeight/6);

	m_table2 = std::make_shared<Sprite2D>(model, shader, texture);
	m_table2->Set2DStaticPosition(0, 0);
	m_table2->SetISize(Globals::screenWidth / 2, Globals::screenHeight / 8);
	//icon
	texture = ResourceManagers::GetInstance()->GetTexture("UI/health_icon.tga");
	auto icon = std::make_shared<Sprite2D>(model, shader, texture);
	icon->Set2DStaticPosition(550, Globals::screenHeight * 5.f / 6.f);
	icon->SetISize(50, 50);
	m_iconList.push_back(icon);

	texture = ResourceManagers::GetInstance()->GetTexture("UI/attack_damage_icon.tga");
	icon = std::make_shared<Sprite2D>(model, shader, texture);
	icon->Set2DStaticPosition(750, Globals::screenHeight * 5.f / 6.f);
	icon->SetISize(50, 50);
	m_iconList.push_back(icon);

	texture = ResourceManagers::GetInstance()->GetTexture("UI/attack_range_icon.tga");
	icon = std::make_shared<Sprite2D>(model, shader, texture);
	icon->Set2DStaticPosition(550, Globals::screenHeight * 5.5f / 6.f);
	icon->SetISize(50, 50);
	m_iconList.push_back(icon);

	texture = ResourceManagers::GetInstance()->GetTexture("UI/attack_speed_icon.tga");
	icon = std::make_shared<Sprite2D>(model, shader, texture);
	icon->Set2DStaticPosition(750, Globals::screenHeight * 5.5f / 6.f);
	icon->SetISize(50, 50);
	m_iconList.push_back(icon);
	//avatar
	m_avatar = std::make_shared<Sprite2D>(model, shader, texture);
	m_avatar->Set2DStaticPosition(400, Globals::screenHeight * 5.25f / 6.f - 10);
	m_avatar->SetISize(100, 100);
	//text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Triangle.ttf");
	m_textHitpointPerMaxHitpoint = std::make_shared< Text>(shader, font, "", Vector4(1.0f, 0.6f, 0.f, 1.0f), 1.0f);
	m_textHitpointPerMaxHitpoint->Set2DPosition(Vector2(600, Globals::screenHeight * 5.f / 6.f + 5));
	m_textAttackDamgage = std::make_shared< Text>(shader, font, "", Vector4(1.0f, 0.6f, 0.f, 1.0f), 1.0f);
	m_textAttackDamgage->Set2DPosition(Vector2(800, Globals::screenHeight * 5.f / 6.f + 5));
	m_textAttackRange = std::make_shared< Text>(shader, font, "", Vector4(1.0f, 0.6f, 0.f, 1.0f), 1.0f);
	m_textAttackRange->Set2DPosition(Vector2(600, Globals::screenHeight * 5.5f / 6.f + 5));
	m_textAttackSpeed = std::make_shared<Text>(shader, font, "", Vector4(1.0f, 0.6f, 0.f, 1.0f), 1.0f);
	m_textAttackSpeed->Set2DPosition(Vector2(800, Globals::screenHeight * 5.5f / 6.f + 5));
	m_textName = std::make_shared<Text>(shader, font, "", Vector4(1.0f, 0.6f, 0.f, 1.0f), 1.0f);
	m_textName->Set2DPosition(Vector2(400, Globals::screenHeight * 5.5f / 6.f + 5));
	m_textLevel = std::make_shared<Text>(shader, font, "", Vector4(1.0f, 0.6f, 0.f, 1.0f), 1.0f);
	m_textLevel->Set2DPosition(Vector2(400, Globals::screenHeight * 5.5f / 6.f + 20));
	UpdateSubject();

	m_textEnemyRemain = std::make_shared<Text>(shader, font, "", Vector4(1.0f, 0.6f, 0.f, 1.0f), 1.0f);
	m_textEnemyRemain->Set2DPosition(Vector2(25, 35));
}

void HUD::ChangeSubject(std::shared_ptr<BaseObject> obj)
{
	m_subj = obj;
	UpdateSubject();
}
void HUD::Reset()
{
	m_subj = MainCharacter::GetInstance();
	UpdateSubject();
}
void HUD::UpdateSubject()
{
	m_textHitpointPerMaxHitpoint->SetText(std::to_string((int)std::dynamic_pointer_cast<AttackAble>(m_subj)->GetHitPoint())+ "/" + std::to_string((int)std::dynamic_pointer_cast<AttackAble>(m_subj)->GetMaxHitPoint()));
	m_textAttackDamgage->SetText(std::to_string((int)std::dynamic_pointer_cast<AbleToAttack>(m_subj)->GetDamage()));
	if (m_subj->GetTypeObject() == "Tower")
		m_textAttackRange->SetText(std::to_string((int)std::dynamic_pointer_cast<AbleToAttack>(m_subj)->GetRange()- 50));
	else
		m_textAttackRange->SetText(std::to_string((int)std::dynamic_pointer_cast<AbleToAttack>(m_subj)->GetRange() ));
	m_textAttackSpeed->SetText(std::to_string((int)std::dynamic_pointer_cast<AbleToAttack>(m_subj)->GetAttackSpeed()));
	m_textName->SetText(m_subj->GetName());
	m_textName->Set2DPosition(400 - m_textName->GetText().length() * 5, Globals::screenHeight * 5.5f / 6.f + 5);
	if (m_subj->GetTypeObject() == "Tower")
		if(std::dynamic_pointer_cast<BaseDefensive>(m_subj)->IsLevelMax())
			m_textLevel->SetText("Level Max");
		else
			m_textLevel->SetText("Level "+ std::to_string(std::dynamic_pointer_cast<BaseDefensive>(m_subj)->GetLevel()));
	else
		m_textLevel->SetText("");
	m_textLevel->Set2DPosition(400 - m_textLevel->GetText().length() * 4, Globals::screenHeight * 5.5f / 6.f + 25);
	m_avatar->SetTexture(std::dynamic_pointer_cast<AttackAble>(m_subj)->GetAvatar());
}
bool HUD::HandleTouchEvents(GLint x, GLint y, bool bIsPressed)
{
	for (auto& enemy:EnemyPoolManager::GetInstance()->flyEnemyList)
	{
		if (enemy->HandleTouchHUD(x, y, bIsPressed)) {
			ChangeSubject(std::dynamic_pointer_cast<BaseObject>(enemy));
			return true;
		}
	}
	for (auto& enemy : EnemyPoolManager::GetInstance()->groundEnemyList)
	{
		if (enemy->HandleTouchHUD(x, y, bIsPressed)) {
			ChangeSubject(std::dynamic_pointer_cast<BaseObject>(enemy));
			return true;
		}
	}
	for (auto& tower : DefensivePoolManager::GetInstance()->unMoveThroughAbleTowerList)
	{
		if (tower->HandleTouchEvents(x, y, bIsPressed,tower)) {
			ChangeSubject(std::dynamic_pointer_cast<BaseObject>(tower));
			return true;
		}
	}
	if (DefensivePoolManager::GetInstance()->mainTower->HandleTouchEvents(x, y, bIsPressed, DefensivePoolManager::GetInstance()->mainTower)) {
		ChangeSubject(std::dynamic_pointer_cast<BaseObject>(DefensivePoolManager::GetInstance()->mainTower));
		return true;
	}
	if (MainCharacter::GetInstance()->HandleTouchHUD(x, y, bIsPressed)) {
		ChangeSubject(MainCharacter::GetInstance());
	}
	return false;
}

void HUD::Update()
{
	if (m_textHitpointPerMaxHitpoint <= 0)
		ChangeSubject(MainCharacter::GetInstance());
	UpdateSubject();
	m_table->Set2DStaticPosition();
	m_table2->Set2DStaticPosition();
	m_avatar->Set2DStaticPosition();
	m_textEnemyRemain->SetText("Total enemy remain: "+ std::to_string(EnemyPoolManager::GetInstance()->groundEnemyList.size() + EnemyPoolManager::GetInstance()->flyEnemyList.size() + EnemyPoolManager::GetInstance()->spawnerList.size()));
	for (auto& icon : m_iconList) {
		icon->Set2DStaticPosition();
	}
}

void HUD::Draw()
{

	for (auto& enemy : EnemyPoolManager::GetInstance()->groundEnemyList) {
		enemy->DrawHUD();
	}
	for (auto& enemy : EnemyPoolManager::GetInstance()->flyEnemyList) {
		enemy->DrawHUD();
	}
	for (auto& tower : DefensivePoolManager::GetInstance()->unMoveThroughAbleTowerList) {
		tower->DrawHUD();
	}
	for (auto& tower : DefensivePoolManager::GetInstance()->spotList) {
		tower->DrawHUD();
	}
	m_table->Draw();
	m_table2->Draw();
	m_avatar->Draw();
	/**/m_textHitpointPerMaxHitpoint->Draw();
	m_textAttackDamgage->Draw();
	m_textAttackRange->Draw();
	m_textAttackSpeed->Draw();
	m_textName->Draw();
	m_textLevel->Draw();
	m_textEnemyRemain->Draw();
	for (auto& icon : m_iconList) {
		icon->Draw();
	}
}
