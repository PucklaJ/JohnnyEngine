#pragma once
#include "Transform2D.h"
#include "Vector2.h"
#include "Matrix3.h"

namespace Johnny
{
	class Camera2D : public TransformableObject2D
	{
	public:
		Camera2D();

		Matrix3f getViewMatrix() const;
		const GLfloat& getZoom() const { return m_transform.getScale().x; }

		void setZoom(GLfloat);

		void addPosition(const Vector2f& pos,bool relToLook = false);
		void addPosition(GLfloat x, GLfloat y,bool relToLook = false);
		void addZoom(GLfloat);
	};
}