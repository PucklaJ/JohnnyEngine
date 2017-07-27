#pragma once
#include "Transform2D.h"
#include "Vector2.h"
#include "Matrix3.h"

namespace Johnny
{
	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		Matrix3f getViewMatrix() const;
		const Vector2f& getPosition() const { return m_transform.getTranslation(); }
		const GLfloat& getRotation() const { return m_transform.getRotation(); }
		const GLfloat& getScale() const { return m_transform.getScale().x; }
		Transform2D& getTransform() { return m_transform; }

		void setPosition(const Vector2f& pos) { m_transform.setTranslation(pos); }
		void setPosition(GLfloat x, GLfloat y) { m_transform.setTranslation(x, y); }
		void setRotation(GLfloat);
		void setScale(GLfloat);

		void addPosition(const Vector2f& pos,bool relToLook = false);
		void addPosition(GLfloat x, GLfloat y,bool relToLook = false);
		void addRotation(GLfloat x) { setRotation( m_transform.getRotation() + x); }
		void addScale(GLfloat);

		bool update() { return true; }

	private:
		Transform2D m_transform;

	};
}