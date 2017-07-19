#include "../include/Camera3D.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#ifndef M_PI
	#define M_PI 3.14159265f
#endif


namespace Johnny
{
	Camera3D::Camera3D() :
		m_lookDirection(0.0, 0.0, -1.0),
		m_up(0.0, 1.0, 0.0)
	{
		m_castsShadows = false;
	}


	Camera3D::~Camera3D()
	{
	}

	glm::mat4 Camera3D::getViewMatrix() const
	{
		return glm::lookAt(m_transform.getTranslation(), m_transform.getTranslation() + m_lookDirection, m_up);
	}

	void Camera3D::setRotation(GLfloat x, GLfloat y, GLfloat z)
	{
		x = glm::clamp(x, -89.0f, 89.0f);

		m_transform.setRotation(x, y, z);
		m_lookDirection = glm::vec3((glm::rotate(glm::rotate(glm::mat4(),y / 180.0f * (GLfloat)M_PI,glm::vec3(0.0, 1.0, 0.0)),x / 180.0f * (GLfloat)M_PI,glm::vec3(1.0, 0.0, 0.0))) * glm::vec4(0.0, 0.0, -1.0, 1.0));

		m_up = glm::vec3(glm::rotate(glm::mat4(),z / 180.0f * (GLfloat)M_PI, glm::vec3(0.0, 0.0, -1.0)) * glm::vec4(0.0, 1.0, 0.0, 1.0));
	}

	void Camera3D::addPosition(const glm::vec3 & pos, bool relToLook)
	{
		if (relToLook == false)
			m_transform.setTranslation(m_transform.getTranslation() + pos);
		else
		{
			glm::vec3 normLook = glm::normalize(m_lookDirection);
			glm::vec3 moveVec = normLook;

			m_transform.setTranslation(m_transform.getTranslation() + moveVec * -pos.z);

			moveVec = glm::normalize(glm::cross(glm::vec3(0.0, -1.0, 0.0), normLook));

			m_transform.setTranslation(m_transform.getTranslation() + moveVec * pos.x);

			moveVec = glm::normalize(glm::cross(glm::vec3(1.0, 0.0, 0.0), normLook));

			m_transform.setTranslation(m_transform.getTranslation() + moveVec * pos.y);
		}
	}

	void Camera3D::addPosition(GLfloat x, GLfloat y, GLfloat z, bool relToLook)
	{
		addPosition(glm::vec3(x, y, z), relToLook);
	}

}
