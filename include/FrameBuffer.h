#pragma once
#include <GL/glew.h>

class Texture;
class RenderBuffer;

class FrameBuffer
{
public:
	FrameBuffer();
	~FrameBuffer();

	void addTexture(Texture*,GLuint attachment = GL_COLOR_ATTACHMENT0,GLenum target = GL_FRAMEBUFFER,GLenum textureTarget = GL_TEXTURE_2D);
	void addRenderBuffer(RenderBuffer*,GLuint attachment = GL_DEPTH_STENCIL_ATTACHMENT,GLenum target = GL_FRAMEBUFFER);
	void checkStatus(GLenum target = GL_FRAMEBUFFER);
	void bind(GLenum target = GL_FRAMEBUFFER);
	void unbind(GLenum target = GL_FRAMEBUFFER);
	void blit(FrameBuffer*,GLint,GLint,GLint,GLint,GLint,GLint,GLint,GLint,GLbitfield mask = GL_COLOR_BUFFER_BIT,GLenum filter = GL_NEAREST);

	GLuint getBuffer() { return m_fbo; }

private:
	GLuint m_fbo = 0;
};

