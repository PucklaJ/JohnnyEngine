#pragma once
#include "Actor.h"
#include "Geometry.h"
#include "Texture.h"
#include "Tween.h"
#include <string>

namespace Johnny {
class TiledMap;

/*! \brief A class which represents a Texture as an Actor
 *
 */
class Sprite2D : public Actor, public TweenableObject2D {
public:
  friend class TiledMap;

  Sprite2D();
  /*! \brief Creates a new Sprite2D
   *  \param file The file path of the Texture for the sprite relative to
   * res/textures
   */
  Sprite2D(const std::string &file);
  /*! \brief Creates a new Sprite2D
   *  \param tex The Texture for the new Sprite2D
   */
  Sprite2D(Texture *tex);
  ~Sprite2D();

  /*! \brief The init method
   *
   *
   * It is overriding the method from Actor
   */
  virtual bool init() override;
  /*! \brief The update method
   *
   *
   * It is overriding the method from Actor
   */
  virtual bool update() override;
  /*! \brief The render method
   *
   *
   * It is overriding the method from Actor
   */
  virtual bool render() override;
  /*! \brief The quit method
   *
   *
   * It is overriding the method from Actor
   */
  virtual void quit() override;

  /*! \brief Sets the Texture of the Sprite2D
   *  \param tex The Texture to set
   */
  void setTexture(Texture *tex);
  /*! \brief Sets the source region of the Sprite2D which defines what to use
   * from the texture for rendering \param region The TextureRegion to set
   */
  void setSrcRegion(const TextureRegion &region);
  /*! \brief Sets the draw size of the Sprite2D which defines how big the
   * Texture should be rendered in pixels \param v A vector to set the size
   */
  void setDrawSize(const Vector2f &v);
  /*! \brief Sets the draw size of the Sprite2D which defines how big the
   * Texture should be rendered in pixels \param width The width which defines
   * how big the Texture should be drawn \param height The height which defines
   * how big the Texture should be drawn
   */
  void setDrawSize(GLfloat width, GLfloat height);
  /*! \brief Sets the depth of the Sprite2D
   *  \param depth The depth to set [-INT_MAX;INT_MAX]
   *
   * Objects with a smaller depth value are rendered above
   */
  void setDepth(int depth) { m_depth = depth; }

  /*! \return The Texture of the Sprite2D
   *
   */
  Texture *getTexture() { return m_texture; }
  /*! \return The source region which defines what to draw from the Texture
   *
   */
  const TextureRegion &getSrcRegion() const { return m_srcRegion; }
  /*! \return The size with which the Sprite2D will be drawn
   *
   */
  Vector2f getDrawSize() const;
  /*! \return The draw size multiplied with the scale
   *
   */
  Vector2f getActualSize() const;
  /*! \return The Bounding Box of the Sprite2D
   *
   */
  Rectangle<GLfloat> getBoundingBox();
  /*! \return The depth of the object
   *
   */
  const int &getDepth() const { return m_depth; }

  /*! \brief Checks if this Sprite2D intersects with another Sprite2D
   *  \param spr The Sprite2D to check
   *  \return true if they intersect and false otherwhise
   */
  bool intersects(Sprite2D *spr);
  /*! \brief Checks if this Sprite2D intersects with a position on the world
   *  \param pos The position to check
   *  \return true if they intersect and false otherwhise
   */
  bool intersects(const Vector2f &pos);
  /*! \brief Checks if this Sprite2D intersects with a rectangle
   *  \param rect The Rectangle to check
   *  \return true if they intersect and false otherwhise
   */
  bool intersects(const Rectangle<GLfloat> &rect);

protected:
  Texture *m_texture = nullptr; //!< The Texture of the Sprite2D
  TextureRegion m_srcRegion;    //!< The source region which defines what to use
                                //!< from the Texture
  /*! \brief The depth of the Sprite2D
   *
   *
   * Objects with a smaller depth value are rendered above
   */
  int m_depth = 0;

private:
  std::string m_fileName = ""; //!< The file pathof the Texture
  Vector2f m_drawScale; //!< The scale which gets multiplied when rendering
};
} // namespace Johnny
