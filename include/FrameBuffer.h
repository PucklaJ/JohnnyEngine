#pragma once
#include <GL/glew.h>

namespace Johnny
{
	class Texture;
	class RenderBuffer;

	/*! \brief a object-oriented implementation of a frame buffer object
	 *		  to make it easier to use
	 *
	 */
	class FrameBuffer
	{
	public:
		FrameBuffer();
		~FrameBuffer();

		/*! \brief Attaches a texture to the frame buffer object 
		 * \param tex The texture to add
		 * \param attachment The attachment to add the texture to
		 * \param target The target to which the frame buffer object should be bound
		 * \param textureTarget The target to which the texture should be bound
		 */
		void addTexture(Texture* tex, GLuint attachment = GL_COLOR_ATTACHMENT0, GLenum target = GL_FRAMEBUFFER, GLenum textureTarget = GL_TEXTURE_2D);
		/*! \brief Attaches a render buffer the frame buffer object
		 * \param rb The render buffer to attach
		 * \param attachment The attachment to add the render buffer to
		 * \param target The target to which the frame buffer object should be bound
		 */
		void addRenderBuffer(RenderBuffer* rb, GLuint attachment = GL_DEPTH_STENCIL_ATTACHMENT, GLenum target = GL_FRAMEBUFFER);
		/*! \brief Checks if the frame buffer object is completed
		 * \param target The target to which the frame buffer object should be bound
		 * \return Wether the frame buffer object is completed
		 */
		bool checkStatus(GLenum target = GL_FRAMEBUFFER);
		/*! \brief Binds the frame buffer object
		 * \param target The target to which the frame buffer object should be bound
		 */
		void bind(GLenum target = GL_FRAMEBUFFER);
		/*! \brief Unbinds the frame buffer object
		 * \param target The target which should be unbound
		 */
		void unbind(GLenum target = GL_FRAMEBUFFER);
		/*! \brief Blits this frame buffer on another one
		 * \param f The frame buffer on which this frame buffer should be blitted
		 * \param sx0 The x coordinate of the rectangle from which to take from this frame buffer
		 * \param sy0 The y coordinate of the rectangle from which to take from this frame buffer
		 * \param sx1 The width of the rectangle from which to take from this frame buffer
		 * \param sy1 The height of the rectangle from which to take from this frame buffer
		 * \param dx0 The x coordinate of the rectangle on which to blit on the other frame buffer
		 * \param dy0 The y coordinate of the rectangle on which to blit on the other frame buffer
		 * \param dx1 The width of the rectangle on which to blit on the other frame bufferr
		 * \param dy1 The height of the rectangle on which to blit on the other frame buffer
		 * \param mask Which mask to blit
		 * \param filter Defines how the pixels should be filtered
		 */
		void blit(FrameBuffer* f, GLint sx0, GLint sy0, GLint sx1, GLint sy1, GLint dx0, GLint dy0, GLint dx1, GLint dy1, GLbitfield mask = GL_COLOR_BUFFER_BIT, GLenum filter = GL_LINEAR);

		/*! \return The name of the frame buffer object
		 *
		 */
		GLuint getBuffer() { return m_fbo; }

	private:
		GLuint m_fbo = 0; //!< The name of the frame buffer object
	};
}

