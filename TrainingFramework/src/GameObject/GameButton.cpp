#include "GameButton.h"

GameButton::GameButton(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(-1, model, shader, texture), m_pBtClick(nullptr), m_isHolding(false)
{
}

GameButton::~GameButton()
{
}

void GameButton::SetOnClick(void(*pBtClickFun)())
{
	m_pBtClick = pBtClickFun;
}

void GameButton::SetOnClickTower(void(*pBtClickFunTower)(std::shared_ptr<BaseDefensive> tower))
{
	m_pBtClickTower = pBtClickFunTower;
}



bool GameButton::HandleTouchEvents(GLint x, GLint y, bool bIsPressed)
{
	m_isHandled = false;
	if (bIsPressed)
	{
		if ((x > m_position.x - m_iWidth / 2) && (x < m_position.x + m_iWidth / 2)
			&& (y > m_position.y - m_iHeight / 2) && (y < m_position.y + m_iHeight / 2))
		{
			// The button is being pressed down
			m_isHolding = true;
		}
	}
	else
	{
		if ((x > m_position.x - m_iWidth / 2) && (x < m_position.x + m_iWidth / 2)
			&& (y > m_position.y - m_iHeight / 2) && (y < m_position.y + m_iHeight / 2)
			&& m_isHolding == true)
		{
			// Only perform click action when the same button was pressed down and released
			m_pBtClick();
			m_isHandled = true;
		}
		m_isHolding = false;
	}
	return m_isHandled;
}
bool GameButton::HandleTouchEventsTower(GLint x, GLint y, bool bIsPressed, std::shared_ptr<BaseDefensive> tower)
{
	m_isHandled = false;
	if (bIsPressed)
	{
		if ((x > m_position.x - m_iWidth / 2) && (x < m_position.x + m_iWidth / 2)
			&& (y > m_position.y - m_iHeight / 2) && (y < m_position.y + m_iHeight / 2))
		{

			// The button is being pressed down
			m_isHolding = true;
		}
	}
	else
	{
		if ((x > m_position.x - m_iWidth / 2) && (x < m_position.x + m_iWidth / 2)
			&& (y > m_position.y - m_iHeight / 2) && (y < m_position.y + m_iHeight / 2)
			&& m_isHolding == true)
		{
			// Only perform click action when the same button was pressed down and released
			m_pBtClickTower(tower);
			m_isHandled = true;
		}
		m_isHolding = false;
	}
	return m_isHandled;
}

bool GameButton::IsHolding()
{
	return m_isHolding;
}

bool GameButton::IsHandled()
{
	return m_isHandled;
}
