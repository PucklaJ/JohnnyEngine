#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include "../include/Actor.h"
#include "../include/Matrix4.h"
#include "Vector3.h"

namespace Johnny
{
	class Camera3D : public Johnny::Actor
	{
	public:
		Camera3D();
		~Camera3D();

		Matrix4f getViewMatrix() const;
		const Vector3f& getPosition() const { return m_transform.getTranslation(); }
		const Vector3f& getLookDirection() const { return m_lookDirection; }
		const Vector3f& getRotation() const { return m_transform.getRotation(); }
		Transform3D& getTransform() { return m_transform; }

		void setPosition(const Vector3f& pos) { m_transform.setTranslation(pos); }
		void setPosition(GLfloat x, GLfloat y, GLfloat z) { m_transform.setTranslation(x, y, z); }
		void setLookDirection(const Vector3f& look) { m_lookDirection = look; }
		void setLookDirection(GLfloat x, GLfloat y, GLfloat z) { m_lookDirection = Vector3f(x, y, z); }
		void setRotation(GLfloat, GLfloat, GLfloat);

		void addPosition(const Vector3f& pos, bool relToLook = false);
		void addPosition(GLfloat x, GLfloat y, GLfloat z, bool relToLook = false);
		void addRotation(GLfloat x, GLfloat y, GLfloat z) { setRotation(m_transform.getRotation().x + x, m_transform.getRotation().y + y, m_transform.getRotation().z + z); }

		bool update() { return true; }

	private:
		Transform3D m_transform;
		Vector3f m_lookDirection;
		Vector3f m_up;

	};
}



#endif
