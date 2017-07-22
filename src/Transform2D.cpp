#include "../include/Transform2D.h"
#include "../include/Camera2D.h"

namespace Johnny
{
	Transform2D::Transform2D() :
		m_translation(0.0f, 0.0f),
		m_rotation(0.0f),
		m_scale(1.0f, 1.0f)
	{

	}

	Transform2D::Transform2D(const Vector2f& translation, const GLfloat& rotation, const Vector2f& scale) :
		m_translation(translation),
		m_rotation(rotation),
		m_scale(scale)
	{

	}

	Transform2D::~Transform2D()
	{

	}

	Matrix3f Transform2D::getTransformation() const
	{
		return Matrix3f::translate(m_translation) * Matrix3f::rotate(m_rotation) * Matrix3f::scale(m_scale);//Matrix3f::identity();
	}

	Matrix3f Transform2D::getProjectedTransformation(const Camera2D* cam) const
	{
		return cam->getViewMatrix() * getTransformation();
	}
}
