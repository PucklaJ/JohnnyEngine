#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <GL\glew.h>
#include "Actor.h"

namespace Johnny
{
	class Camera3D : public Johnny::Actor
	{
	public:
		Camera3D();
		~Camera3D();

		glm::mat4 getViewMatrix() const;
		const glm::vec3& getPosition() const { return m_transform.getTranslation(); }
		const glm::vec3& getLookDirection() const { return m_lookDirection; }
		const glm::vec3& getRotation() const { return m_transform.getRotation(); }
		Transform3D& getTransform() { return m_transform; }

		void setPosition(const glm::vec3& pos) { m_transform.setTranslation(pos); }
		void setPosition(GLfloat x, GLfloat y, GLfloat z) { m_transform.setTranslation(x, y, z); }
		void setLookDirection(const glm::vec3& look) { m_lookDirection = look; }
		void setLookDirection(GLfloat x, GLfloat y, GLfloat z) { m_lookDirection = glm::vec3(x, y, z); }
		void setRotation(GLfloat, GLfloat, GLfloat);

		void addPosition(const glm::vec3& pos, bool relToLook = false);
		void addPosition(GLfloat x, GLfloat y, GLfloat z, bool relToLook = false);
		void addRotation(GLfloat x, GLfloat y, GLfloat z) { setRotation(m_transform.getRotation().x + x, m_transform.getRotation().y + y, m_transform.getRotation().z + z); }

		bool update() { return true; }

	private:
		Transform3D m_transform;
		glm::vec3 m_lookDirection;
		glm::vec3 m_up;

	};
}



#endif

