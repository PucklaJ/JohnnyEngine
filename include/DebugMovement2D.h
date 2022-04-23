#pragma once
#include "Actor.h"

namespace Johnny {
/*! \brief A class which adds a small 2D DebugCameraMovement to the application
 *        like camera scrolling, zooming and rotating
 *
 */
class DebugMovement2D : public Actor {
public:
  /*! \brief Creates a new DebugMovement2D
   * \param moveSpeed The speed with which the camera scrolls [pixel/s]
   * \param zoomSpeed The speed with which the camera zooms [n/s]
   * \param ratoteSpeed The speed with which the camera rotates [degree/s]
   */
  DebugMovement2D(float moveSpeed = 100.0f, float zoomSpeed = 0.4f,
                  float rotateSpeed = 10.0f);
  ~DebugMovement2D();

  /*! \brief The update method
   *
   *
   * It is overriding the method from Actor
   */
  bool update() override;

private:
  float m_moveSpeed =
      100.0f; //!< The speed with which the camera scrolls [pixel/s]
  float m_zoomSpeed = 0.4f; //!< The speed with which the camera zooms [n/s]
  float m_rotateSpeed =
      10.0f; //!< The speed with which the camera rotates [degree/s]
};
} // namespace Johnny