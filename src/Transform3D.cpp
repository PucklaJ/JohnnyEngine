#include "../include/Transform3D.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
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
		/*glm::mat4 rxm, rym, rzm;

		float x = m_rotation.x;
		float y = m_rotation.y;
		float z = m_rotation.z;

		x = x / 180.0f * M_PI;
		y = y / 180.0f * M_PI;
		z = z / 180.0f * M_PI;

		float rx[16], ry[16], rz[16];

		rx[0] = cos(z);	rx[1] = -sin(z); rx[2] = 0; rx[3] = 0;
		rx[4] = sin(z);	rx[5] = cos(z); rx[6] = 0; rx[7] = 0;
		rx[8] = 0;	rx[9] = 0; rx[10] = 1; rx[11] = 0;
		rx[12] = 0;	rx[13] = 0; rx[14] = 0; rx[15] = 1;

		ry[0] = 1;	ry[1] = 0; ry[2] = 0; ry[3] = 0;
		ry[4] = 0;	ry[5] = cos(x); ry[6] = -sin(x); ry[7] = 0;
		ry[8] = 0;	ry[9] = sin(x); ry[10] = cos(x); ry[11] = 0;
		ry[12] = 0;	ry[13] = 0; ry[14] = 0; ry[15] = 1;

		rz[0] = cos(y);	rz[1] = 0; rz[2] = -sin(y); rz[3] = 0;
		rz[4] = 0;	rz[5] = 1; rz[6] = 0; rz[7] = 0;
		rz[8] = sin(y);	rz[9] = 0; rz[10] = cos(y); rz[11] = 0;
		rz[12] = 0;	rz[13] = 0; rz[14] = 0; rz[15] = 1;

		rxm = glm::make_mat4(rx);
		rym = glm::make_mat4(ry);
		rzm = glm::make_mat4(rz);

		rotationMatrix = rzm * rym * rxm;*/

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
