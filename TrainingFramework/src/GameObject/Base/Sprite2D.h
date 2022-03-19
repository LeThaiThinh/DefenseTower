#pragma once
#include "BaseObject.h"

class Sprite2D : public BaseObject
{
protected:
	GLint		m_iWidth;
	GLint		m_iHeight;
	int			m_width;
	int			m_height;
	Vector3		m_centerPosition;
	GLuint		m_vboId;
	int			m_static_x;
	int			m_static_y;

public:
	Sprite2D() : BaseObject(), m_iWidth(0), m_iHeight(0), m_vboId(0), m_height(0), m_width(0), m_centerPosition(Vector3(0, 0, 0)),m_static_x(0),m_static_y(0) {}
	Sprite2D(GLint id, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
	Sprite2D(GLint id, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, Vector4 color);
	Sprite2D(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
	Sprite2D(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int iwidth, int iheight);
	Sprite2D(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, float x, float y, int iwidth, int iheight, int width, int height);
	~Sprite2D();

	void		Init() override;
	void		Draw() override;
	void		Update(GLfloat deltatime) override;

	void		Set2DPosition(GLfloat x, GLfloat y);
	void		Set2DStaticPosition(GLfloat x, GLfloat y);
	void		Set2DStaticPosition();
	void		Set2DPosition(Vector2 position);
	void		SetISize(GLint width, GLint height);
	int			GetIWidth() { return m_iWidth; }
	int			GetIHeight() { return m_iHeight; }
	void		SetSize(GLint width, GLint height);
	int			GetWidth() { return m_width; }
	int			GetHeight() { return m_height; }
	Vector3		GetCenterPosition() { return m_centerPosition; }
	Vector3		GetLeftTop() { return Vector3(m_centerPosition.x - m_width / 2.f, m_centerPosition.y - m_height / 2.f, 0); }
	Vector3		GetRightTop() { return Vector3(m_centerPosition.x + m_width / 2.f, m_centerPosition.y - m_height / 2.f, 0); }
	Vector3		GetLeftBottom() { return Vector3(m_centerPosition.x - m_width / 2.f, m_centerPosition.y + m_height / 2.f, 0); }
	Vector3		GetRightBottom() { return Vector3(m_centerPosition.x + m_width / 2.f, m_centerPosition.y + m_height / 2.f, 0); }

};

