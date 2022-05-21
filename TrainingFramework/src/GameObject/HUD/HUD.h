#pragma once
#include "Singleton.h"
#include <Base/Text.h>
#include "Base/Sprite2D.h"

class HUD : public CSingleton<HUD>
{
public:
	HUD();
	~HUD();

	void Init();
	void ChangeSubject(std::shared_ptr<BaseObject> obj);
	void Reset();
	void UpdateSubject();
	bool HandleTouchEvents(GLint x, GLint y, bool bIsPressed);
	void Update();
	void Draw();

private:
	std::shared_ptr<BaseObject> m_subj;
	std::shared_ptr<Text> m_textHitpointPerMaxHitpoint;
	std::shared_ptr<Text> m_textAttackDamgage;
	std::shared_ptr<Text> m_textAttackSpeed;
	std::shared_ptr<Text> m_textAttackRange;
	std::shared_ptr<Text> m_textName;
	std::shared_ptr<Text> m_textLevel;
	std::shared_ptr<Text> m_textEnemyRemain;
	std::shared_ptr<Sprite2D>	m_table;
	std::shared_ptr<Sprite2D>	m_table2;
	std::shared_ptr<Sprite2D>	m_avatar;
	std::list<std::shared_ptr<Sprite2D>>	m_iconList;
};

