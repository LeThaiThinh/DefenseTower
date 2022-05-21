#pragma once
#include "../GameManager/Singleton.h"
#include "Base/Sprite2D.h"
#include <Base/Text.h>
#include "ResourceManagers.h"
#include "GameStates/GSSelectStage.h"
#define COIN_POSITION_X Globals::screenWidth/2.f-Globals::screenWidth/16.f-10
#define COIN_POSITION_Y Globals::screenHeight * 0.5f / 10.f
#define COIN_WIDTH 30
#define COIN_HEIGHT 30
class Coin:public CSingleton<Coin>
{
public:
	int m_coinValue;
	std::shared_ptr<Text> m_coinText;
	std::shared_ptr<Sprite2D> m_coinImage;
	Coin():m_coinValue(0){}
	~Coin(){}
	void Init() {
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
		auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		auto texture = ResourceManagers::GetInstance()->GetTexture("UI/coin.tga");
		auto font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
		m_coinImage = std::make_shared<Sprite2D>(model, shader, texture, COIN_POSITION_X, COIN_POSITION_Y, COIN_WIDTH, COIN_HEIGHT, COIN_WIDTH, COIN_HEIGHT);
		m_coinImage->Set2DStaticPosition(COIN_POSITION_X - 20, COIN_POSITION_Y);
		shader = ResourceManagers::GetInstance()->GetShader("TextShader");
		switch (GSSelectStage::choosenLevel)
		{
		case 1:
			m_coinValue = 5000;
			break;
		case 2: 
			m_coinValue = 2000;
			break;
		default:
			m_coinValue = 2000;
			break;
		}
		m_coinText = std::make_shared<Text>(shader, font, std::to_string(m_coinValue), Vector4(1.0f, 0.5f, 0.0f, 1.0f), 1.0f);
		m_coinText->Set2DPosition(COIN_POSITION_X + 5, COIN_POSITION_Y+10);
	}
	bool Purchase(int cost) { 
		if (m_coinValue >= cost) {
			m_coinValue -= cost;
			return true; 
		}
		return false;
	}
	void Refund(int cost) {
		m_coinValue += cost;
	}
	void Bounty(int bounty) {
		m_coinValue += bounty;
	}
	void Update() {
		m_coinText->SetText(std::to_string(m_coinValue));
		m_coinText->Set2DPosition(COIN_POSITION_X + 5, COIN_POSITION_Y+10);
		m_coinImage->Set2DStaticPosition();

	}
	void Draw() {
		m_coinImage->Draw();
		m_coinText->Draw();
	}
	void Reset() {
		m_coinValue = 0;
	}

};
