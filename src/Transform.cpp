#include "Transform.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"
#define MATH_PI 3.14159265f

float Transform::zFar;
float Transform::zNear;
float Transform::width;
float Transform::height;
float Transform::fov;

void Transform::setProjection(float fov, float width, float height, float zNear, float zFar)
{
	Transform::fov = fov;
	Transform::width = width;
	Transform::height = height;
	Transform::zNear = zNear;
	Transform::zFar = zFar;
}

glm::mat4 Transform::getProjectionMatrix()
{
	return glm::perspective(fov, width / height, zNear, zFar);
}

Transform::Transform()
{
	m_translation = glm::vec3(0.0f,0.0f,0.0f);
	m_rotation = glm::vec3(0.0f,0.0f,0.0f);
	m_scale = glm::vec3(1.0f,1.0f,1.0f);
}


Transform::~Transform()
{
}

void Transform::setTranslation(const glm::vec3 & vec)
{
	m_translation = vec;
}

void Transform::setTranslation(float x, float y, float z)
{
	m_translation = glm::vec3(x,y,z);
}

glm::mat4 Transform::getTransformation() const
{
	glm::mat4 translationMatrix;
	glm::mat4 rotationMatrix;
	glm::mat4 scaleMatrix;

	/*float m[16];

	m[0] = 1;	m[1] = 0; m[2] = 0; m[3] = m_translation.x;
	m[4] = 0;	m[5] = 1; m[6] = 0; m[7] = m_translation.y;
	m[8] = 0;	m[9] = 0; m[10] = 1; m[11] = m_translation.z;
	m[12] = 0;	m[13] = 0; m[14] = 0; m[15] = 1;

	translationMatrix = glm::make_mat4(m);*/

	glm::mat4 rxm, rym, rzm;

	float x = m_rotation.x;
	float y = m_rotation.y;
	float z = m_rotation.z;

	x = x / 180.0f * MATH_PI;
	y = y / 180.0f * MATH_PI;
	z = z / 180.0f * MATH_PI;

	float rx[16],ry[16],rz[16];

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

	rotationMatrix = rzm * rym * rxm;

	/*float sx = m_scale.x;
	float sy = m_scale.y;
	float sz = m_scale.z;

	float s[16];

	s[0] = sx;	s[1] = 0; s[2] = 0; s[3] = 0;
	s[4] = 0;	s[5] = sy; s[6] = 0; s[7] = 0;
	s[8] = 0;	s[9] = 0; s[10] = sz; s[11] = 0;
	s[12] = 0;	s[13] = 0; s[14] = 0; s[15] = 1;

	scaleMatrix = glm::make_mat4(s);*/


	translationMatrix = glm::translate(glm::mat4(), m_translation);

	/*rotationMatrix = glm::rotate(glm::mat4(), m_rotation.x / 180.0f*MATH_PI, glm::vec3(1.0, 0.0, 0.0));
	rotationMatrix = glm::rotate(rotationMatrix, m_rotation.y/180.0f*MATH_PI, glm::vec3(0.0, 1.0, 0.0));
	rotationMatrix = glm::rotate(rotationMatrix, m_rotation.z / 180.0f*MATH_PI, glm::vec3(0.0, 0.0, 1.0));*/
	
	scaleMatrix = glm::scale(glm::mat4(),m_scale);

	return translationMatrix * rotationMatrix * scaleMatrix;
}

glm::mat4 Transform::getProjectedTransformation(Camera* cam) const
{
	glm::mat4 trans = getTransformation();
	glm::mat4 proj;

	float ar = width / height;

	/*float tanHalfFov = (float)tan(fov / 180.0f*MATH_PI / 2.0f);
	float zRange = zNear - zFar;

	float pr[16];

	pr[0] = 1.0f / (tanHalfFov * ar);	pr[1] = 0; 				   pr[2] = 0; 					  pr[3] = 0;
	pr[4] = 0;							pr[5] = 1.0f / tanHalfFov; pr[6] = 0; 					  pr[7] = 0;
	pr[8] = 0;							pr[9] = 0; 				   pr[10] = (-zNear - zFar) / zRange; pr[11] = 2.0f * zFar * zNear / zRange;
	pr[12] = 0;							pr[13] = 0; 			   pr[14] = 1; 					  pr[15] = 0;

	proj = glm::make_mat4(pr);*/

	proj = glm::perspective(fov / 180.0f * MATH_PI, ar, zNear, zFar);

	if (cam == nullptr)
		return proj*trans;
	else
		return proj*cam->getViewMatrix()*trans;
}

void Transform::setRotation(const glm::vec3 & vec)
{
	m_rotation = vec;
}

void Transform::setRotation(float x, float y, float z)
{
	m_rotation = glm::vec3(x, y, z);
}

void Transform::setScale(const glm::vec3 & vec)
{
	m_scale = vec;
}

void Transform::setScale(float x, float y, float z)
{
	m_scale = glm::vec3(x, y, z);
}
