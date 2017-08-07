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

		Matrix4f getProjectedTransformation(const Camera3D* cam = nullptr) const;

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

	class TransformableObject3D
	{
	public:
		TransformableObject3D();
		virtual ~TransformableObject3D();

		virtual const Vector3f& getPosition() const { return m_transform.getTranslation(); }
		virtual const Vector3f& getRotation() const { return m_transform.getRotation(); }
		virtual const Vector3f& getScale() const { return m_transform.getScale(); }
		 
		virtual void setPosition(const Vector3f& pos) { m_transform.setTranslation(pos); }
		virtual void setPosition(GLfloat x, GLfloat y, GLfloat z) { m_transform.setTranslation(x, y, z); }
		virtual void setRotation(const Vector3f& rot) { m_transform.setRotation(rot); }
		virtual void setRotation(GLfloat, GLfloat, GLfloat);
		 
		virtual void addPosition(const Vector3f& pos);
		virtual void addPosition(GLfloat x, GLfloat y, GLfloat z);
		virtual void addRotation(const Vector3f& v) { addRotation(v.x, v.y, v.z); }
		virtual void addRotation(GLfloat x, GLfloat y, GLfloat z) { setRotation(m_transform.getRotation().x + x, m_transform.getRotation().y + y, m_transform.getRotation().z + z); }

		Matrix4f getTransformation() const;
		Matrix4f getProjectedTransformation(const Camera3D* cam = nullptr) const;

		Transform3D& getTransform() { return m_transform; }

	protected:
		Transform3D m_transform;
	};
}
