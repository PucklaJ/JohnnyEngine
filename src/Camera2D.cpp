#include "..\include\Camera2D.h"
#include <iostream>

namespace Johnny
{
	Camera2D::Camera2D()
	{
		
	}

	Camera2D::~Camera2D()
	{
		
	}

	Matrix3f Camera2D::getViewMatrix() const
	{
		return Matrix3f::camera(m_transform.getTranslation(), m_transform.getScale().x, m_transform.getRotation());
	}

	void Camera2D::setRotation(GLfloat x)
	{
		m_transform.setRotation(x);
	}

	void Camera2D::setScale(GLfloat s)
	{
		m_transform.setScale(s, 1.0f);
	}

	void Camera2D::addPosition(const Vector2f & pos, bool relToLook)
	{
		m_transform.setTranslation(m_transform.getTranslation() + (relToLook ? Matrix3f::rotate(-m_transform.getRotation())*pos : pos));
	}

	void Camera2D::addPosition(GLfloat x, GLfloat y, bool relToLook)
	{
		addPosition(Vector2f(x,y),relToLook);
	}
	void Camera2D::addScale(GLfloat x)
	{
		setScale(getScale() + x);
	}
}


