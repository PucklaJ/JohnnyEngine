#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include "../include/Actor.h"
#include "../include/Matrix4.h"
#include "../include/Transform3D.h"
#include "Vector3.h"

namespace Johnny
{
	class Camera3D : public Actor, public TransformableObject3D
	{
	public:
		Camera3D();
		~Camera3D();

		Matrix4f getViewMatrix() const;
		const Vector3f& getLookDirection() const { return m_lookDirection; }

		void setLookDirection(const Vector3f& look) { m_lookDirection = look; }
		void setLookDirection(GLfloat x, GLfloat y, GLfloat z) { m_lookDirection = Vector3f(x, y, z); }
		void setRotation(const Vector3f& v) override { setRotation(v.x, v.y, v.z); }
		void setRotation(GLfloat, GLfloat, GLfloat) override;

		void addPosition(const Vector3f& pos) override { addPosition(pos, false); }
		void addPosition(GLfloat x, GLfloat y, GLfloat z) override { addPosition(Vector3f(x, y, z)); }
		void addPosition(const Vector3f&, bool);
		void addPosition(GLfloat x, GLfloat y, GLfloat z, bool);

		bool update() { return true; }
	private:
		Vector3f m_lookDirection;
		Vector3f m_up;

	};
}



#endif
