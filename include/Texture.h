#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <string>
#include <SDL2/SDL.h>
#include "Matrix3.h"
#include "Vector2.h"



namespace Johnny
{
	class MainClass;
	class Shader;
	class Mesh3D;
	class Camera2D;

	class Texture
	{
	public:
		static Mesh3D* createTexturePlane(GLfloat, GLfloat);
		static Texture* SDL_SurfaceToTexture(SDL_Surface*);
		static void initTexture2DShader(MainClass*);
		static void initTexture2DBuffers();
		static void renderTexture2D(Texture*, const Matrix3f&, bool bindShader = true);
		static void renderTexture2D(Texture*, const Vector2f&, const Vector2f& scale = Vector2f(1.0f,1.0f), const GLfloat& rotation = 0.0f, const Camera2D* cam = nullptr, bool bindShader = true);

		static Shader* getTexture2DShader();

		Texture(GLubyte*, GLsizei, GLsizei, GLint internalFormat = GL_RGBA, GLenum format = GL_RGBA, GLenum type = GL_UNSIGNED_BYTE, GLenum target = GL_TEXTURE_2D);
		Texture();
		~Texture();

		void bind(Shader*, const std::string& name = "textureAddress", GLuint unit = 0, GLenum target = GL_TEXTURE_2D);
		void unbind(GLuint unit = 0, GLenum target = GL_TEXTURE_2D);

		GLuint getBuffer() { return m_texture; }
		GLsizei getWidth();
		GLsizei getHeight();

	protected:
		static Shader* m_texture2DShader;
		static GLuint m_texture2D_vbo;
		static GLuint m_texture2D_vao;

		GLuint m_texture = 0;
		GLsizei m_width = 0;
		GLsizei m_height = 0;

	};
}

#endif

