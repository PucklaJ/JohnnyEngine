#pragma once
#include "../include/mathematics_functions.h"
#include <GL/glew.h>
#include <cmath>
#include <iostream>

namespace Johnny {
template <class T> class Vector2;
template <class T>
const Vector2<T> operator+(const Vector2<T> &, const Vector2<T> &);
template <class T>
const Vector2<T> operator-(const Vector2<T> &, const Vector2<T> &);
template <class T>
const Vector2<T> operator*(const Vector2<T> &, const Vector2<T> &);
template <class T> const Vector2<T> operator*(const Vector2<T> &, const T &);
template <class T>
const Vector2<T> operator/(const Vector2<T> &, const Vector2<T> &);
template <class T> const Vector2<T> operator/(const Vector2<T> &, const T &);
template <class T> std::ostream &operator<<(std::ostream &, const Vector2<T> &);

/*! \brief A class which represents a value with two dimensions
 *  \param T The type of the elements of the Vector2
 */
template <class T> class Vector2 {
public:
  Vector2() = default;
  /*! \brief Creates a new Vector2
   *  \param x The x value of the new Vector2
   *  \param y The y value of the new Vector2
   */
  Vector2(const T &x, const T &y);
  /*! \brief Copies a Vector2
   *  \param v The Vector2 to copy
   */
  Vector2(const Vector2 &v);

  union {
    T x = 0; //!< The x value of the Vector2 if it is used as a position
    T r;     //!< The x value of the Vector2 if it is used as a color
    T width; //!< The x value of the Vector2 if it is used as dimensions
  };

  union {
    T y = 0;  //!< The y value of the Vector2 if it is used as a position
    T g;      //!< The y value of the Vector2 if it is used as a color
    T height; //!< The y value of the Vector2 if it is used as dimensions
  };

  /*! \param squared Wether the result should be the squared length or not
   *  \return The length of the Vector2
   */
  T length(bool squared = false) const;
  /*! \brief Normalises a Vector2
   *  \return A reference to this object
   */
  Vector2 &normalise();

  /*! \brief Adds a Vector2 to this object
   *  \param v The Vector2 to add
   *  \return A reference to this object
   */
  Vector2 &add(const Vector2 &v);
  /*! \brief Subtracts a Vector2 from this object
   *  \param v The Vector2 to subtract
   *  \return A refreence to this object
   */
  Vector2 &subtract(const Vector2 &v);
  /*! \brief Multiplies each element of the Vector2 which each other
   *  \param v The Vector2 for the multiplication
   *  \return A reference to this object
   */
  Vector2 &multiply(const Vector2 &v);
  /*! \brief Multiplies this vector with a scalar
   *  \param s The scalar to multiply
   *  \return A reference to the object
   */
  Vector2 &multiply(const T &s);
  /*! \brief Divides each element of the Vector2 by the corresponding element of
   * the other Vector2 \param v The other Vector2 for the division \return A
   * reference to the object
   */
  Vector2 &divide(const Vector2 &v);
  /*! \brief Divides each element by a scalar
   *  \param s The scalar for the division
   *  \return A reference to the object
   */
  Vector2 &divide(const T &s);

  /*! \return The angle between the positive x-Axis and the Vector2
   *
   */
  T angle() const;

  /*! \brief Calculates the dot product with this Vector2 and another one
   *  \param v The other Vector2 of the dot product
   *  \return The calculated dot product
   */
  T dot(const Vector2 &v) const;
  /*! \brief Calculates the distance between this Vector2 and another Vector2
   *  \param v The other Vector2 for the calculation
   *  \param squared Wether the result should be the squared distance
   *  \return The distance between this Vector2 and the other Vector2
   */
  T distance(const Vector2 &v, bool squared = false) const;

  Vector2 &operator+=(const Vector2 &);
  Vector2 &operator-=(const Vector2 &);
  Vector2 &operator*=(const Vector2 &);
  Vector2 &operator/=(const Vector2 &);

  Vector2 &operator*=(const T &);
  Vector2 &operator/=(const T &);

  friend const Vector2<T> operator+<>(const Vector2<T> &, const Vector2<T> &);
  friend const Vector2<T> operator-<>(const Vector2<T> &, const Vector2<T> &);
  friend const Vector2<T> operator*<>(const Vector2<T> &, const Vector2<T> &);
  friend const Vector2<T> operator*<>(const Vector2<T> &, const T &);
  friend const Vector2<T> operator/<>(const Vector2<T> &, const Vector2<T> &);
  friend const Vector2<T> operator/<>(const Vector2<T> &, const T &);

  friend std::ostream &operator<<<>(std::ostream &, const Vector2<T> &);
};

template <class T> Vector2<T>::Vector2(const T &x, const T &y) {
  this->x = x;
  this->y = y;
}
template <class T> Vector2<T>::Vector2(const Vector2<T> &v) {
  x = v.x;
  y = v.y;
}
template <class T> T Vector2<T>::length(bool squared) const {
  if (squared)
    return x * x + y * y;
  else
    return sqrt(x * x + y * y);
}
template <class T> Vector2<T> &Vector2<T>::normalise() {
  T Length = length();

  x /= Length;
  y /= Length;

  return *this;
}
template <class T> Vector2<T> &Vector2<T>::add(const Vector2<T> &v) {
  x += v.x;
  y += v.y;

  return *this;
}
template <class T> Vector2<T> &Vector2<T>::subtract(const Vector2<T> &v) {
  x -= v.x;
  y -= v.y;

  return *this;
}
template <class T> Vector2<T> &Vector2<T>::multiply(const Vector2<T> &v) {
  x *= v.x;
  y *= v.y;

  return *this;
}
template <class T> Vector2<T> &Vector2<T>::multiply(const T &s) {
  x *= s;
  y *= s;

  return *this;
}
template <class T> Vector2<T> &Vector2<T>::divide(const Vector2<T> &v) {
  x /= v.x;
  y /= v.y;

  return *this;
}
template <class T> Vector2<T> &Vector2<T>::divide(const T &s) {
  x /= s;
  y /= s;

  return *this;
}
template <class T> T Vector2<T>::angle() const {
  T _angle = -(T)toDegrees(atan2(y, x));

  if (_angle < (T)0 && _angle > (T)-180) {
    _angle = (T)360 + _angle;
  }

  return _angle;
}
template <class T> T Vector2<T>::dot(const Vector2<T> &v) const {
  return x * v.x + y * v.y;
}
template <class T>
T Vector2<T>::distance(const Vector2<T> &v, bool squared) const {
  Vector2<T> v1(v);

  v1.subtract(*this);

  return v1.length(squared);
}
template <class T> Vector2<T> &Vector2<T>::operator+=(const Vector2<T> &v2) {
  return add(v2);
}
template <class T> Vector2<T> &Vector2<T>::operator-=(const Vector2<T> &v2) {
  return subtract(v2);
}
template <class T> Vector2<T> &Vector2<T>::operator*=(const Vector2<T> &v2) {
  return multiply(v2);
}
template <class T> Vector2<T> &Vector2<T>::operator/=(const Vector2<T> &v2) {
  return divide(v2);
}
template <class T> Vector2<T> &Vector2<T>::operator*=(const T &s) {
  x *= s;
  y *= s;

  return *this;
}
template <class T> Vector2<T> &Vector2<T>::operator/=(const T &s) {
  x /= s;
  y /= s;

  return *this;
}
template <class T>
const Vector2<T> operator+(const Vector2<T> &v1, const Vector2<T> &v2) {
  return Vector2<T>(v1).add(v2);
}
template <class T>
const Vector2<T> operator-(const Vector2<T> &v1, const Vector2<T> &v2) {
  return Vector2<T>(v1).subtract(v2);
}
template <class T>
const Vector2<T> operator*(const Vector2<T> &v1, const Vector2<T> &v2) {
  return Vector2<T>(v1).multiply(v2);
}
template <class T> const Vector2<T> operator*(const Vector2<T> &v, const T &s) {
  return Vector2<T>(v).multiply(s);
}
template <class T>
const Vector2<T> operator/(const Vector2<T> &v1, const Vector2<T> &v2) {
  return Vector2<T>(v1).divide(v2);
}
template <class T> const Vector2<T> operator/(const Vector2<T> &v, const T &s) {
  return Vector2<T>(v).divide(s);
}
template <class T>
std::ostream &operator<<(std::ostream &os, const Vector2<T> &v) {
  os << "(" << v.x << ";" << v.y << ")";
  return os;
}

typedef Vector2<GLfloat> Vector2f;
typedef Vector2<GLdouble> Vector2d;
typedef Vector2<GLint> Vector2i;
} // namespace Johnny
