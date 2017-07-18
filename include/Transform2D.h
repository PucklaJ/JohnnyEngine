#pragma once
#include "Vector2.h"
#include "Matrix3.h"
#include <GL/glew.h>

namespace Johnny
{
	class Transform2D
	{
	public:
		Transform2D();
		Transform2D(const Vector2f&, const GLfloat&, const Vector2f&);
		~Transform2D();

		const Vector2f& getTranslation() const { return m_translation; }
		const GLfloat& getRotation() const { return m_rotation; }
		const Vector2f& getScale() const { return m_scale; }

		void setTranslation(const Vector2f& translation) { m_translation = translation; }
		void setRotation(const GLfloat& rotation) { m_rotation = rotation; }
		void setScale(const Vector2f& scale) { m_scale = scale; }

		void setTranslation(const GLfloat& transX,const GLfloat& transY) { m_translation = Vector2f(transX,transY); }
		void setScale(const GLfloat& scaleX,const GLfloat& scaleY) { m_scale = Vector2f(scaleX,scaleY); }

		Matrix3f getTransformation() const;
	private:
		Vector2f m_translation;
		GLfloat m_rotation;
		Vector2f m_scale;
	};
}