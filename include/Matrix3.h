#pragma once
#include "../include/Vector2.h"
#include "../include/Vector3.h"
#include <iostream>

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

typedef Matrix3<GLfloat> Matrix3f;
typedef Matrix3<GLdouble> Matrix3d;
typedef Matrix3<GLint> Matrix3i;
} // namespace Johnny

#include "../src/Matrix3.cpp"
