#pragma once
#include "../GameManager/Singleton.h"
#include "Sprite2D.h"
#include <Text.h>
#include "ResourceManagers.h"
#include "GameStates/GSMenu.h"
#define DIAMOND_POSITION_X Globals::screenWidth/2.f+Globals::screenWidth/16.f-20
#define DIAMOND_POSITION_X_MIDDLE Globals::screenWidth/2.f
#define DIAMOND_POSITION_Y Globals::screenHeight * 0.5f / 10.f
#define DIAMOND_WIDTH 30
#define DIAMOND_HEIGHT 30
class Diamond :public CSingleton<Diamond>
{
public:
	std::shared_ptr<Text> m_diamondText;
	std::shared_ptr<Sprite2D> m_diamondImage;
	std::shared_ptr<Text> m_diamondText_middle;
	std::shared_ptr<Sprite2D> m_diamondImage_middle;
	Diamond()  {}
	~Diamond() {}
	void Init() {
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
		auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		auto texture = ResourceManagers::GetInstance()->GetTexture("UI/crystal.tga");
		auto font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
		m_diamondImage = std::make_shared<Sprite2D>(model, shader, texture, DIAMOND_POSITION_X, DIAMOND_POSITION_Y, DIAMOND_WIDTH, DIAMOND_HEIGHT, DIAMOND_WIDTH, DIAMOND_HEIGHT);
		m_diamondImage->Set2DStaticPosition(DIAMOND_POSITION_X - 20, DIAMOND_POSITION_Y);
		m_diamondImage_middle = std::make_shared<Sprite2D>(model, shader, texture, DIAMOND_POSITION_X, DIAMOND_POSITION_Y, DIAMOND_WIDTH, DIAMOND_HEIGHT, DIAMOND_WIDTH, DIAMOND_HEIGHT);
		m_diamondImage_middle->Set2DStaticPosition(DIAMOND_POSITION_X_MIDDLE - 20, DIAMOND_POSITION_Y);
		shader = ResourceManagers::GetInstance()->GetShader("TextShader");
		m_diamondText = std::make_shared<Text>(shader, font, std::to_string(GSMenu::diamond), Vector4(1.0f, 0.5f, 0.0f, 1.0f), 1.0f);
		m_diamondText->Set2DPosition(DIAMOND_POSITION_X+ 5, DIAMOND_POSITION_Y+10);
		m_diamondText_middle = std::make_shared<Text>(shader, font, std::to_string(GSMenu::diamond), Vector4(1.0f, 0.5f, 0.0f, 1.0f), 1.0f);
		m_diamondText_middle->Set2DPosition(DIAMOND_POSITION_X_MIDDLE + 5, DIAMOND_POSITION_Y + 10);
	}
	bool Purchase(int cost) {
		if (GSMenu::diamond > cost) {
			GSMenu::diamond -= cost;
			return true;
		}
		return false;
	}
	void Refund(int cost) {
		GSMenu::diamond += cost;
	}
	void Bounty(int bounty) {
		GSMenu::diamond += bounty;
	}
	void Update() {
		m_diamondText->SetText(std::to_string(GSMenu::diamond));
		m_diamondText->Set2DPosition(DIAMOND_POSITION_X + 5.f, DIAMOND_POSITION_Y+10);
		m_diamondImage->Set2DStaticPosition();
	}
	void UpdateMiddle() {
		m_diamondText_middle->SetText(std::to_string(GSMenu::diamond));
		m_diamondText_middle->Set2DPosition(DIAMOND_POSITION_X_MIDDLE + 5.f, DIAMOND_POSITION_Y + 10);
		m_diamondImage_middle->Set2DStaticPosition();
	}
	void Draw() {
		m_diamondImage->Draw();
		m_diamondText->Draw();
	}
	void DrawMiddle() {
		m_diamondImage_middle->Draw();
		m_diamondText_middle->Draw();
	}
	void Reset() {
		GSMenu::diamond = 0;
	}

};
