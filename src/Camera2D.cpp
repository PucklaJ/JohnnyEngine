#include "../include/Camera2D.h"
#include <iostream>
#include "../include/MainClass.h"

namespace Johnny
{
	Camera2D::Camera2D()
	{
		m_affectedByCenter = false;
	}

	Matrix3f Camera2D::getViewMatrix() const
	{
		return Matrix3f::camera(m_transform.getTranslation(), m_transform.getScale().x, m_transform.getRotation());
	}

	void Camera2D::setZoom(GLfloat s)
	{
		setScale(s, 1.0f);
	}

	void Camera2D::addPosition(const Vector2f & pos, bool relToLook)
	{
		setPosition(getPosition() + (relToLook ? Matrix3f::rotate(m_transform.getRotation())*pos : pos));
	}

	void Camera2D::addPosition(GLfloat x, GLfloat y, bool relToLook)
	{
		addPosition(Vector2f(x,y),relToLook);
	}
	void Camera2D::addZoom(GLfloat x)
	{
		setZoom(getZoom() + x);
	}
	void Camera2D::setPosition(const Vector2f& pos)
	{
		Vector2f pos1(pos);
		pos1 -= MainClass::getInstance()->getNativeRes() / 2.0f;
		pos1.y = -pos1.y;
		m_transform.setTranslation(pos1);
	}

	Vector2f Camera2D::getPosition() const
	{
		Vector2f pos1(m_transform.getTranslation());
		pos1.y = -pos1.y;
		pos1 += MainClass::getInstance()->getNativeRes() / 2.0f;

		return pos1;
	}
}


