#include "Texture.h"
#include <iostream>
#include "Shader.h"
#include "Mesh.h"
#include "Vertex.h"
#include "LogManager.h"
#include <SDL2/SDL.h>
#include "ResourceManager.h"
#include "MainClass.h"
#include "RenderManager.h"

Shader* Texture::m_texture2DShader = nullptr;
GLuint Texture::m_texture2D_vbo = 0;
GLuint Texture::m_texture2D_vao = 0;

Mesh* Texture::createTexturePlane(GLfloat width, GLfloat height)
{
	Mesh* mesh = new Mesh();

	Vertex* vertices = new Vertex[4];
	GLuint* indices = new GLuint[6];

	vertices[0].pos = glm::vec3(-width/2.0f,-height/2.0f,0.0f);
	vertices[0].normal = glm::vec3(0.0, 0.0, 1.0);
	vertices[0].uv = glm::vec2(0.0,0.0);

	vertices[1].pos = glm::vec3(width / 2.0f, -height / 2.0f, 0.0f);
	vertices[1].normal = glm::vec3(0.0, 0.0, 1.0);
	vertices[1].uv = glm::vec2(1.0, 0.0);

	vertices[2].pos = glm::vec3(width / 2.0f, height / 2.0f, 0.0f);
	vertices[2].normal = glm::vec3(0.0, 0.0, 1.0);
	vertices[2].uv = glm::vec2(1.0, 1.0);

	vertices[3].pos = glm::vec3(-width / 2.0f, height / 2.0f, 0.0f);
	vertices[3].normal = glm::vec3(0.0, 0.0, 1.0);
	vertices[3].uv = glm::vec2(0.0, 1.0);

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 2;
	indices[4] = 3;
	indices[5] = 0;

	mesh->addVertices(vertices,4,indices,6);
	delete[] vertices;
	delete[] indices;

	return mesh;
}

Texture * Texture::SDL_SurfaceToTexture(SDL_Surface* sur)
{
	GLenum mode = sur->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB;
	Texture* tex = new Texture((GLubyte*)sur->pixels, sur->w, sur->h, mode, mode, GL_UNSIGNED_BYTE, GL_TEXTURE_2D);

	return tex;
}

void Texture::initTexture2DShader(SDL::MainClass* mainClass)
{
	if (!m_texture2DShader)
	{
		m_texture2DShader = new Shader();
		m_texture2DShader->setLoadDefaultUniforms(false);

		m_texture2DShader->addVertexShader(mainClass->getResourceManager()->loadShader("vertexShaderTexture2D.glsl"));
		m_texture2DShader->addGeometryShader(mainClass->getResourceManager()->loadShader("geometryShaderTexture2D.glsl"));
		m_texture2DShader->addFragmentShader(mainClass->getResourceManager()->loadShader("fragmentShaderTexture2D.glsl"));

		m_texture2DShader->addAttribute("position", 0);

		m_texture2DShader->link();

		m_texture2DShader->addUniform("width");
		m_texture2DShader->addUniform("height");
		m_texture2DShader->addUniform("offset");
		m_texture2DShader->addUniform("textureAddress");

		mainClass->getRenderManager()->addShader(m_texture2DShader);
	}
	
}

void Texture::initTexture2DBuffers()
{
	if (m_texture2D_vbo == 0)
	{
		glGenBuffers(1, &m_texture2D_vbo);
		if (m_texture2D_vbo == 0)
		{
			SDL::LogManager::error("Couldn't generate Texture2DVBO",true,true,false);
			return;
		}
		glGenVertexArrays(1, &m_texture2D_vao);
		if (m_texture2D_vao == 0)
		{
			SDL::LogManager::error("Couldn't generate Texture2DVAO",true,true,false);
			return;
		}

		glm::vec2 pos(0.0, 0.0);

		glBindBuffer(GL_ARRAY_BUFFER, m_texture2D_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2), &pos, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(m_texture2D_vao);

		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, m_texture2D_vbo);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), 0);

		glBindVertexArray(0);
	}
}

void Texture::renderTexture2D(Texture* tex, const glm::vec2& pos, GLsizei w, GLsizei h)
{
	if (m_texture2D_vbo != 0 && m_texture2D_vao != 0 && m_texture2DShader)
	{
		GLint params[4];
		glGetIntegerv(GL_VIEWPORT, params);

		m_texture2DShader->bind();
		m_texture2DShader->setUniformVec2("offset", glm::vec2(pos.x / (GLfloat)params[2] * 2.0f - 1.0f, pos.y / (GLfloat)params[3] * 2.0f - 1.0f));
		m_texture2DShader->setUniformf("width", (GLfloat)w / (GLfloat)params[2] * 2.0f);
		m_texture2DShader->setUniformf("height", (GLfloat)h / (GLfloat)params[3] * 2.0f);
		tex->bind(m_texture2DShader);

		glBindVertexArray(m_texture2D_vao);

		glDrawArrays(GL_POINTS, 0, 1);

		glBindVertexArray(0);
	}
	
}

Shader* Texture::getTexture2DShader()
{
	return m_texture2DShader;
}

Texture::Texture(GLubyte* pixels, GLsizei width, GLsizei height, GLint internalFormat, GLenum format, GLenum type, GLenum target) : Texture()
{
	if(m_texture != 0)
	{
		glBindTexture(target, m_texture);

		glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameterf(target,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameterf(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (target == GL_TEXTURE_2D_MULTISAMPLE)
			glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 8, internalFormat, width, height, GL_TRUE);
		else
			glTexImage2D(target, 0, internalFormat, width, height, 0, format, type, (pixels ? pixels : nullptr));

		if(pixels)
			glGenerateMipmap(target);

		glBindTexture(target,0);
	}
}

Texture::Texture()
{
	glGenTextures(1, &m_texture);

	if (m_texture == 0)
	{
		SDL::LogManager::error("Couldn't generate Texture Buffer",true,true,false);
	}
}


Texture::~Texture()
{
	if (m_texture != 0)
	{
		glDeleteTextures(1,&m_texture);
	}
}

void Texture::bind(Shader* s,const std::string& name,GLuint unit,GLenum target)
{
	if (m_texture != 0)
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(target, m_texture);

		s->setUniformi(name, (GLint)unit);
	}
	
}

void Texture::unbind(GLuint unit,GLenum target)
{
	if (m_texture != 0)
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(target, 0);
	}
}
