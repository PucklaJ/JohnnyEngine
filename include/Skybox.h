#pragma once
#include "../include/Actor.h"
#include "ShaderUpdater.h"
#include "Vector3.h"
#include <GL/glew.h>
#include <string>

namespace Johnny {
class CubeMap3D;
class Shader;

/*! \brief The ShaderUpdater for the Skybox
 *
 */
class SkyboxShaderUpdater : public ShaderUpdater {
public:
  SkyboxShaderUpdater(Shader *s) : ShaderUpdater(s) {}
  ~SkyboxShaderUpdater() {}

  void setUniforms(Skybox *, const unsigned int index = 0) override;
  void setUniforms(Lighting3D *, const unsigned int index = 0) override {}
  void setUniforms(Camera3D *, const unsigned int index = 0) override;
};

/*! \brief A Vertex which is used for the SkyboxMesh
 *
 */
class SkyboxVertex {
public:
  Vector3f position; //!< Position of the SkyboxVertex
};

/*! \brief The mesh wich is used for the Skybox
 *
 */
class SkyboxMesh {
public:
  SkyboxMesh();
  ~SkyboxMesh();

  /*! \brief Adds vertices to the buffer
   *  \param vertices An array SkyboxVertices to add
   *  \param size The number of vertices to add
   */
  void addVertices(SkyboxVertex *vertices, unsigned int size);

  /*! \brief Renders the SkyboxMesh
   *
   */
  void render();

private:
  GLuint m_vbo = 0; //!< The name of the vertex buffer
  GLuint m_vao = 0; //!< The vertex arrray object of the SkyboxMesh

  GLsizei m_numVertices = 0; //!< The number of vertices in the buffer
};

/*! \brief An enum which consists of the planes of the Skybox
 *
 */
enum SkyboxTex {
  SKY_RIGHT = 0,
  SKY_LEFT = 1,
  SKY_TOP = 2,
  SKY_BOTTOM = 3,
  SKY_FRONT = 4,
  SKY_BACK = 5
};

/*! \brief A class which represents a box which is around the player and has no
 * view translation
 *
 */
class Skybox : public Actor {
public:
  friend class SkyboxShaderUpdater;

  /*! \brief Deletes the SkyboxMesh and SkyboxShader
   *
   */
  static void clear();

  Skybox();
  ~Skybox();

  /*! \brief The init method
   *
   *
   * It is overriding the method from Actor
   */
  bool init() override;
  /*! \brief The update method
   *
   *
   * It is overriding the method from Actor
   */
  bool update() override;
  /*! \brief The render method
   *
   *
   * It is overriding the method from Actor
   */
  bool render() override;
  /*! \brief The quit method
   *
   *
   * It is overriding the method from Actor
   */
  void quit() override;

  /*! \brief Sets the texture file of a plane of the Skybox
   *  \param plane Which plane to set the file for
   *  \param file The file path of the texture relateive to res/textures
   */
  void setTexture(short plane, const std::string &file);

private:
  static Shader
      *SKYBOX_SHADER; //!< The Shader which is used for rendering the Skybox
  static SkyboxMesh
      *SKYBOX_MESH; //!< The Mesh which is used for rendering the Skybox

  CubeMap3D *m_cubeMap =
      nullptr;               //!< The CubeMap3D which stores the texture planes
  std::string m_textures[6]; //!< The file paths od the texture planes
  bool m_texturesSet =
      false; //!< true if any texture has been set and false otherwhise
};
} // namespace Johnny
