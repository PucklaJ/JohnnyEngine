#include "../include/Texture.h"
#include <iostream>
#include "../include/Shader.h"
#include "../include/Mesh3D.h"
#include "../include/Vertex3D.h"
#include "../include/LogManager.h"
#include <SDL2/SDL.h>
#include "../include/ResourceManager.h"
#include "../include/MainClass.h"
#include "../include/RenderManager.h"
#include "../include/Matrix4.h"
#include "../include/Camera2D.h"
#include "../include/Transform2D.h"
#include "../include/Geometry.h"
#include "../include/Sprite2D.h"

namespace Johnny
{
    const unsigned int Texture2DShaderUpdater::TRANSFORM_NORMAL=0;
    const unsigned int Texture2DShaderUpdater::TRANSFORM_CAMERA=1;

    void Texture2DShaderUpdater::update()
    {
        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT,viewport);
        
        m_shader->setUniform("viewportSize", Vector2f(viewport[2],viewport[3]));
    }
    
    void Texture2DShaderUpdater::setUniforms(Transform2D* m,unsigned int index)
    {
        switch(index)
        {
            case TRANSFORM_NORMAL:
                m_shader->setUniform("transform",m->getTransformation());
                break;
            case TRANSFORM_CAMERA:
                m_shader->setUniform("transform",m->getProjectedTransformation(MainClass::getInstance()->getCamera2D()));
                break;
        }
    }
    
    void Texture2DShaderUpdater::setUniforms(Texture* m,unsigned int index)
    {
        m->bind(m_shader);
    }
    
    void Texture2DShaderUpdater::setUniforms(TextureRegion* m,unsigned int index)
    {
        m_shader->setUniform("textureRegion", *m);
    }
    
    void Texture2DShaderUpdater::setUniforms(Sprite2D* m,const unsigned int index)
    {
        Texture::renderSprite2D();
    }
    
	Shader* Texture::m_texture2DShader = nullptr;
	GLuint Texture::m_texture2D_vbo = 0;
	GLuint Texture::m_texture2D_vao = 0;

	Mesh3D* Texture::createTexturePlane(GLfloat width, GLfloat height)
	{
		Mesh3D* mesh = new Mesh3D();

		Vertex3D* vertices = new Vertex3D[4];
		GLuint* indices = new GLuint[6];

		vertices[0].pos = glm::vec3(-width / 2.0f, -height / 2.0f, 0.0f);
		vertices[0].normal = glm::vec3(0.0, 0.0, 1.0);
		vertices[0].uv = glm::vec2(0.0, 0.0);

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

		mesh->addVertices(vertices, 4, indices, 6);
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

	void Texture::initTexture2DShader(MainClass* mainClass)
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
            m_texture2DShader->setShaderUpdater<Texture2DShaderUpdater>();

			m_texture2DShader->addUniform("transform");
			m_texture2DShader->addUniform("textureAddress");
			m_texture2DShader->addUniform("viewportSize");
			m_texture2DShader->addUniform("textureRegion");

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
				LogManager::error("Couldn't generate Texture2DVBO", true, true, false);
				return;
			}
			glGenVertexArrays(1, &m_texture2D_vao);
			if (m_texture2D_vao == 0)
			{
				LogManager::error("Couldn't generate Texture2DVAO", true, true, false);
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

	void Texture::renderTexture2D(Texture* tex, const Matrix3f& transformation,const TextureRegion* srcRegion,bool bindShader)
	{
		if (m_texture2D_vbo != 0 && m_texture2D_vao != 0 && m_texture2DShader)
		{
            GLint viewport[4];
            glGetIntegerv(GL_VIEWPORT,viewport);
            
			if(bindShader)
				m_texture2DShader->bind();
			m_texture2DShader->setUniform("transform", transformation);
			m_texture2DShader->setUniform("viewportSize", Vector2f(viewport[2],viewport[3]));
			m_texture2DShader->setUniform("textureRegion", srcRegion ? *srcRegion : TextureRegion(0, 0, tex->getWidth(), tex->getHeight()));
			tex->bind(m_texture2DShader);

			glBindVertexArray(m_texture2D_vao);

			glDrawArrays(GL_POINTS, 0, 1);

			glBindVertexArray(0);
		}

	}

	void Texture::renderTexture2D(Texture* tex, const Vector2f& position, const Vector2f& scale, const GLfloat& rotation, const Camera2D* cam,const TextureRegion* srcRegion, bool bindShader)
	{
		if (m_texture2D_vbo != 0 && m_texture2D_vao != 0 && m_texture2DShader)
		{
			Vector2f newPos = TransformableObject2D::fromCoords(position) + Vector2f((GLfloat)tex->getWidth() / 2.0f * scale.x, (GLfloat)tex->getHeight() / 2.0f * scale.y) + TransformableObject2D::getCenter();
			Matrix3f transformation = cam ? (cam->getViewMatrix()*Matrix3f::translate(newPos)) : Matrix3f::translate(newPos);

			if (scale.x != 1.0f || scale.y != 1.0f)
				transformation *= Matrix3f::scale(scale);
			if (rotation != 0.0f && (GLint)rotation % 360 != 0)
				transformation *= Matrix3f::rotate(rotation);
				

			if(bindShader)
				m_texture2DShader->bind();
			m_texture2DShader->setUniform("transform", transformation);
			m_texture2DShader->setUniform("viewportSize", MainClass::getInstance()->getNativeRes());
			m_texture2DShader->setUniform("textureRegion", srcRegion ? *srcRegion : TextureRegion(0,0,tex->getWidth(),tex->getHeight()));
			//m_texture2DShader->setUniform("scale", scale);
			tex->bind(m_texture2DShader);

			glBindVertexArray(m_texture2D_vao);

			glDrawArrays(GL_POINTS, 0, 1);

			glBindVertexArray(0);
		}
	}
    
    void Texture::renderSprite2D()
    {
        glBindVertexArray(m_texture2D_vao);

        glDrawArrays(GL_POINTS, 0, 1);

        glBindVertexArray(0);
    }

	Shader* Texture::getTexture2DShader()
	{
		return m_texture2DShader;
	}

	Texture::Texture(GLubyte* pixels, GLsizei width, GLsizei height,GLenum filtering, GLint internalFormat, GLenum format, GLenum type, GLenum target) : Texture()
	{
		if (m_texture != 0)
		{
			glBindTexture(target, m_texture);

			glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			glTexParameteri(target, GL_TEXTURE_MIN_FILTER, filtering);
			glTexParameteri(target, GL_TEXTURE_MAG_FILTER, filtering);

			if (target == GL_TEXTURE_2D_MULTISAMPLE)
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 8, internalFormat, width, height, GL_TRUE);
			else
				glTexImage2D(target, 0, internalFormat, width, height, 0, format, type, (pixels ? pixels : nullptr));

			if (pixels)
				glGenerateMipmap(target);

			glBindTexture(target, 0);
		}
	}

	Texture::Texture()
	{
		glGenTextures(1, &m_texture);

		if (m_texture == 0)
		{
			LogManager::error("Couldn't generate Texture Buffer", true, true, false);
		}
	}


	Texture::~Texture()
	{
		if (m_texture != 0)
		{
			glDeleteTextures(1, &m_texture);
		}
	}

	void Texture::bind(Shader* s, const std::string& name, GLuint unit, GLenum target)
	{
		if (m_texture != 0)
		{
			glActiveTexture(GL_TEXTURE0 + unit);
			glBindTexture(target, m_texture);

			s->setUniform(name, (GLint)unit);
		}

	}

	void Texture::unbind(GLuint unit, GLenum target)
	{
		if (m_texture != 0)
		{
			glActiveTexture(GL_TEXTURE0 + unit);
			glBindTexture(target, 0);
		}
	}

	GLsizei Texture::getWidth()
	{
		if (m_width == 0)
		{
			glBindTexture(GL_TEXTURE_2D, m_texture);
			glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &m_width);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		

		return m_width;
	}

	GLsizei Texture::getHeight()
	{
		if (m_height == 0)
		{
			glBindTexture(GL_TEXTURE_2D, m_texture);
			glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &m_height);
			glBindTexture(GL_TEXTURE_2D, 0);
		}


		return m_height;
	}

}