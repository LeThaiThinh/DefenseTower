#pragma once
#include "../GameObject/AttackAble.h"
#include "../GameObject/AbleToAttack.h"
#include <GameButton.h>
enum class TowerType
{
	Spot,
	Main,
	One,
	Two,
	Three,
	Four,
	Five
};
class TowerOption;
class BaseTower:
	public AbleToAttack,
	public Sprite2D
{
public:
	BaseTower():AbleToAttack(),Sprite2D(), m_level(0),m_disposable(false){}
	BaseTower(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, float x, float y, float width, float height, float range, float attackSpeed,int level)
		:Sprite2D(model, shader, texture,x,y,  width,  height), AbleToAttack(range, attackSpeed), m_level(level), m_disposable(false) {}
	~BaseTower(){}

	virtual void	Attack() = 0;
	virtual void	Update(GLfloat deltatime)=0 ;
	bool IsDisposable(){ return m_disposable; }
	void SetDisposable(bool disposable) { m_disposable= disposable; }
	void Upgrade() { m_level++; }

protected:
	bool m_disposable;
	int m_level;
	std::shared_ptr<TowerOption> m_towerOption;
};
