#pragma once
#include "Coin.h"
#include "Diamond.h"
class ResourceTable :public CSingleton<ResourceTable>
{
public:
	ResourceTable(){};
	~ResourceTable(){};
	void Init() {
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
		auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		auto texture = ResourceManagers::GetInstance()->GetTexture("UI/table.tga");
		m_table = std::make_shared<Sprite2D>(model, shader, texture);
		m_table->Set2DStaticPosition(Globals::screenWidth / 2.f, Globals::screenHeight * 0.5 / 10.f);
		m_table->SetISize(Globals::screenWidth * 1 / 4.f, Globals::screenHeight *0.5 / 10.f);
		texture = ResourceManagers::GetInstance()->GetTexture("UI/window_1.tga");
		m_table_2= std::make_shared<Sprite2D>(model, shader, texture);
		m_table_2->Set2DStaticPosition(Globals::screenWidth / 2.f, Globals::screenHeight * 0.5 / 10.f);
		m_table_2->SetISize(Globals::screenWidth * 1 / 4.f - 30, Globals::screenHeight *0.5/ 10.f - 12);
		Coin::GetInstance()->Init();
		Diamond::GetInstance()->Init();
		//rope
		texture = ResourceManagers::GetInstance()->GetTexture("UI/rope_big.tga");
		auto sprite = std::make_shared<Sprite2D>(model, shader, texture);
		sprite->Set2DStaticPosition(Globals::screenWidth / 2.f - 100.f, Globals::screenHeight *0.25 / 10.f);
		sprite->SetISize(10, Globals::screenHeight * 0.5 / 10.f);
		m_listRope.push_back(sprite);
		sprite = std::make_shared<Sprite2D>(model, shader, texture);
		sprite->Set2DStaticPosition(Globals::screenWidth / 2.f + 100.f, Globals::screenHeight *0.25 / 10.f);
		sprite->SetISize(10, Globals::screenHeight * 0.5 / 10.f);
		m_listRope.push_back(sprite);
	}
	void Draw() {
		for (auto& rope : m_listRope)
		{
			rope->Draw();
		}
		m_table->Draw();
		m_table_2->Draw();
		Coin::GetInstance()->Draw();
		Diamond::GetInstance()->Draw();
	}
	void DrawMiddle() {
		for (auto& rope : m_listRope)
		{
			rope->Draw();
		}
		m_table->Draw();
		m_table_2->Draw();
		Diamond::GetInstance()->DrawMiddle();
	}
	void Update() {
		m_table->Set2DStaticPosition();
		m_table_2->Set2DStaticPosition();
		Coin::GetInstance()->Update();
		Diamond::GetInstance()->Update();
		for (auto& rope : m_listRope)
		{
			rope->Set2DStaticPosition();
		}
	}
	void UpdateMiddle() {
		m_table->Set2DStaticPosition();
		m_table_2->Set2DStaticPosition();
		Coin::GetInstance()->Update();
		Diamond::GetInstance()->UpdateMiddle();
		for (auto& rope : m_listRope)
		{
			rope->Set2DStaticPosition();
		}
	}
	void Reset() {
		Coin::GetInstance()->Reset();
		Diamond::GetInstance()->Reset();
	}
private:
	std::shared_ptr<Sprite2D>				m_table;
	std::shared_ptr<Sprite2D>				m_table_2;
	std::list<std::shared_ptr<Sprite2D>>	m_listRope;

};
