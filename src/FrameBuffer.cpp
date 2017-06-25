#include <FrameBuffer.h>
#include <Texture.h>
#include <RenderBuffer.h>
#include <iostream>

FrameBuffer::FrameBuffer()
{
	glGenFramebuffers(1, &m_fbo);
	if (m_fbo == 0)
	{
		std::cerr << "Couldn't create FrameBuffer" << std::endl;
	}
}

FrameBuffer::~FrameBuffer()
{
	if (m_fbo != 0)
	{
		glDeleteFramebuffers(1, &m_fbo);
	}
}

void FrameBuffer::addTexture(Texture* t, GLuint attachment, GLenum target,GLenum textureTarget)
{
	bind(target);
	glBindTexture(textureTarget, t->getBuffer());
	glFramebufferTexture2D(target, attachment,textureTarget, t->getBuffer(), 0);
	glBindTexture(textureTarget, 0);
	unbind(target);
}

void FrameBuffer::addRenderBuffer(RenderBuffer* r, GLuint attachment, GLenum target)
{
	bind(target);
	r->bind();
	glFramebufferRenderbuffer(target, attachment, GL_RENDERBUFFER, r->getBuffer());
	r->unbind();
	unbind(target);
}

void FrameBuffer::checkStatus(GLenum target)
{
	bind(target);
	if (glCheckFramebufferStatus(target) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cerr << "FrameBuffer isn't completed" << std::endl;
	}
	unbind(target);
}

void FrameBuffer::bind(GLenum target)
{
	glBindFramebuffer(target, m_fbo);
}

void FrameBuffer::unbind(GLenum target)
{
	glBindFramebuffer(target, 0);
}

void FrameBuffer::blit(FrameBuffer* f, GLint sx0, GLint sy0, GLint sx1, GLint sy1, GLint dx0, GLint dy0, GLint dx1, GLint dy1, GLbitfield mask, GLenum filter)
{
	bind(GL_READ_FRAMEBUFFER);
	if(f)
		f->bind(GL_DRAW_FRAMEBUFFER);
	glBlitFramebuffer(sx0, sy0, sx1, sy1, dx0, dy0, dx1, dy1, mask, filter);
	if(f)
		f->unbind(GL_DRAW_FRAMEBUFFER);
	unbind(GL_READ_FRAMEBUFFER);
}
