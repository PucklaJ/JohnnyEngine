#pragma once
#include "../include/Matrix4.h"
#include "../include/Vector2.h"
#include "../include/Vector3.h"
#include "../include/mathematics_functions.h"
#include <GL/glew.h>
#include <iostream>
#include <string>

#define MAT3_GET(r, c) (r + c * 3)

namespace Johnny {
template <class T> class Matrix3;
template <class T> Matrix3<T> operator*(const Matrix3<T> &, const Matrix3<T> &);
template <class T> Matrix3<T> operator*(const Matrix3<T> &, const T &);
template <class T> std::ostream &operator<<(std::ostream &, const Matrix3<T> &);
template <class T> Vector3<T> operator*(const Matrix3<T> &, const Vector3<T> &);
template <class T> Vector2<T> operator*(const Matrix3<T> &, const Vector2<T> &);

/*! \brief A class which represents a 3x3 matrix
 *  \param T The type of which the elements of the matrix should be
 */
template <class T> class Matrix3 {
public:
  /*! \brief Creates an identity 3x3 matrix
   *  \return The newly created 3x3 identity matrix
   */
  static Matrix3 identity();
  /*! \brief Creates a 3x3 translation matrix
   *  \param x How much to translate on the x-Axis
   *  \param y How much to translate on the y-Axis
   *  \return The newly created 3x3 translation matrix
   */
  static Matrix3 translate(const T &x, const T &y);
  /*! \brief Creates a 3x3 translation matrix
   *  \param v The vector on which to translate
   *  \return The newly created translation matrix
   */
  static Matrix3 translate(const Vector2<T> &v);
  /*! \brief Creates a 3x3 rotation matrix
   *  \param rot How much to rotate on the z-Axis in degrees
   *  \return The newly created 3x3 rotation matrix
   */
  static Matrix3 rotate(const T &rot);
  /*! \brief Creates a 3x3 scale matrix
   *  \param x The scaling factor of the x-Axis
   *  \param y The scaling factor of the y-Axis
   *  \return The newly created 3x3 scale matrix
   */
  static Matrix3 scale(const T &x, const T &y);
  /*! \brief Creates a 3x3 scale matrix
   *  \param v The scaling vector
   *  \return The newly created 3x3 scale matrix
   */
  static Matrix3 scale(const Vector2<T> &v);
  /*! \brief Creates a 3x3 worldview matrix
   *  \param pos The position of the viewer
   *  \param zoom How much is zoomed in
   *  \param The rotation of the viewer in degrees
   *  \return The newly created 3x3 worldview matrix
   */
  static Matrix3 camera(const Vector2<T> &pos, const T &zoom, const T &rot);
  /*! \brief Creates a 3x3 worldview matrix
   *  \param pos The position of the viewer
   *  \param middle The point to which the viewer looks
   *  \param up The direction vector which defines where up is
   *  \return The newly created worldview matrix
   */
  static Matrix3 lookAt(const Vector3<T> &pos, const Vector3<T> &middle,
                        const Vector3<T> &up);

  Matrix3() = default;
  /*! \brief Creates a new 3x3 matrix
   *  \param d The value of the diagonal values
   */
  Matrix3(const T &d);
  /*! \brief The copy constructor
   *  \param mat The 3x3 matrix to copy from
   */
  Matrix3(const Matrix3 &mat);

  union {
    T values[3 * 3];       //!< The elements of the 3x3 matrix as an array
    Vector3<T> columns[3]; //!< The elements of the 3x3 matrix as columns
  };

  /*! \brief Multiplies a 3x3 matrix with this matrix
   *  \param mat The 3x3 matrix to multiply with
   *  \return A reference to this matrix
   */
  Matrix3 &multiply(const Matrix3 &mat);
  /*! \brief Multiplies this matrix with a scalar
   *  \param The scalar to multiply with
   *  \return A reference of this matrix
   */
  Matrix3 &multiply(const T &s);
  /*! \brief Multiplies this matrix with a Vector3<T>
   *  \param v The vector to multiply with
   *  \return The resulting Vector3<T> of the multiplication
   */
  Vector3<T> multiply(const Vector3<T> &v) const;

  /*! \brief Prints the 3x3 matrix to the console
   *
   */
  void print();

  Matrix3 &operator*=(const Matrix3 &);
  Matrix3 &operator*=(const T &);

  Vector3<T> &operator[](unsigned int);

  friend Matrix3<T> operator*<>(const Matrix3<T> &, const Matrix3<T> &);
  friend Matrix3<T> operator*<>(const Matrix3<T> &, const T &);
  friend Vector3<T> operator*<>(const Matrix3<T> &, const Vector3<T> &);
  friend Vector2<T> operator*<>(const Matrix3<T> &, const Vector2<T> &);

  friend std::ostream &operator<<<>(std::ostream &, const Matrix3<T> &);
};

template <class T> Matrix3<T> Matrix3<T>::identity() { return Matrix3(1); }

template <class T> Matrix3<T> Matrix3<T>::translate(const T &x, const T &y) {
  Matrix3<T> mat(1);

  mat.values[MAT3_GET(0, 2)] = x;
  mat.values[MAT3_GET(1, 2)] = y;

  return mat;
}

template <class T> Matrix3<T> Matrix3<T>::translate(const Vector2<T> &v) {
  return translate(v.x, v.y);
}

template <class T> Matrix3<T> Matrix3<T>::rotate(const T &angle) {
  Matrix3<T> mat(1);
  T sina = (T)sin((double)toRadians(angle));
  T cosa = (T)cos((double)toRadians(angle));

  mat.values[MAT3_GET(0, 0)] = cosa;
  mat.values[MAT3_GET(1, 1)] = cosa;
  mat.values[MAT3_GET(1, 0)] = sina;
  mat.values[MAT3_GET(0, 1)] = -sina;

  return mat;
}

template <class T> Matrix3<T> Matrix3<T>::scale(const T &x, const T &y) {
  Matrix3<T> mat(1);

  mat.values[MAT3_GET(0, 0)] = x;
  mat.values[MAT3_GET(1, 1)] = y;

  return mat;
}

template <class T> Matrix3<T> Matrix3<T>::scale(const Vector2<T> &v) {
  return scale(v.x, v.y);
}

template <class T>
Matrix3<T> Matrix3<T>::camera(const Vector2<T> &position, const T &zoom,
                              const T &rotation) {
  return rotate(rotation) * scale(zoom, zoom) * translate(position * (T)-1);
}

template <class T>
Matrix3<T> Matrix3<T>::lookAt(const Vector3<T> &position,
                              const Vector3<T> &middle, const Vector3<T> &up) {
  // Src:
  // https://github.com/TheCherno/Sparky/blob/master/Sparky-core/src/sp/maths/mat4.cpp

  Matrix3<T> result(1);
  Vector3<T> f = (middle - position);
  f.normalise();
  Vector3<T> up1 = up;
  up1.normalise();
  Vector3<T> s = f.cross(up);
  Vector3<T> u = s.cross(f);

  result.values[0 + 0 * 3] = s.x;
  result.values[0 + 1 * 3] = s.y;
  result.values[0 + 2 * 3] = s.z;

  result.values[1 + 0 * 3] = u.x;
  result.values[1 + 1 * 3] = u.y;
  result.values[1 + 2 * 3] = u.z;

  result.values[2 + 0 * 3] = -f.x;
  result.values[2 + 1 * 3] = -f.y;
  result.values[2 + 2 * 3] = -f.z;

  return result * translate(-position.x, -position.y);
}

template <class T> Matrix3<T>::Matrix3(const T &v) {
  for (unsigned int i = 0; i < 9; i++) {
    values[i] = 0;
  }

  values[MAT3_GET(0, 0)] = v;
  values[MAT3_GET(1, 1)] = v;
  values[MAT3_GET(2, 2)] = v;
}

template <class T> Matrix3<T>::Matrix3(const Matrix3<T> &mat) {
  for (unsigned int i = 0; i < 9; i++)
    values[i] = mat.values[i];
}

template <class T> Matrix3<T> &Matrix3<T>::multiply(const Matrix3<T> &mat) {
  T sum[3];

  for (unsigned int r = 0; r < 3; r++) {
    for (unsigned int c = 0; c < 3; c++) {
      sum[c] = 0;
      for (unsigned int i = 0; i < 3; i++) {
        sum[c] += values[MAT3_GET(r, i)] * mat.values[MAT3_GET(i, c)];
      }
    }

    for (unsigned int i = 0; i < 3; i++) {
      values[MAT3_GET(r, i)] = sum[i];
    }
  }

  return *this;
}

template <class T> Matrix3<T> &Matrix3<T>::multiply(const T &v) {
  for (unsigned int i = 0; i < 9; i++) {
    values[i] *= v;
  }
}

template <class T> Vector3<T> Matrix3<T>::multiply(const Vector3<T> &v) const {
  Vector3<T> v1(v);

  v1.x = values[MAT3_GET(0, 0)] * v.x + values[MAT3_GET(0, 1)] * v.y +
         values[MAT3_GET(0, 2)] * v.z;
  v1.y = values[MAT3_GET(1, 0)] * v.x + values[MAT3_GET(1, 1)] * v.y +
         values[MAT3_GET(1, 2)] * v.z;
  v1.z = values[MAT3_GET(2, 0)] * v.x + values[MAT3_GET(2, 1)] * v.y +
         values[MAT3_GET(2, 2)] * v.z;

  return v1;
}

template <class T> inline void Matrix3<T>::print() { std::cout << *this; }

template <class T> Matrix3<T> &Matrix3<T>::operator*=(const Matrix3<T> &mat2) {
  return multiply(mat2);
}

template <class T> Matrix3<T> &Matrix3<T>::operator*=(const T &v) {
  return multiply(v);
}

template <class T> Vector3<T> &Matrix3<T>::operator[](unsigned int i) {
  return columns[i];
}

template <class T>
Matrix3<T> operator*(const Matrix3<T> &mat1, const Matrix3<T> &mat2) {
  return Matrix3<T>(mat1).multiply(mat2);
}

template <class T> Matrix3<T> operator*(const Matrix3<T> &mat, const T &v) {
  return Matrix3<T>(mat).multiply(v);
}

template <class T>
Vector2<T> operator*(const Matrix3<T> &mat, const Vector2<T> &v) {
  Vector3<T> v1(mat * Vector3<T>(v.x, v.y, 1));

  return Vector2<T>(v1.x / v1.z, v1.y / v1.z);
}

template <class T>
Vector3<T> operator*(const Matrix3<T> &mat, const Vector3<T> &v) {
  return mat.multiply(v);
}

template <class T>
std::ostream &operator<<(std::ostream &os, const Matrix3<T> &mat) {
  for (unsigned int r = 0; r < 3; r++) {
    os << "[ ";
    for (unsigned int c = 0; c < 3; c++) {
      os << mat.values[MAT3_GET(r, c)] << " ";
    }
    os << "]" << std::endl;
  }

  return os;
}

typedef Matrix3<GLfloat> Matrix3f;
typedef Matrix3<GLdouble> Matrix3d;
typedef Matrix3<GLint> Matrix3i;
} // namespace Johnny
