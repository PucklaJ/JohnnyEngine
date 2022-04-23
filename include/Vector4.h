#pragma once
#include <GL/glew.h>
#include <iostream>

namespace Johnny {
template <class T> class Vector4;
template <class T>
const Vector4<T> operator+(const Vector4<T> &, const Vector4<T> &);
template <class T>
const Vector4<T> operator-(const Vector4<T> &, const Vector4<T> &);
template <class T>
const Vector4<T> operator*(const Vector4<T> &, const Vector4<T> &);
template <class T>
const Vector4<T> operator/(const Vector4<T> &, const Vector4<T> &);

template <class T> std::ostream &operator<<(std::ostream &, const Vector4<T> &);

/*! \brief A class which represents a value with four dimensions
 *  \param T The type of the elements of the Vector4
 */
template <class T> class Vector4 {
public:
  Vector4() = default;
  /*! \brief Creates a new Vector4
   *  \param x The x value of the new Vector4
   *  \param y The y value of the new Vector4
   *  \param z The z value of the new Vector4
   *  \param w The w value of the new Vector4
   */
  Vector4(const T &x, const T &y, const T &z, const T &w);
  /*! \brief Copies a Vector4
   *  \param v The Vector4 to copy
   */
  Vector4(const Vector4 &v);

  union {
    T x = 0; //!< The x value of the Vector4 if it is used as a position
    T r;     //!< The x value of the Vector4 if it is used as a color
    T width; //!< The x value of the Vector4 if it is used as dimensions
  };

  union {
    T y = 0;  //!< The y value of the Vector4 if it is used as a position
    T g;      //!< The y value of the Vector4 if it is used as a color
    T height; //!< The y value of the Vector4 if it is used as dimensions
  };

  union {
    T z = 0; //!< The z value of the Vector4 if it is used as a position
    T b;     //!< The z value of the Vector4 if it is used as a color
    T depth; //!< The z value of the Vector4 if it is used as dimensions
  };

  union {
    T w = 0; //!< The w value of the Vector4 if it i used as a position
    T a;     //!< The w value of the Vector4 if it i used as a color
    T time;  //!< The w value of the Vector4 if it i used as dimensions
  };

  /*! \param squared Wether the result should be the squared length or not
   *  \return The length of the Vector4
   */
  T length(bool squared = false) const;
  /*! \brief Normalises a Vector4
   *  \return A reference to this object
   */
  Vector4 &normalise();

  /*! \brief Adds a Vector4 to this object
   *  \param v The Vector4 to add
   *  \return A reference to this object
   */
  Vector4 &add(const Vector4 &v);
  /*! \brief Subtracts a Vector4 from this object
   *  \param v The Vector4 to subtract
   *  \return A refreence to this object
   */
  Vector4 &subtract(const Vector4 &v);
  /*! \brief Multiplies each element of the Vector4 which each other
   *  \param v The Vector4 for the multiplication
   *  \return A reference to this object
   */
  Vector4 &multiply(const Vector4 &v);
  /*! \brief Multiplies this vector with a scalar
   *  \param s The scalar to multiply
   *  \return A reference to the object
   */
  Vector4 &multiply(const T &s);
  /*! \brief Divides each element of the Vector4 by the corresponding element of
   * the other Vector4 \param v The other Vector4 for the division \return A
   * reference to the object
   */
  Vector4 &divide(const Vector4 &v);
  /*! \brief Divides each element by a scalar
   *  \param s The scalar for the division
   *  \return A reference to the object
   */
  Vector4 &divide(const T &s);

  /*! \brief Calculates the distance between this Vector4 and another Vector4
   *  \param v The other Vector4 for the calculation
   *  \param squared Wether the result should be the squared distance
   *  \return The distance between this Vector4 and the other Vector4
   */
  T distance(const Vector4 &v, bool squared = false) const;

  Vector4 &operator+=(const Vector4 &);
  Vector4 &operator-=(const Vector4 &);
  Vector4 &operator*=(const Vector4 &);
  Vector4 &operator/=(const Vector4 &);

  T &operator[](unsigned int);

  friend const Vector4<T> operator+<>(const Vector4<T> &, const Vector4<T> &);
  friend const Vector4<T> operator-<>(const Vector4<T> &, const Vector4<T> &);
  friend const Vector4<T> operator*<>(const Vector4<T> &, const Vector4<T> &);
  friend const Vector4<T> operator/<>(const Vector4<T> &, const Vector4<T> &);

  friend std::ostream &operator<<<>(std::ostream &, const Vector4<T> &);
};

typedef Vector4<GLfloat> Vector4f;
typedef Vector4<GLdouble> Vector4d;
typedef Vector4<GLint> Vector4i;
} // namespace Johnny

#include "../src/Vector4.cpp"
