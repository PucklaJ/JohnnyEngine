#pragma once
#include "Vector2.h"
#include <ostream>

namespace Johnny {
template <class T> class Rectangle;
template <class T>
std::ostream &operator<<(std::ostream &, const Rectangle<T> &);

/*! \brief A class which represents a rectangle
 * \param T The type of the x,y,width,height values
 */
template <class T> class Rectangle {
public:
  /*! \brief Creates a new rectangle
   *        with x=0,y=0,width=0,height=0
   *
   */
  Rectangle();
  /*! \brief Creates a new rectangle
   * \param x The x value of the new rectangle
   * \param y The y value of the new rectangle
   * \param width The width value of the new rectangle
   * \param height The height value of the new rectangle
   */
  Rectangle(const T &x, const T &y, const T &width, const T &height);
  /*! \brief Creates a new rectangle
   * \param pos The position of the new rectangle x=pos.x,y=pos.y
   * \param size The size of the new rectangle
   * width=size.width,height=size.height
   */
  Rectangle(const Vector2<T> &pos, const Vector2<T> &size);
  ~Rectangle();

  /*! \return The area of the rectangle
   *
   */
  T area();

  T x = 0; //!< The x coordinate of the position of the rectangle
  T y = 0; //!< The y coordinate of the position of the rectangle
  union {
    T width = 0; //!< The width of the rectangle
    T w;
  };

  union {
    T height = 0; //!< The height of the rectangle
    T h;
  };

  bool intersects(const Rectangle<T> &rect) const;

  friend std::ostream &operator<<<>(std::ostream &, const Rectangle<T> &);
};

template <class T> Rectangle<T>::Rectangle() : Rectangle<T>(0, 0, 0, 0) {}

template <class T>
Rectangle<T>::Rectangle(const T &_x, const T &_y, const T &_width,
                        const T &_height)
    : x(_x), y(_y), width(_width), height(_height) {}

template <class T>
Rectangle<T>::Rectangle(const Vector2<T> &pos, const Vector2<T> &_size)
    : x(pos.x), y(pos.y), width(_size.x), height(_size.y) {}

template <class T> Rectangle<T>::~Rectangle() {}

template <class T> T Rectangle<T>::area() { return width * height; }

template <class T>
bool Rectangle<T>::intersects(const Rectangle<T> &rect) const {
  return rect.x < x + width && rect.x + rect.width > x && rect.y < y + height &&
         rect.y + rect.height > y;
}

template <class T>
std::ostream &operator<<(std::ostream &os, const Rectangle<T> &r) {
  os << "(" << r.x << ";" << r.y << ";" << r.width << ";" << r.height << ")";
  return os;
}

/*! \brief Defines a rectangle on a texture
 *
 */
typedef Rectangle<GLint> TextureRegion;
} // namespace Johnny
