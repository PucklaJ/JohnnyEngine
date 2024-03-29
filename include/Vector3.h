#pragma once
#include "Vector4.h"
#include <GL/glew.h>
#include <cmath>
#include <iostream>

namespace Johnny {
template <class T> class Vector3;
template <class T> Vector3<T> operator+(const Vector3<T> &, const Vector3<T> &);
template <class T> Vector3<T> operator-(const Vector3<T> &, const Vector3<T> &);
template <class T> Vector3<T> operator*(const Vector3<T> &, const Vector3<T> &);
template <class T> Vector3<T> operator*(const Vector3<T> &, const T &);
template <class T> Vector3<T> operator/(const Vector3<T> &, const Vector3<T> &);
template <class T> Vector3<T> operator-(const Vector3<T> &);

template <class T> std::ostream &operator<<(std::ostream &, const Vector3<T> &);

/*! \brief A class which represents a value with three dimensions
 *  \param T The type of the elements of the Vector3
 */
template <class T> class Vector3 {
public:
  Vector3() = default;
  /*! \brief Creates a new Vector3
   *  \param x The x value of the new Vector3
   *  \param y The y value of the new Vector3
   *  \param z The z value of the new Vector3
   */
  Vector3(const T &x, const T &y, const T &z);
  /*! \brief Copies a Vector3
   *  \param v The Vector3 to copy
   */
  Vector3(const Vector3 &v);
  /*! \brief Converts a Vector4 to a Vector3
   *  \param v The Vector4 to convert
   *
   * It converts the Vector4 through dividing each element by the w component
   */
  Vector3(const Vector4<T> &v);

  union {
    T x = 0; //!< The x value of the Vector3 if it is used as a position
    T r;     //!< The x value of the Vector3 if it is used as a color
    T width; //!< The x value of the Vector3 if it is used as dimensions
  };

  union {
    T y = 0;  //!< The y value of the Vector3 if it is used as a position
    T g;      //!< The y value of the Vector3 if it is used as a color
    T height; //!< The y value of the Vector3 if it is used as dimensions
  };

  union {
    T z = 0; //!< The z value of the Vector3 if it is used as a position
    T b;     //!< The z value of the Vector3 if it is used as a color
    T depth; //!< The z value of the Vector3 if it is used as dimensions
  };

  /*! \param squared Wether the result should be the squared length or not
   *  \return The length of the Vector3
   */
  T length(bool squared = false) const;
  /*! \brief Normalises a Vector3
   *  \return A reference to this object
   */
  Vector3 &normalise();
  /*! \brief Normalises a Vector3
   *  \return The normalised Vector3
   *
   * It ismeant to be used when you want to normalise a temporary Vector3
   */
  Vector3 normaliseConst() const;

  /*! \brief Adds a Vector3 to this object
   *  \param v The Vector3 to add
   *  \return A reference to this object
   */
  Vector3 &add(const Vector3 &v);
  /*! \brief Subtracts a Vector3 from this object
   *  \param v The Vector3 to subtract
   *  \return A refreence to this object
   */
  Vector3 &subtract(const Vector3 &v);
  /*! \brief Multiplies each element of the Vector3 which each other
   *  \param v The Vector3 for the multiplication
   *  \return A reference to this object
   */
  Vector3 &multiply(const Vector3 &v);
  /*! \brief Multiplies this vector with a scalar
   *  \param s The scalar to multiply
   *  \return A reference to the object
   */
  Vector3 &multiply(const T &s);
  /*! \brief Divides each element of the Vector3 by the corresponding element of
   * the other Vector2 \param v The other Vector3 for the division \return A
   * reference to the object
   */
  Vector3 &divide(const Vector3 &v);
  /*! \brief Divides each element by a scalar
   *  \param s The scalar for the division
   *  \return A reference to the object
   */
  Vector3 &divide(const T &s);

  /*! \brief Calculates the cross product of this Vector3 and another Vector3
   *  \param v The other Vector3 for the cross product
   *  \return The cross product of this Vector3 and the other Vector3
   */
  Vector3 cross(const Vector3 &v);
  /*! \brief Calculates the dot product with this Vector3 and another one
   *  \param v The other Vector3 of the dot product
   *  \return The calculated dot product
   */
  T dot(const Vector3 &v);
  /*! \brief Calculates the distance between this Vector3 and another Vector3
   *  \param v The other Vector3 for the calculation
   *  \param squared Wether the result should be the squared distance
   *  \return The distance between this Vector3 and the other Vector3
   */
  T distance(const Vector3 &v, bool squared = false) const;

  Vector3 &operator+=(const Vector3 &);
  Vector3 &operator-=(const Vector3 &);
  Vector3 &operator*=(const Vector3 &);
  Vector3 &operator*=(const T &);
  Vector3 &operator/=(const Vector3 &);

  Vector3 &operator=(const Vector4<T> &);

  T &operator[](unsigned int);

  friend Vector3<T> operator+<>(const Vector3<T> &, const Vector3<T> &);
  friend Vector3<T> operator-<>(const Vector3<T> &, const Vector3<T> &);
  friend Vector3<T> operator*<>(const Vector3<T> &, const Vector3<T> &);
  friend Vector3<T> operator*<>(const Vector3<T> &, const T &);
  friend Vector3<T> operator/<>(const Vector3<T> &, const Vector3<T> &);
  friend Vector3<T> operator-<>(const Vector3<T> &);

  friend std::ostream &operator<<<>(std::ostream &, const Vector3<T> &);
};

template <class T> Vector3<T>::Vector3(const T &x, const T &y, const T &z) {
  this->x = x;
  this->y = y;
  this->z = z;
}
template <class T> Vector3<T>::Vector3(const Vector3 &v) {
  x = v.x;
  y = v.y;
  z = v.z;
}
template <class T> Vector3<T>::Vector3(const Vector4<T> &v) {
  x = v.x / v.w;
  y = v.y / v.w;
  z = v.z / v.w;
}

template <class T> T Vector3<T>::length(bool squared) const {
  if (squared)
    return x * x + y * y + z * z;
  else
    return sqrt(x * x + y * y + z * z);
}

template <class T> Vector3<T> &Vector3<T>::normalise() {
  T Length = length();

  x /= Length;
  y /= Length;
  z /= Length;

  return *this;
}
template <class T> Vector3<T> Vector3<T>::normaliseConst() const {
  return Vector3<T>(*this).normalise();
}

template <class T> Vector3<T> &Vector3<T>::add(const Vector3<T> &v) {
  x += v.x;
  y += v.y;
  z += v.z;

  return *this;
}
template <class T> Vector3<T> &Vector3<T>::subtract(const Vector3<T> &v) {
  x -= v.x;
  y -= v.y;
  z -= v.z;

  return *this;
}
template <class T> Vector3<T> &Vector3<T>::multiply(const Vector3<T> &v) {
  x *= v.x;
  y *= v.y;
  z *= v.z;

  return *this;
}
template <class T> Vector3<T> &Vector3<T>::multiply(const T &s) {
  x *= s;
  y *= s;
  z *= s;

  return *this;
}
template <class T> Vector3<T> &Vector3<T>::divide(const Vector3<T> &v) {
  x /= v.x;
  y /= v.y;
  z /= v.z;

  return *this;
}
template <class T> Vector3<T> &Vector3<T>::divide(const T &s) {
  x /= s;
  y /= s;
  z /= s;

  return *this;
}
template <class T> Vector3<T> Vector3<T>::cross(const Vector3<T> &v) {
  Vector3<T> v1(*this);

  v1.x = y * v.z - z * v.y;
  v1.y = z * v.x - x * v.z;
  v1.z = x * v.y - y * v.x;

  return v1;
}
template <class T> T Vector3<T>::dot(const Vector3<T> &v) {
  return x * v.x + y * v.y + z * v.z;
}

template <class T>
T Vector3<T>::distance(const Vector3<T> &v, bool squared) const {
  Vector3<T> v1(v);

  v1.subtract(*this);

  return v1.length(squared);
}
template <class T> Vector3<T> &Vector3<T>::operator+=(const Vector3<T> &v2) {
  return add(v2);
}
template <class T> Vector3<T> &Vector3<T>::operator-=(const Vector3<T> &v2) {
  return subtract(v2);
}
template <class T> Vector3<T> &Vector3<T>::operator*=(const Vector3<T> &v2) {
  return multiply(v2);
}
template <class T> Vector3<T> &Vector3<T>::operator*=(const T &s) {
  return multiply(s);
}
template <class T> Vector3<T> &Vector3<T>::operator/=(const Vector3<T> &v2) {
  return divide(v2);
}
template <class T>
Vector3<T> operator+(const Vector3<T> &v1, const Vector3<T> &v2) {
  return Vector3<T>(v1).add(v2);
}
template <class T>
Vector3<T> operator-(const Vector3<T> &v1, const Vector3<T> &v2) {
  return Vector3<T>(v1).subtract(v2);
}
template <class T>
Vector3<T> operator*(const Vector3<T> &v1, const Vector3<T> &v2) {
  return Vector3<T>(v1).multiply(v2);
}
template <class T> Vector3<T> operator*(const Vector3<T> &v, const T &s) {
  return Vector3<T>(v).multiply(s);
}

template <class T>
Vector3<T> operator/(const Vector3<T> &v1, const Vector3<T> &v2) {
  return Vector3<T>(v1).divide(v2);
}
template <class T> Vector3<T> operator-(const Vector3<T> &v) {
  Vector3<T> v1(v);
  return v1.multiply((T)-1);
}
template <class T>
std::ostream &operator<<(std::ostream &os, const Vector3<T> &v) {
  os << "(" << v.x << ";" << v.y << ";" << v.z << ")";
  return os;
}
template <class T> Vector3<T> &Vector3<T>::operator=(const Vector4<T> &v2) {
  *this = Vector3<T>(v2);
  return *this;
}
template <class T> T &Vector3<T>::operator[](unsigned int i) {
  switch (i) {
  case 0:
    return x;
  case 1:
    return y;
  case 2:
    return z;
  default:
    throw "operator[] unsigned int must be 0,1,2";
    break;
  }
}

typedef Vector3<GLfloat> Vector3f;
typedef Vector3<GLdouble> Vector3d;
typedef Vector3<GLint> Vector3i;
} // namespace Johnny
