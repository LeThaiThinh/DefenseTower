#include "GameButton.h"
#include <CheckCollision.h>

GameButton::GameButton(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(-1, model, shader, texture), m_pBtClick(nullptr),m_pBtClickTower(nullptr),m_pBtClickTexture(nullptr), m_isHandled(false), m_isHolding(false)
{
}

GameButton::~GameButton()
{
}

void GameButton::SetOnClick(void(*pBtClickFun)())
{

	m_pBtClick = pBtClickFun;
}
void GameButton::SetOnClickTexture(void(*pBtClickFunTexture)(std::shared_ptr<GameButton> gamebutton))
{

	m_pBtClickTexture = pBtClickFunTexture;

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
		if (CheckCollision::PointInRectI(Vector3(x, y, 0), std::dynamic_pointer_cast<Sprite2D>(shared_from_this())))
		{
			// The button is being pressed down
			m_isHolding = true;
		}
	}
	else
	{
		if (CheckCollision::PointInRectI(Vector3(x,y,0),std::dynamic_pointer_cast<Sprite2D>(shared_from_this()))
			&& m_isHolding == true)
		{
			// Only perform click action when the same button was pressed down and released
			if(m_pBtClick)
				m_pBtClick();
			else
				m_pBtClickTexture(std::dynamic_pointer_cast<GameButton>(shared_from_this()));
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
		if ((x > m_position.x - m_iWidth / 2.f) && (x < m_position.x + m_iWidth / 2.f)
			&& (y > m_position.y - m_iHeight / 2.f) && (y < m_position.y + m_iHeight / 2.f))
		{
			// The button is being pressed down
			m_isHolding = true;
		}
	}
	else
	{
		if ((x > m_position.x - m_iWidth / 2.f) && (x < m_position.x + m_iWidth / 2.f)
			&& (y > m_position.y - m_iHeight / 2.f) && (y < m_position.y + m_iHeight / 2.f)
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
