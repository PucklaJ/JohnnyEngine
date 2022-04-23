#ifndef PHYSICS_SPRITE_H
#define PHYSICS_SPRITE_H
#include "../include/Sprite2D.h"
#include <box2d/box2d.h>

namespace Johnny {
class Texture;

/*! \brief A class which represents a b2Body as a Sprite2D
 *
 */
class PhysicsSprite2D : public Sprite2D {
public:
  /*! \brief Creates a new PhysicsSprite2D
   *  \param body The body of the new PhysicsSprite2D
   */
  PhysicsSprite2D(b2Body *body = nullptr);
  /*! \brief Creates a new PhysicsSprite2D
   *  \param file The file path of the Texture of the new PhysicsSprite2D
   *  \param body The b2Body of the new PhysicsSprite2D
   */
  PhysicsSprite2D(const std::string &file, b2Body *body = nullptr);
  /*! \brief Creates a new PhysicsSprite2D
   *  \param texture The Texture of the new PhysicsSprite2D
   *  \param body The b2Body of the new PhysicsSprite2D
   */
  PhysicsSprite2D(Texture *texture, b2Body *body = nullptr);
  virtual ~PhysicsSprite2D();

  /*! \brief The init method
   *
   *
   * It is overriding the method from Sprite2D
   */
  virtual bool init() override;
  /*! \brief The m_update method
   *
   *
   * It is overriding the method from Sprite2D
   */
  virtual bool m_update() override;
  /*! \brief The m_quit method
   *
   *
   * It is overriding the method from m_quit
   */
  virtual void m_quit() override;

  /*! \return The b2Body of the PhysicsSprite2D
   *
   */
  b2Body *getBody() { return m_body; }
  /*! \return If the PhysicsSprite2D should be destroyed if it moves out of the
   * physics world
   *
   */
  bool getAutomaticDestroy() { return m_automaticDestroy; }
  /*! \return The offset that applies to the attaching of the Sprite2D to the
   * b2Body
   *
   */
  const Vector2f &getOffset() const { return m_offset; }

  /*! \brief Sets the body of the PhysicsSprite2D
   *  \param body The b2Body to set
   */
  void setBody(b2Body *body) {
    m_body = body;
    body->SetUserData(this);
  }
  /*! \brief Sets if the PhysicsSprite2D should be destroyed if it moves out of
   * the physics world \param b The bool value to set m_automaticDestroy
   */
  void setAutomaticDestroy(bool b) { m_automaticDestroy = b; }
  /*! \brief Sets the offset which applies to the attaching of the Sprite2D to
   * the b2Body \param v The offset to set
   */
  void setOffset(const Vector2f &v) { m_offset = v; }

  /*! \brief Gets called when the b2Body of the PhysicsSprite2D begins colliding
   * with another b2Body \param c The b2Contact of the collision \param f1 The
   * b2Fixture of the PhysicsSprite2D \param f2 The b2Fixture of the other
   * b2Body it collides with \param spr The other PhysicsSprite2D, if the body
   * is not attached to a PhysicsSprite2D it is nullptr
   */
  virtual void BeginContact(b2Contact *c, b2Fixture *f1, b2Fixture *f2,
                            PhysicsSprite2D *spr) {}
  /*! \brief Gets called when the b2Body of the PhysicsSprite2D ends colliding
   * with another b2Body \param c The b2Contact of the collision \param f1 The
   * b2Fixture of the Physics \param f2 The b2Fixture of the other b2Body \param
   * spr The other PhysicsSprite2D, if the body is not attached to a
   * PhysicsSprite2D it is nullptr
   */
  virtual void EndContact(b2Contact *c, b2Fixture *f1, b2Fixture *f2,
                          PhysicsSprite2D *spr) {}
  /*! \brief Gets called every time the PhysicsSprite2D is colliding with
   * another b2Body \param c The b2Contact of the collision \param f1 The
   * b2Fixture of the PhysicsSprite2D \param f2 The b2Fixture of the other
   * b2Body \param m The b2Manifold of the collision \param spr The other
   * PhysicsSprite2D, if the body is not attached to a PhysicsSprite2D it is
   * nullptr
   */
  virtual void PreSolve(b2Contact *c, b2Fixture *f1, b2Fixture *f2,
                        const b2Manifold *m, PhysicsSprite2D *spr) {}
  /*! \brief Gets called every time the PhysicsSprite2D is colliding with
   * another b2Body after PreSolve \param c The b2Contact of the collision
   *  \param f1 The b2Fixture of the PhysicsSprite2D
   *  \param f2 The b2Fixture of the other b2Body
   *  \param ci The b2ContactImpulse of the collision
   *  \param spr The other PhysicsSprite2D, if the body is not attached to a
   * PhysicsSprite2D it is nullptr
   */
  virtual void PostSolve(b2Contact *c, b2Fixture *f1, b2Fixture *f2,
                         const b2ContactImpulse *ci, PhysicsSprite2D *spr) {}

protected:
  bool m_automaticDestroy =
      true; //!< Defines if the PhysicsSprite2D should be destroyed if it moves
            //!< out of the physics world
  Vector2f m_offset; //!< The offset of the PhysicsSprite2D with which it gets
                     //!< attached to the b2Body in pixel coordinates

private:
  /*! \brief Gets called every frame and connects the b2Body with the Sprite2D
   *
   */
  virtual void attachBodyToSprite();

  b2Body *m_body = nullptr; //!< The b2Body of the PhysicsSprite2D
};
} // namespace Johnny

#endif
