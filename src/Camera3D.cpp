#include "../include/Camera3D.h"
#include <iostream>
#ifndef M_PI
#define M_PI 3.14159265f
#endif

namespace Johnny {
Camera3D::Camera3D()
    : m_lookDirection(0.0f, 0.0f, -1.0f), m_up(0.0f, 1.0f, 0.0f) {
  m_castsShadows3D = false;
}

Camera3D::~Camera3D() {}

Matrix4f Camera3D::getViewMatrix() const {
  return Matrix4f::lookAt(m_transform.getTranslation(),
                          m_transform.getTranslation() + m_lookDirection, m_up);
}

void Camera3D::setRotation(GLfloat x, GLfloat y, GLfloat z) {
  x = clamp(x, -89.0f, 89.0f);

  m_transform.setRotation(x, y, z);

  m_lookDirection = Matrix4f::rotate(y, Vector3f(0.0f, 1.0f, 0.0f)) *
                    Matrix4f::rotate(x, Vector3f(1.0f, 0.0f, 0.0f)) *
                    Vector4f(0.0f, 0.0f, -1.0f, 1.0f);

  m_up = Matrix4f::rotate(z, Vector3f(0.0f, 0.0f, -1.0f)) *
         Vector4f(0.0f, 1.0f, 0.0f, 1.0f);
}

void Camera3D::addPosition(const Vector3f &pos, bool relToLook) {
  if (relToLook == false)
    m_transform.setTranslation(m_transform.getTranslation() + pos);
  else {
    Vector3f normLook = m_lookDirection.normaliseConst();
    Vector3f moveVec = normLook;

    m_transform.setTranslation(m_transform.getTranslation() + moveVec * -pos.z);

    moveVec = Vector3f(0.0f, -1.0f, 0.0f).cross(normLook).normalise();

    m_transform.setTranslation(m_transform.getTranslation() + moveVec * pos.x);

    moveVec = Vector3f(1.0f, 0.0f, 0.0f).cross(normLook).normalise();

    m_transform.setTranslation(m_transform.getTranslation() + moveVec * pos.y);
  }
}

void Camera3D::addPosition(GLfloat x, GLfloat y, GLfloat z, bool relToLook) {
  addPosition(Vector3f(x, y, z), relToLook);
}

} // namespace Johnny
