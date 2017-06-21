#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <string>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

class Shader;
class Mesh;

namespace SDL
{
	class MainClass;
}

class Texture
{
public:
	static Mesh* createTexturePlane(GLfloat,GLfloat);
	static Texture* SDL_SurfaceToTexture(SDL_Surface*);
	static void initTexture2DShader(SDL::MainClass*);
	static void initTexture2DBuffers();
	static void renderTexture2D(Texture*, const glm::vec2&, GLsizei, GLsizei);

	static Shader* getTexture2DShader();

	Texture(GLubyte*,GLsizei,GLsizei,GLint internalFormat = GL_RGBA,GLenum format = GL_RGBA,GLenum type = GL_UNSIGNED_BYTE,GLenum target = GL_TEXTURE_2D);
	Texture();
	~Texture();

	void bind(Shader*,const std::string& name = "textureAddress",GLuint unit = 0,GLenum target = GL_TEXTURE_2D);
	void unbind(GLuint unit = 0,GLenum target = GL_TEXTURE_2D);

	GLuint getBuffer() { return m_texture; }

protected:
	static Shader* m_texture2DShader;
	static GLuint m_texture2D_vbo;
	static GLuint m_texture2D_vao;

	GLuint m_texture = 0;

};

#endif

