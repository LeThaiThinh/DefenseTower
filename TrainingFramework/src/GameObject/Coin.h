#pragma once
#include "../GameManager/Singleton.h"
#include "Sprite2D.h"
#include <Text.h>
#include "ResourceManagers.h"
#define COIN_POSITION_X 50.f
#define COIN_POSITION_Y 50.f
#define COIN_WIDTH 50
#define COIN_HEIGHT 50
#define COIN_TEXT_POSITION_X 0.f
#define COIN_TEXT_POSITION_Y 50.f
class Coin:public CSingleton<Coin>
{
public:
	int m_coinValue;
	std::shared_ptr<Text> m_coinText;
	std::shared_ptr<Sprite2D> m_coinImage;
	Coin():m_coinValue(0){}
	~Coin(){}
	void Init(int level) {
		m_coinValue = 200;
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
		auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		auto texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
		auto font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
		m_coinImage = std::make_shared<Sprite2D>(model, shader, texture, COIN_POSITION_X, COIN_POSITION_Y, COIN_WIDTH, COIN_HEIGHT, COIN_WIDTH, COIN_HEIGHT);
		shader = ResourceManagers::GetInstance()->GetShader("TextShader");
		m_coinText=std::make_shared<Text>(shader, font ,std::to_string(m_coinValue), Vector4(1.0f, 0.5f, 0.0f, 1.0f), 1.0f);
		m_coinText->Set2DPosition(COIN_TEXT_POSITION_X, COIN_TEXT_POSITION_Y);
	}
	bool Purchase(int cost) { 
		if (m_coinValue > cost) {
			m_coinValue -= cost;
			return true; 
		}
		return false;
	}
	void Refund(int cost) {
		m_coinValue += cost;
	}
	void Update() {
		m_coinText->SetText(std::to_string(m_coinValue));
		m_coinText->Set2DPosition(COIN_TEXT_POSITION_X, COIN_TEXT_POSITION_Y);
	}
	void Draw() {
		//m_coinImage->Draw();
		m_coinText->Draw();
	}
	void Reset() {
		m_coinValue = 0;
	}

};
