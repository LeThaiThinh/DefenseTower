#pragma once 
#include "Sprite2D.h"

class BaseDefensive;
class GameButton : public Sprite2D
{
public:
	GameButton() : Sprite2D(), m_pBtClick(nullptr), m_pBtClickTower(nullptr), m_isHandled(false), m_pBtClickTexture(nullptr), m_isHolding(false) {}
	GameButton(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
	~GameButton();
	void	SetOnClick(void	(*pBtClickFun)());
  void	SetOnClickTexture(void(*pBtClickFunTexture)(std::shared_ptr<GameButton> gamebutton));;
	void	SetOnClickTower(void(*pBtClickFunTower)(std::shared_ptr<BaseDefensive> tower));;

	bool	HandleTouchEvents(GLint x, GLint y, bool bIsPressed);
	bool	HandleTouchEventsTower(GLint x, GLint y, bool bIsPressed, std::shared_ptr<BaseDefensive> tower);
	bool	IsHolding();
	bool	IsHandled();

private:
	void	(*m_pBtClick)();
	void	(*m_pBtClickTexture)(std::shared_ptr<GameButton> gamebutton);
	void	(*m_pBtClickTower)(std::shared_ptr<BaseDefensive> tower);

	bool	m_isHolding;
	bool	m_isHandled;

};
