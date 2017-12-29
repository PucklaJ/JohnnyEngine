#include "../include/Transform3D.h"
#include "../include/Camera3D.h"
#include "../include/mathematics.h"

namespace Johnny
{
	/*GLfloat Transform3D::zFar;
	GLfloat Transform3D::zNear;
	GLfloat Transform3D::width;
	GLfloat Transform3D::height;
	GLfloat Transform3D::fov;*/

	Matrix4f Transform3D::m_projectionMatrix = Matrix4f::identity();

	void Transform3D::setProjection(const Matrix4f& projectionMatrix)
	{
		m_projectionMatrix = projectionMatrix;
	}

	Matrix4f Transform3D::getProjectionMatrix()
	{
		return m_projectionMatrix;
	}

	Transform3D::Transform3D() :
        m_translation(0.0f,0.0f,0.0f),
        m_rotation(0.0f,0.0f,0.0f),
        m_scale(1.0f,1.0f,1.0f)
	{
		
	}


	Transform3D::~Transform3D()
	{
	}

	void Transform3D::setTranslation(const Vector3f& vec)
	{
		m_translation = vec;
	}

	void Transform3D::setTranslation(GLfloat x, GLfloat y, GLfloat z)
	{
		setTranslation(Vector3f(x,y,z));
	}

	Matrix4f Transform3D::getTransformation() const
	{
		return Matrix4f::translate(m_translation) * (Matrix4f::rotate(m_rotation.y,Vector3f(0.0f,1.0f,0.0f))*
                                                                      Matrix4f::rotate(m_rotation.x,Vector3f(1.0f,0.0f,0.0f))*
                                                                      Matrix4f::rotate(m_rotation.z,Vector3f(0.0f,0.0f,-1.0f)))*
               Matrix4f::scale(m_scale);
	}

	Matrix4f Transform3D::getProjectedTransformation(const Camera3D* cam) const
	{
		if (cam == nullptr)
			return getProjectionMatrix()*getTransformation();
		else
        {
            return getProjectionMatrix()*cam->getViewMatrix()*getTransformation();
        }
			
	}

	void Transform3D::setRotation(const Vector3f& vec)
	{
		m_rotation = vec;
	}

	void Transform3D::setRotation(GLfloat x, GLfloat y, GLfloat z)
	{
		setRotation(Vector3f(x,y,z));
	}

	void Transform3D::setScale(const Vector3f& vec)
	{
		m_scale = vec;
	}

	void Transform3D::setScale(GLfloat x, GLfloat y, GLfloat z)
	{
		setScale(Vector3f(x,y,z));
	}

	TransformableObject3D::TransformableObject3D()
	{
	}

	TransformableObject3D::~TransformableObject3D()
	{
	}

	void TransformableObject3D::setRotation(GLfloat x, GLfloat y, GLfloat z)
	{
		setRotation(Vector3f(x, y, z));
	}

	void TransformableObject3D::addPosition(const Vector3f& pos)
	{
		m_transform.setTranslation(m_transform.getTranslation() + pos);
	}

	void TransformableObject3D::addPosition(GLfloat x, GLfloat y, GLfloat z)
	{
		addPosition(Vector3f(x, y, z));
	}

	void TransformableObject3D::setScale(GLfloat x, GLfloat y, GLfloat z)
	{
		m_transform.setScale(x, y, z);
	}

	Matrix4f TransformableObject3D::getTransformation() const
	{
		return m_transform.getTransformation();
	}

	Matrix4f TransformableObject3D::getProjectedTransformation(const Camera3D* cam) const
	{
		return m_transform.getProjectedTransformation(cam);
	}

}
