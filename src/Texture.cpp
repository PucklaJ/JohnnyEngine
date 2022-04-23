#include "../include/Texture.h"
#include "../include/Camera2D.h"
#include "../include/FrameBuffer.h"
#include "../include/Geometry.h"
#include "../include/LogManager.h"
#include "../include/MainClass.h"
#include "../include/Matrix4.h"
#include "../include/Mesh3D.h"
#include "../include/RenderManager.h"
#include "../include/ResourceManager.h"
#include "../include/Shader.h"
#include "../include/Sprite2D.h"
#include "../include/Transform2D.h"
#include "../include/Vertex3D.h"
#include <SDL2/SDL.h>
#include <iostream>

namespace Johnny {
const unsigned int Texture2DShaderUpdater::TRANSFORM_NORMAL = 0;
const unsigned int Texture2DShaderUpdater::TRANSFORM_CAMERA = 1;

Texture2DShaderUpdater::~Texture2DShaderUpdater() {}

void Texture2DShaderUpdater::update() {
  GLint viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);

  m_shader->setUniform("viewportSize",
                       Vector2f((GLfloat)viewport[2], (GLfloat)viewport[3]));
}

void Texture2DShaderUpdater::setUniforms(Transform2D *m, unsigned int index) {
  switch (index) {
  case TRANSFORM_NORMAL:
    m_shader->setUniform("transform", m->getTransformation());
    break;
  case TRANSFORM_CAMERA:
    m_shader->setUniform(
        "transform",
        m->getProjectedTransformation(MainClass::getInstance()->getCamera2D()));
    break;
  }
}

void Texture2DShaderUpdater::setUniforms(Texture *m, unsigned int index) {
  m->bind(m_shader);
  m_shader->setUniform("keyColor", m->getKeyColor().normalise());
  m_shader->setUniform("modColor", m->getModColor().normalise());
  m_shader->setUniform("drawMode", m->getDrawMode());
  m_shader->setUniform("flip", m->getFlip());
  m_shader->setUniform("isFrameBuffer", index != 0);
}

void Texture2DShaderUpdater::setUniforms(TextureRegion *m, unsigned int index) {
  m_shader->setUniform("textureRegion", *m);
}

void Texture2DShaderUpdater::setUniforms(Sprite2D *m,
                                         const unsigned int index) {
  if (m->getTexture()->getDrawMode() == DrawModes::DIRECT)
    glDisable(GL_BLEND);

  m_shader->setUniform("depth", (GLfloat)m->getDepth() / (GLfloat)INT_MAX);

  Texture::renderSprite2D();

  if (m->getTexture()->getDrawMode() == DrawModes::DIRECT)
    glEnable(GL_BLEND);
}

Shader *Texture::m_texture2DShader = nullptr;
GLuint Texture::m_texture2D_vbo = 0;
GLuint Texture::m_texture2D_vao = 0;

Mesh3D *Texture::createTexturePlane(GLfloat width, GLfloat height) {
  Mesh3D *mesh = new Mesh3D();

  Vertex3D *vertices = new Vertex3D[4];
  GLuint *indices = new GLuint[6];

  vertices[0].pos = Vector3f(-width / 2.0f, -height / 2.0f, 0.0f);
  vertices[0].normal = Vector3f(0.0, 0.0, 1.0);
  vertices[0].uv = Vector2f(0.0, 0.0);

  vertices[1].pos = Vector3f(width / 2.0f, -height / 2.0f, 0.0f);
  vertices[1].normal = Vector3f(0.0, 0.0, 1.0);
  vertices[1].uv = Vector2f(1.0, 0.0);

  vertices[2].pos = Vector3f(width / 2.0f, height / 2.0f, 0.0f);
  vertices[2].normal = Vector3f(0.0, 0.0, 1.0);
  vertices[2].uv = Vector2f(1.0, 1.0);

  vertices[3].pos = Vector3f(-width / 2.0f, height / 2.0f, 0.0f);
  vertices[3].normal = Vector3f(0.0, 0.0, 1.0);
  vertices[3].uv = Vector2f(0.0, 1.0);

  indices[0] = 0;
  indices[1] = 1;
  indices[2] = 2;
  indices[3] = 2;
  indices[4] = 3;
  indices[5] = 0;

  mesh->addVertices(vertices, 4, indices, 6);
  delete[] vertices;
  delete[] indices;

  return mesh;
}

Texture *Texture::SDL_SurfaceToTexture(SDL_Surface *sur, GLenum filtering) {
  GLenum mode = sur->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB;
  Texture *tex = new Texture((GLubyte *)sur->pixels, sur->w, sur->h, filtering,
                             mode, mode, GL_UNSIGNED_BYTE, GL_TEXTURE_2D);

  return tex;
}

void Texture::initTexture2DShader(MainClass *mainClass) {
  if (!m_texture2DShader) {
    m_texture2DShader = new Shader();

    m_texture2DShader->addVertexShader(
        mainClass->getResourceManager()->loadShader(
            "vertexShaderTexture2D.glsl"));
    m_texture2DShader->addGeometryShader(
        mainClass->getResourceManager()->loadShader(
            "geometryShaderTexture2D.glsl"));
    m_texture2DShader->addFragmentShader(
        mainClass->getResourceManager()->loadShader(
            "fragmentShaderTexture2D.glsl"));

    m_texture2DShader->addAttribute("position", 0);

    m_texture2DShader->link();
    m_texture2DShader->setShaderUpdater<Texture2DShaderUpdater>();

    m_texture2DShader->addUniform("transform");
    m_texture2DShader->addUniform("textureAddress");
    m_texture2DShader->addUniform("viewportSize");
    m_texture2DShader->addUniform("textureRegion");
    m_texture2DShader->addUniform("isFrameBuffer");
    m_texture2DShader->addUniform("modColor");
    m_texture2DShader->addUniform("keyColor");
    m_texture2DShader->addUniform("drawMode");
    m_texture2DShader->addUniform("flip");
    m_texture2DShader->addUniform("depth");

    mainClass->getRenderManager()->addShader(m_texture2DShader);
  }
}

void Texture::initTexture2DBuffers() {
  if (m_texture2D_vbo == 0) {
    glGenBuffers(1, &m_texture2D_vbo);
    if (m_texture2D_vbo == 0) {
      LogManager::error("Couldn't generate Texture2DVBO", true, true, false);
      return;
    }
    glGenVertexArrays(1, &m_texture2D_vao);
    if (m_texture2D_vao == 0) {
      LogManager::error("Couldn't generate Texture2DVAO", true, true, false);
      return;
    }

    Vector2f pos(0.0, 0.0);

    glBindBuffer(GL_ARRAY_BUFFER, m_texture2D_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vector2f), &pos, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(m_texture2D_vao);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, m_texture2D_vbo);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2f), 0);

    glBindVertexArray(0);
  }
}

void Texture::renderTexture2D(Texture *tex, const Matrix3f &transformation,
                              const TextureRegion *srcRegion, bool bindShader,
                              bool isFrameBuffer, int depth) {
  if (m_texture2D_vbo != 0 && m_texture2D_vao != 0 && m_texture2DShader) {
    if (bindShader)
      m_texture2DShader->bind();
    if (tex->getDrawMode() == DrawModes::DIRECT)
      glDisable(GL_BLEND);
    m_texture2DShader->setUniform("transform", transformation);
    m_texture2DShader->setUniform("viewportSize",
                                  TransformableObject2D::getViewportSize());
    m_texture2DShader->setUniform(
        "textureRegion",
        srcRegion ? *srcRegion
                  : TextureRegion(0, 0, tex->getWidth(), tex->getHeight()));
    m_texture2DShader->setUniform("isFrameBuffer", isFrameBuffer);
    m_texture2DShader->setUniform("keyColor", tex->getKeyColor().normalise());
    m_texture2DShader->setUniform("modColor", tex->getModColor().normalise());
    m_texture2DShader->setUniform("drawMode", tex->getDrawMode());
    m_texture2DShader->setUniform("flip", tex->getFlip());
    m_texture2DShader->setUniform("depth", (GLfloat)depth / (GLfloat)INT_MAX);
    tex->bind(m_texture2DShader);

    glBindVertexArray(m_texture2D_vao);

    glDrawArrays(GL_POINTS, 0, 1);

    glBindVertexArray(0);

    if (tex->getDrawMode() == DrawModes::DIRECT)
      glEnable(GL_BLEND);
  }
}

void Texture::renderTexture2D(Texture *tex, const Vector2f &position,
                              const Vector2f &scale, const GLfloat &rotation,
                              const Camera2D *cam,
                              const TextureRegion *srcRegion, bool bindShader,
                              bool isFrameBuffer, GLenum target, int depth) {
  if (m_texture2D_vbo != 0 && m_texture2D_vao != 0 && m_texture2DShader) {
    Vector2f newPos = TransformableObject2D::fromCoords(position) +
                      Vector2f((GLfloat)tex->getWidth() / 2.0f * scale.x,
                               (GLfloat)tex->getHeight() / 2.0f * -scale.y) +
                      TransformableObject2D::getCenter() *
                          TransformableObject2D::getViewportSize();
    Matrix3f transformation =
        cam ? (cam->getViewMatrix() * Matrix3f::translate(newPos))
            : Matrix3f::translate(newPos);

    if (scale.x != 1.0f || scale.y != 1.0f)
      transformation *= Matrix3f::scale(scale);
    if (rotation != 0.0f && (GLint)rotation % 360 != 0)
      transformation *= Matrix3f::rotate(rotation);

    if (tex->getDrawMode() == DrawModes::DIRECT)
      glDisable(GL_BLEND);

    if (bindShader)
      m_texture2DShader->bind();
    m_texture2DShader->setUniform("transform", transformation);
    m_texture2DShader->setUniform("viewportSize",
                                  TransformableObject2D::getViewportSize());
    m_texture2DShader->setUniform(
        "textureRegion",
        srcRegion ? *srcRegion
                  : TextureRegion(0, 0, tex->getWidth(), tex->getHeight()));
    m_texture2DShader->setUniform("isFrameBuffer", isFrameBuffer);
    m_texture2DShader->setUniform("keyColor", tex->getKeyColor().normalise());
    m_texture2DShader->setUniform("modColor", tex->getModColor().normalise());
    m_texture2DShader->setUniform("drawMode", tex->getDrawMode());
    m_texture2DShader->setUniform("flip", tex->getFlip());
    m_texture2DShader->setUniform("depth", (GLfloat)depth / (GLfloat)INT_MAX);
    tex->bind(m_texture2DShader, "textureAddress", 0, target);

    glBindVertexArray(m_texture2D_vao);

    glDrawArrays(GL_POINTS, 0, 1);

    glBindVertexArray(0);

    if (tex->getDrawMode() == DrawModes::DIRECT)
      glEnable(GL_BLEND);
  }
}

void Texture::renderTexture2D(Texture *tex, const TextureRegion *dst,
                              const TextureRegion *src, const GLfloat &rotation,
                              const Camera2D *cam, bool bindShader,
                              bool isFrameBuffer, int depth) {
  renderTexture2D(
      tex,
      dst ? Vector2f((GLfloat)dst->x, (GLfloat)dst->y) : Vector2f(0.0f, 0.0f),
      dst ? (Vector2f((GLfloat)dst->w, (GLfloat)dst->h) /
             Vector2f((GLfloat)tex->getWidth(), (GLfloat)tex->getHeight()))
          : (TransformableObject2D::getViewportSize() /
             Vector2f((GLfloat)tex->getWidth(), (GLfloat)tex->getHeight())),
      rotation, cam, src, bindShader, isFrameBuffer, depth);
}

void Texture::renderSprite2D() {
  glBindVertexArray(m_texture2D_vao);

  glDrawArrays(GL_POINTS, 0, 1);

  glBindVertexArray(0);
}

Texture *Texture::BOX(const Vector2i &size, const Colorf &color, GLenum target,
                      GLenum filtering, GLenum format, GLenum type) {
  Texture *tex = new Texture(nullptr, size.x, size.y, filtering, format, format,
                             type, target);
  FrameBuffer *fr = new FrameBuffer();
  fr->addTexture(tex);
  fr->bind();
  glClearColor(color.r, color.g, color.b, color.a);
  glClear(GL_COLOR_BUFFER_BIT);
  fr->unbind();
  delete fr;

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  return tex;
}

Shader *Texture::getTexture2DShader() { return m_texture2DShader; }

Texture::Texture(GLubyte *pixels, GLsizei width, GLsizei height,
                 GLenum filtering, GLint internalFormat, GLenum format,
                 GLenum type, GLenum target)
    : Texture() {
  if (m_texture != 0) {
    glBindTexture(target, m_texture);

    glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, filtering);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, filtering);

    if (target == GL_TEXTURE_2D_MULTISAMPLE)
      glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 8, internalFormat,
                              width, height, GL_TRUE);
    else
      glTexImage2D(target, 0, internalFormat, width, height, 0, format, type,
                   (pixels ? pixels : nullptr));

    if (pixels)
      glGenerateMipmap(target);

    glBindTexture(target, 0);
  }
}

Texture::Texture(GLuint texture, GLsizei width, GLsizei height)
    : m_texture(texture), m_width(width), m_height(height) {}

Texture::Texture() {
  glGenTextures(1, &m_texture);

  if (m_texture == 0) {
    LogManager::error("Couldn't generate Texture Buffer", true, true, false);
  }
}

Texture::~Texture() {
  if (m_texture != 0) {
    glDeleteTextures(1, &m_texture);
  }
}

void Texture::bind(Shader *s, const std::string &name, GLuint unit,
                   GLenum target) {
  if (m_texture != 0) {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(target, m_texture);

    s->setUniform(name, (GLint)unit);
  }
}

void Texture::unbind(GLuint unit, GLenum target) {
  if (m_texture != 0) {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(target, 0);
  }
}

GLubyte *Texture::readPixels(GLenum target, GLenum format, GLenum type) {
  GLubyte *data = new GLubyte[4 * getWidth() * getHeight()];

  glGetError();
  glGetTextureImage(m_texture, 0, format, type,
                    4 * sizeof(GLubyte) * getWidth() * getHeight(), data);

  GLenum error = glGetError();

  switch (error) {
  case GL_INVALID_ENUM:
    LogManager::error("Target is invalid in readPixels!");
    break;
  case GL_INVALID_OPERATION:
    LogManager::error("The name of the texture doesn't exist in readPixels");
    break;
  case GL_NO_ERROR:
    break;
  default:
    LogManager::error("Couldn't detect the error: " + std::to_string(error) +
                      " in readPixels!");
    break;
  }

  return data;
}

SDL_Surface *Texture::toSDLSurface(GLenum target, GLenum format, GLenum type) {
  SDL_Surface *sur = SDL_CreateRGBSurfaceWithFormatFrom(
      readPixels(target, format, type), getWidth(), getHeight(), 32,
      getWidth() * 2,
      format == GL_RGBA ? SDL_PIXELFORMAT_RGBA8888 : SDL_PIXELFORMAT_RGB888);

  return sur;
}

const GLsizei &Texture::getWidth() {
  if (m_width == 0) {
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &m_width);
    glBindTexture(GL_TEXTURE_2D, 0);
  }

  return m_width;
}

const GLsizei &Texture::getHeight() {
  if (m_height == 0) {
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &m_height);
    glBindTexture(GL_TEXTURE_2D, 0);
  }

  return m_height;
}

} // namespace Johnny