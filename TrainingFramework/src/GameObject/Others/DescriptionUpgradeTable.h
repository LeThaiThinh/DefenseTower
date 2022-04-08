#pragma once
#include "Application.h"
#include "Base/Sprite2D.h"
#include "UpgradeOption.h"
#include "ResourceManagers.h"
#define DesTableHeight Globals::screenWidth/6
#define DesTableWidth Globals::screenWidth/3
#define DesTableY Globals::screenHeight*5/6

class DescriptionUpgradeTable
{
public:
	DescriptionUpgradeTable() {
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
		auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		auto texture = ResourceManagers::GetInstance()->GetTexture("UI/table.tga");
		leftTable = std::make_shared<Sprite2D>(model, shader, texture);
		leftTable->Set2DPosition(Globals::screenWidth / 2 - DesTableWidth / 2, DesTableY);
		leftTable->SetISize(DesTableWidth, DesTableHeight);
		rightTable = std::make_shared<Sprite2D>(model, shader, texture);
		rightTable->Set2DPosition(Globals::screenWidth / 2 + DesTableWidth / 2, DesTableY);
		rightTable->SetISize(DesTableWidth, DesTableHeight);
		texture = ResourceManagers::GetInstance()->GetTexture("UI/window_2.tga");
		middleTable = std::make_shared<Sprite2D>(model, shader, texture);
		middleTable->Set2DPosition(Globals::screenWidth / 2 , DesTableY - DesTableHeight/2);
		middleTable->SetISize(DesTableWidth * 2/3 , DesTableHeight/2);
		texture = ResourceManagers::GetInstance()->GetTexture("UI/yellow_arrow.tga");
		yellowArrow = std::make_shared<Sprite2D>(model, shader, texture);
		yellowArrow->Set2DPosition(Globals::screenWidth / 2, DesTableY );
		yellowArrow->SetISize(30, 50);
	};
	~DescriptionUpgradeTable(){};

	void Draw(std::shared_ptr<UpgradeOption> upOpt) {
		leftTable->Draw();
		rightTable->Draw();
		middleTable->Draw();
		yellowArrow->Draw();
		upOpt->DrawDes();
	};
	void Draw() {
		leftTable->Draw();
		rightTable->Draw();
		middleTable->Draw();
		yellowArrow->Draw();

	}
private:
	std::shared_ptr<Sprite2D> leftTable;
	std::shared_ptr<Sprite2D> rightTable;
	std::shared_ptr<Sprite2D> middleTable;
	std::shared_ptr<Sprite2D> yellowArrow;

};

