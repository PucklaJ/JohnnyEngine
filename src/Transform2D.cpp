#include "../include/Transform2D.h"

namespace Johnny
{
	Transform2D::Transform2D() :
		m_translation(0.0f, 0.0f),
		m_rotation(0.0f),
		m_scale(1.0f, 1.0f)
	{

	}

	Transform2D::Transform2D(const glm::vec2& translation, const GLfloat& rotation, const glm::vec2& scale) :
		m_translation(translation),
		m_rotation(rotation),
		m_scale(scale)
	{

	}

	Transform2D::~Transform2D()
	{

	}
}
