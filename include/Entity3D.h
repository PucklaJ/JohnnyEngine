#pragma once
#include "../include/Actor.h"
#include "../include/Transform3D.h"
#include <string>

namespace Johnny {
class Model3D;
class Shader;
class Mesh3D;

/*! \brief Thes represents a model as a Actor
 *
 */
class Entity3D : public Actor, public TransformableObject3D {
public:
  /*! \brief Creates a new Entity3D
   * \param file The file from which to load the model
   *
   */
  Entity3D(const std::string &file);
  /*! \brief Creates a new Entity3D
   * \param mesh The mesh which is used for rendering
   */
  Entity3D(Mesh3D *mesh);
  /*! \brief Creates a new Entity3D
   * \param model The model which is used for rendering
   */
  Entity3D(Model3D *model);
  ~Entity3D();

  /*! \brief The init method
   *
   *
   * It is overriding the method of Actor
   */
  virtual bool init() override;
  /*! \brief The update method
   *
   *
   * It is overriding the method of Actor
   */
  virtual bool update() override;
  /*! \brief The render method
   *
   *
   * It is overriding the method of Actor
   */
  virtual bool render() override;
  /*! \brief The quit method
   *
   *
   * It is overriding the method of Actor
   */
  virtual void quit() override;

  /*! \brief Sets the model of the object
   * \param m The model to set
   */
  void setModel(Model3D *m) { m_model = m; }

  /*! \return The model of the object
   *
   */
  Model3D *getModel() { return m_model; }

private:
  std::string m_fileName = ""; //!< The file name of the model to load
  Model3D *m_model = nullptr;  //!< The model
};
} // namespace Johnny
