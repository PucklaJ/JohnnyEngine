#pragma once
#include <GL/glew.h>

namespace Johnny
{
	/*! \brief A object-oriented implemantation of the render buffer object
	 *
	 */
	class RenderBuffer
	{
	public:
		/*! \brief Creates a new RenderBuffer
		 *  \param width The width of the RenderBuffer in pixels
		 *  \param height The height of the RenderBuffer in pixels
		 *  \param format The format of the RenderBuffer in which the bits are interpreted
		 *  \param target The target to which the render buffer object gets bound
		 *  \param multisample Defines wether it should be a multisampling buffer or not
		 */
		RenderBuffer(GLsizei width, GLsizei height, GLenum format = GL_DEPTH24_STENCIL8, GLenum target = GL_RENDERBUFFER, bool multisampling = false);
		~RenderBuffer();

		/*! \brief Binds the render buffer object
		 *  \param target The target to which the render buffer object gets bound
		 */
		void bind(GLenum target = GL_RENDERBUFFER);
		/*! \brief Unbinds the render buffer object
		 *  \param target The target from which it should be unbound
		 */
		void unbind(GLenum target = GL_RENDERBUFFER);

		/*! \return The name of the render buffer object
		 *
		 */
		GLuint getBuffer() { return m_rbo; }
	private:
		GLuint m_rbo = 0; //!< The name of the render buffer object
	};
}



