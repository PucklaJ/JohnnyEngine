#pragma once
#include "Vector3.h"
#include "Matrix4.h"

namespace Johnny
{
	class Camera3D;

	class Transform3D
	{
	public:
		static Matrix4f getProjectionMatrix();

		Transform3D();
		~Transform3D();

		const Vector3f& getTranslation() const { return m_translation; }
		void setTranslation(const Vector3f&);
		void setTranslation(GLfloat, GLfloat, GLfloat);

		const Vector3f& getRotation() const { return m_rotation; }
		void setRotation(const Vector3f&);
		void setRotation(GLfloat, GLfloat, GLfloat);

		const Vector3f& getScale() const { return m_scale; }
		void setScale(const Vector3f&);
		void setScale(GLfloat, GLfloat, GLfloat);

		Matrix4f getTransformation() const;

		Matrix4f getProjectedTransformation(Camera3D* cam = nullptr) const;

		static void setProjection(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
		static GLfloat getNearPlane() { return zNear; }
		static GLfloat getFarPlane() { return zFar; }
		static GLfloat getFOV() { return fov; }

	private:
		static GLfloat zNear;
		static GLfloat zFar;
		static GLfloat width;
		static GLfloat height;
		static GLfloat fov;

		Vector3f m_translation;
		Vector3f m_rotation;
		Vector3f m_scale;
	};
}
