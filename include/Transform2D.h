#pragma once
#include "Matrix3.h"
#include "Vector2.h"
#include <GL/glew.h>
#include <vector>

namespace Johnny {
class Camera2D;

/*! \brief A class for calculating a transformation matrix
 *
 */
class Transform2D {
public:
  Transform2D();
  /*! \brief Creates a new Transform2D
   *  \param translation The translation of the new Transform2D
   *  \param rotation The rotation of the new Transform2D
   *  \param scale The scale of the new Transform2D
   */
  Transform2D(const Vector2f &translation, const GLfloat &rotation,
              const Vector2f &scale);
  ~Transform2D();

  /*! \return The translation of the Transform2D
   *
   */
  const Vector2f &getTranslation() const { return m_translation; }
  /*! \return The rotation of the Transform2D
   *
   */
  const GLfloat &getRotation() const { return m_rotation; }
  /*! \return The scale of the Transform2D
   *
   */
  const Vector2f &getScale() const { return m_scale; }

  /*! \brief Sets the translation of the Transform2D
   *  \param translation The translation to set
   */
  void setTranslation(const Vector2f &translation) {
    m_translation = translation;
  }
  /*! \brief Sets the rotation of the Transform2D
   *  \param rotation The rotation to set
   */
  void setRotation(const GLfloat &rotation) { m_rotation = rotation; }
  /*! \brief Sets the scale of the Transform2D
   *  \param scale The scale to set
   */
  void setScale(const Vector2f &scale) { m_scale = scale; }

  /*! \brief Sets the translation of the Transform2D
   *  \param transX The x translation to set
   *  \param transY The y translation to set
   */
  void setTranslation(const GLfloat &transX, const GLfloat &transY) {
    m_translation = Vector2f(transX, transY);
  }
  /*! \brief Sets the scale of the Transform2D
   *  \param scaleX The x scale to set
   *  \param scaleY The y scale to set
   */
  void setScale(const GLfloat &scaleX, const GLfloat &scaleY) {
    m_scale = Vector2f(scaleX, scaleY);
  }

  /*! \return The modelworld transformation matrix
   *
   */
  Matrix3f getTransformation() const;
  /*! \return The modelworldview matrix
   *  \param cam The Camera2D to use for the view
   */
  Matrix3f getProjectedTransformation(const Camera2D *cam) const;

private:
  Vector2f m_translation; //!< The translation of the Transform2D
  GLfloat m_rotation;     //!< The rotation of the Transformr2D
  Vector2f m_scale;       //!< The scale of the Tranform2D
};

/*! \brief A class which represents a object with a Transform2D
 *
 */
class TransformableObject2D {
public:
  /*! \return The center of the coordinate system relative the center of the
   * screen (will be multiplied onto the viewport size)
   *
   */
  static const Vector2f &getCenter();
  /*! \return Wether the y-Axis is flipped in this coordinate system
   *
   */
  static bool getYAxisFlipped();
  /*! \return Wether the x-Yxis is dlipped int this coordinate system
   *
   */
  static bool getXAxisFlipped();
  /*! \return The size of the viewport you are currently rendering to
   *
   */
  static const Vector2f &getViewportSize();

  /*! \brief Sets the center of the coordinate system
   *  \param center The center to set relative to the center of the screen (will
   * be multiplied to onto the viewport size, internal use only)
   */
  static void setCenter(const Vector2f &center);
  /*! \brief Sets wether the y-Axis is flipped in this coordinate system
   *  \param b The coresponding bool value
   */
  static void setYAxisFlipped(bool b);
  /*! \brief Sets wether the x-Axis is flipped in this scoordinate system
   *  \param b The coresponding bool value
   */
  static void setXAxisFlipped(bool b);
  /*! \brief Sets the size of the viewport
   *  \param view The viewport to set
   */
  static void setViewportSize(const Vector2f &view);

  /*! \brief Converts a vector into the coordinate system
   *  \param v The vector to convert
   *  \param viewport The viewport which will be used for the calculation (if
   * x=-1.0f && y-1.0f the viewport of the class will be used)
   */
  static Vector2f toCoords(const Vector2f &v,
                           const Vector2f &viewport = Vector2f(-1.0f, -1.0f));
  /*! \brief Converts a vector into the coordinate system
   *  \param v The vector to convert
   *  \param x Wether the x-Axis should be flipped
   *  \param y Wether the y-Axis should be flipped
   */
  static Vector2f toCoords(const Vector2f &v, bool x, bool y);
  /*! \brief Converts a vector from the coordinate system
   *  \param v The vector to convert
   *  \param viewport The viewport which will be used for the calculation (if
   * x=-1.0f && y-1.0f the viewport of the class will be used)
   */
  static Vector2f fromCoords(const Vector2f &,
                             const Vector2f &viewport = Vector2f(-1.0f, -1.0f));
  /*! \brief Converts a vector from the coordinate system
   *  \param v The vector to convert
   *  \param x Wether the x-Axis should be flipped
   *  \param y Wether the y-Axis should be flipped
   */
  static Vector2f fromCoords(const Vector2f &, bool, bool);

  static bool centerSet; //!< Wether the center has been defined

  TransformableObject2D();
  virtual ~TransformableObject2D();

  /*! \brief Sets the position of the object
   *  \param v The position in the converted coordinate system
   */
  virtual void setPosition(const Vector2f &v);
  /*! \brief Sets the position of the object
   *  \param x The x position in the converted coordinate system
   *  \param y The y position in the converted coordinate system
   */
  virtual void setPosition(const GLfloat &x, const GLfloat &y);
  /*! \brief Sets the rotation of the object
   *  \param rot The rotation to set in degress
   */
  virtual void setRotation(const GLfloat &rot);
  /*! \brief Sets the scale of the object
   *  \param scale The scale to set
   */
  virtual void setScale(const Vector2f &scale);
  /*! \brief Sets the scale of the object
   *  \param x The x scale of the object
   *  \param y The y scale of the object
   */
  virtual void setScale(const GLfloat &x, const GLfloat &y);

  /*! \brief Adds a vector to the position
   *  \param v The vector to add
   */
  virtual void addPosition(const Vector2f &v);
  /*! \brief Adds a vector to the position
   *  \param x The x value of the vector to add
   *  \param y The y value of the vector to add
   */
  virtual void addPosition(const GLfloat &x, const GLfloat &y);
  /*! \brief Adds a value to the rotation
   *  \param x The rotation to add
   */
  virtual void addRotation(const GLfloat &x) {
    setRotation(m_transform.getRotation() + x);
  }
  /*! \brief Adds a vector to the scale
   *  \param v The vector to add to the scale
   */
  virtual void addScale(const Vector2f &v);
  /*! \brief Adds a vector to the scale
   *  \param x The x value of the vector to add
   *  \param y The y value of the vector to add
   */
  virtual void addScale(const GLfloat &x, const GLfloat &y);

  /*! \return The position of the object
   *
   */
  virtual Vector2f getPosition() const;
  /*! \return The rotation of the object on degrees
   *
   */
  virtual const GLfloat &getRotation() const {
    return m_transform.getRotation();
  }
  /*! \return The scale of the object
   *
   */
  virtual const Vector2f &getScale() const { return m_transform.getScale(); }

  /*! \return The Transform2D of the object
   *
   */
  Transform2D &getTransform() { return m_transform; }

protected:
  /*! \brief Sets the size of the object
   *  \param v The size to set
   */
  virtual void setSize(const Vector2f &v);
  /*! \brief Sets the size of the object
   *  \param x The x size to set
   *  \param y The y size to set
   */
  virtual void setSize(GLfloat x, GLfloat y) { setSize(Vector2f(x, y)); }

  /*! \return The size of the object
   *
   */
  virtual const Vector2f &getSize() const { return m_size; }

  Transform2D m_transform;        //!< The Transform2D of the object
  Vector2f m_size;                //!< The size of the object
  bool m_affectedByCenter = true; //!< Defines wether the object is centered not
                                  //!< in the center of the screen
private:
  static Vector2f center; //!< The center of the coordinate system (relative to
                          //!< the center of the screen)
  static Vector2f viewportSize; //!< The size of the viewport
  static bool yAxisFlipped;     //!< Defines wether the y-Axis is flipped in the
                                //!< coordinate system
  static bool xAxisFlipped;     //!< Defines wether the x-Axis is flipped in the
                                //!< coordinate system
  static std::vector<TransformableObject2D *>
      objects; //!< An array with all TransformableObject2Ds
};
} // namespace Johnny