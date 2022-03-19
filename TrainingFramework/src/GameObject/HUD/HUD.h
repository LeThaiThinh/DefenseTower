#pragma once
#include "Singleton.h"
#include <Base/Text.h>
class HUD : CSingleton<HUD>
{
public:
	HUD();
	~HUD();

	void ChangeSubject(std::shared_ptr<BaseObject> obj);
	bool HandleTouchEvents(GLint x, GLint y, bool bIsPressed);
	void Draw();

private:
	float m_hitpoint;
	float m_maxHitpoint;
	std::shared_ptr<Text> m_textHitpointPerMaxHitpoint;
	float m_attackDamage;
	std::shared_ptr<Text> m_textAttackDamgage;
	float m_attackSpeed;
	std::shared_ptr<Text> m_textAttackSpeed;
	float m_attackRange;
	std::shared_ptr<Text> m_textAttackRange;

};

