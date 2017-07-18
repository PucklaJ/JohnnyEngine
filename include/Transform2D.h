#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>

namespace Johnny
{
	class Transform2D
	{
	public:
		Transform2D();
		Transform2D(const glm::vec2&, const GLfloat&, const glm::vec2&);
		~Transform2D();

		const glm::vec2& getTranslation() const { return m_translation; }
		const GLfloat& getRotation() const { return m_rotation; }
		const glm::vec2& getScale() const { return m_scale; }

		void setTranslation(const glm::vec2& translation) { m_translation = translation; }
		void setRotation(const GLfloat& rotation) { m_rotation = rotation; }
		void setScale(const glm::vec2& scale) { m_scale = scale; }

		void setTranslation(const GLfloat& transX,const GLfloat& transY) { m_translation = glm::vec2(transX,transY); }
		void setScale(const GLfloat& scaleX,const GLfloat& scaleY) { m_scale = glm::vec2(scaleX,scaleY); }
	private:
		glm::vec2 m_translation;
		GLfloat m_rotation;
		glm::vec2 m_scale;
	};
}