#pragma once
#include "Matrix4.h"
#include "ShaderUpdater.h"
#include "Texture.h"
#include <string>

#define SHADOW_POINT 1
#define SHADOW_DIR 2
#define SHADOW_SPOT 3

namespace Johnny {
class MainClass;
class FrameBuffer;
class PointLight3D;
class DirectionalLight3D;
class SpotLight3D;
class Shader;
class Entity3D;

/*! \brief The ShaderUpdater class for the ShadowMap3D
 *
 */
class ShadowMap3DShaderUpdater : public ShaderUpdater {
public:
  ShadowMap3DShaderUpdater(Shader *s) : ShaderUpdater(s) {}
  ~ShadowMap3DShaderUpdater() {}

  void setUniforms(Camera3D *, const unsigned int index = 0) override {}
  void setUniforms(Lighting3D *, const unsigned int index = 0) override {}
  void setUniforms(Mesh3D *, const unsigned int index = 0) override {}

  void setUniforms(Transform3D *, const unsigned int index = 0) override;
  void setUniforms(Entity3D *, const unsigned int index = 0) override;
};

/*! \brief A class which represents a shadow map which is used to store the
 * depth of every object which casts shadows
 *
 */
class ShadowMap3D : public Texture {
public:
  /*! \brief Creates a new ShadowMap3D
   *  \param width The width of the new ShadowMap3D in pixels
   *  \param height The height of the new ShadowMap3D in pixels
   */
  ShadowMap3D(GLsizei width, GLsizei height);
  ~ShadowMap3D();

  /*! \brief Renderes the ShadowMap3D
   *  \param m The MainClass from which to use the objects
   *  \param s The Shader with which to render the ShadowMap3D
   */
  void render(MainClass *m, Shader *s);

  /*! \brief Sets light which casts the shadows on the map to a PointLight3D
   *  \param p The PointLight3D to set
   */
  void setPointLight(PointLight3D *p);
  /*! \brief Sets light which casts the shadows on the map to a
   * DirectionalLight3D \param d The DirectionalLight3D to set
   */
  void setDirectionalLight(DirectionalLight3D *d);
  /*! \brief Sets light which casts the shadows on the map to a SpotLight3D
   *  \param s The SpotLight3D to set
   */
  void setSpotLight(SpotLight3D *s);
  /*! \brief Loads the light projetion matrix into a Shader as a uniform
   *  \param s The Shader to which the matrix should be loaded
   *  \param name The name of the uniform
   */
  void loadMatrix(Shader *s, const std::string &name = "lightSpaceMatrix");
  /*! \brief Loads the light projection matrix and the Texture into a Shader as
   * a uniform \param s The Shader to load to \param index The index x to which
   * the Texture should be bound \param matrixName The name of the uniform for
   * the light projection matrix \param textureName The name of the uniform for
   * the Texture
   */
  void load(Shader *s, GLuint index = 0,
            const std::string &matrixName = "lightSpaceMatrix",
            const std::string &textureName = "shadowMap");

  /*! \return The FrameBuffer which woll be used for the rendering
   *
   */
  FrameBuffer *getFrameBuffer() { return m_frameBuffer; }

private:
  /*! \brief Caclulates the light projection matrix and loads it to a Shader
   *  \param s The Shader to load the matrix to
   */
  void configureMatricesAndShader(Shader *s);

  FrameBuffer *m_frameBuffer =
      nullptr; //!< The FrameBuffer which is used for rendering to the Texture
  PointLight3D *m_pointLight =
      nullptr; //!< The PointLight3D which casts the shadows
  DirectionalLight3D *m_directionalLight =
      nullptr; //!< The DirectionalLight3D which casts the shadows
  SpotLight3D *m_spotLight =
      nullptr;           //!< The SpotLight3D which casts the shadows
  GLuint m_curLight = 0; //!< The type of the light which casts the shadows

  Matrix4f m_lightSpaceMatrix; //!< The light space projection matrix which is
                               //!< used to transform the vertices into the view
                               //!< of the light
};

} // namespace Johnny
