#include "RenderBuffer.h"
#include <iostream>


RenderBuffer::RenderBuffer(GLsizei width, GLsizei height, GLenum format,GLenum target,bool multisampling)
{
	glGenRenderbuffers(1, &m_rbo);
	if (m_rbo == 0)
	{
		std::cerr << "Couldn't create RenderBuffer" << std::endl;
	}
	else
	{
		bind(target);
		if(multisampling)
			glRenderbufferStorageMultisample(target,8, format, width, height);
		else
			glRenderbufferStorage(target, format, width, height);
		unbind(target);
	}
}


RenderBuffer::~RenderBuffer()
{
	if (m_rbo != 0)
	{
		glDeleteRenderbuffers(1, &m_rbo);
	}
}

void RenderBuffer::bind(GLenum target)
{
	glBindRenderbuffer(target, m_rbo);
}

void RenderBuffer::unbind(GLenum target)
{
	glBindRenderbuffer(target, 0);
}
