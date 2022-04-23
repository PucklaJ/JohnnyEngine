#pragma once
#include "Matrix3.h"
#include "Transform2D.h"
#include "Vector2.h"

namespace Johnny {
/*! \brief The camera for all 2D objects
 *        It transforms all 2D objects with m_affectedByCamera = true
 *
 */
class Camera2D : public TransformableObject2D {
public:
  Camera2D();

  /*! \return The 3x3 matrix to transform a 2D object from world space to view
   * space
   *
   */
  Matrix3f getViewMatrix() const;
  /*! \return The zoom of the camera
   *
   */
  const GLfloat &getZoom() const { return m_transform.getScale().x; }

  /*! \brief Sets the zoom of the camera
   * \param zoom The zoom to set
   *
   */
  void setZoom(GLfloat zoom);

  /*! \brief Adds a vector to the position
   * \param pos The vector to add to the position
   * \param relToLook Defines wether the addition should be relative to the
   * rotation
   */
  void addPosition(const Vector2f &pos, bool relToLook = false);
  /*! \brief Same as addPosition(const Vector2f&,bool)
   * \param x The x value of the vector to add to the position
   * \param y The y value of the vector to add to the position
   * \param z The z value of the vector to add to the position
   * \param relToLook Defines wether the addition should be relative to the
   * rotation
   */
  void addPosition(GLfloat x, GLfloat y, bool relToLook = false);
  /*! \brief Adds a value to the zoom
   * \param zoom The zoom to add
   */
  void addZoom(GLfloat zoom);

  /*! \brief Sets the position of the camera
   *
   *
   * It is overriding the method from TransformableObject2D
   * \param pos The position to set the position of the camera
   */
  void setPosition(const Vector2f &pos) override;
  using TransformableObject2D::setPosition;
  /*! \brief This method is overriding the method from TransformableObject2D
   * \return The position of the camera
   *
   */
  Vector2f getPosition() const override;
};
} // namespace Johnny