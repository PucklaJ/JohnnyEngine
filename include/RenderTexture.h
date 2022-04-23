#include "Geometry.h"
#include "Texture.h"
#include <GL/glew.h>

namespace Johnny {
class FrameBuffer;
class Camera2D;

/*! \brief A Texture that is attached to a FrameBuffer for easy to use render to
 * Texture
 *
 */
class RenderTexture : public Texture {
public:
  /*! \brief Creates a new RenderTexture
   *  \param width The width of the new RenderTexture
   *  \param height The height of the new RenderTexture
   *  \param filtering The filter technique which will be used for sampling from
   * the texture \param target The target to which the new RenderTexture will be
   * bound \param format The format of the pixels of the new RenderTexture
   *  \param type The type of the new RenderTexture with which the pixels are
   * stored
   */
  RenderTexture(GLsizei width, GLsizei height, GLenum filtering = GL_LINEAR,
                GLenum target = GL_TEXTURE_2D, GLenum format = GL_RGBA,
                GLenum type = GL_UNSIGNED_BYTE);
  ~RenderTexture();

  /*! \brief Binds the FrameBuffer and ajusts the viewport
   *
   */
  void target();
  /*! \brief Unbinds the FrameBuffer and reajusts the viewport
   *
   */
  void untarget();
  /*! \brief Renders the Texture of the RenderTexture
   *  \param position The position where to render in pixels
   *  \param scale The scale with which the Texture will be rendered
   *  \param rotation The rotation with which the Texture will be rendered
   *  \param cam The Camera2D in which view the Texture should be transformed
   * (if nullptr no view transformation will be apllied) \param srcRegion The
   * TextureRegion which defines what to take from the Texture (if nullptr
   * {0,0,width,height} will be used) \param bindShader Defines whether to bind
   * the Texture2DShader \param target The target to which the Texture should be
   * bound
   */
  void render(const Vector2f &position,
              const Vector2f &scale = Vector2f(1.0f, 1.0f),
              GLfloat rotation = 0.0f, const Camera2D *cam = nullptr,
              const TextureRegion *srcRegion = nullptr, bool bindShader = true,
              GLenum target = GL_TEXTURE_2D);

  /*! \return Tthe FrameBuffer of the RenderTexture
   *
   */
  FrameBuffer *getFrameBuffer() { return m_frameBuffer; }

private:
  FrameBuffer *m_frameBuffer =
      nullptr; //!< The FrameBuffer of the RenderTexture
};
} // namespace Johnny