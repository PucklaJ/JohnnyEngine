#pragma once
#include <GL/glew.h>

class RenderBuffer
{
public:
	RenderBuffer(GLsizei,GLsizei,GLenum format = GL_DEPTH24_STENCIL8,GLenum target = GL_RENDERBUFFER,bool multisampling = false);
	~RenderBuffer();

	void bind(GLenum target = GL_RENDERBUFFER);
	void unbind(GLenum target = GL_RENDERBUFFER);

	GLuint getBuffer() { return m_rbo; }
private:
	GLuint m_rbo = 0;
};

