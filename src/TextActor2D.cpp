#include "../include/TextActor2D.h"
#include "../include/MainClass.h"
#include <iostream>
#include "../include/Texture.h"
#include "../include/Camera2D.h"
#include "../include/Transform2D.h"

namespace Johnny
{
	TextActor2D::TextActor2D(TTF_Font* font,const SDL_Color& color,const std::string& text) : Actor("TextActor"),
        m_text(text),
        m_font(font),
        m_color(color)
    {
        setName(text.c_str());
		m_castsShadows = false;
    }
    
	TextActor2D::~TextActor2D()
    {
        
    }
    
    bool TextActor2D::init()
    {
		Texture::initTexture2DShader(m_mainClass);
		Texture::initTexture2DBuffers();

		setShader(Texture::getTexture2DShader());

        generateText();

        return true;
    }
    
    bool TextActor2D::update()
    {
        if(m_needsUpdate)
        {
            generateText();
            m_needsUpdate = false;
        }
        return true;
    }

	bool TextActor2D::render()
	{
		Texture::renderTexture2D(m_texture, m_isAffectedByCamera ? m_transform.getProjectedTransformation(m_mainClass->getCamera2D()) : m_transform.getTransformation());

		return true;
	}

	void TextActor2D::setPosition(const Vector2f& pos)
	{
		if (m_texture)
			m_transform.setTranslation(pos + Vector2f((GLfloat)m_texture->getWidth() / 2.0f, (GLfloat)m_texture->getHeight() / 2.0f) * m_transform.getScale());
		else
			m_transform.setTranslation(pos);
	}

	void TextActor2D::setPosition(const GLfloat& x, const GLfloat& y)
	{
		setPosition(Vector2f(x,y));
	}

	void TextActor2D::setRotation(const GLfloat& rotation)
	{
		m_transform.setRotation(rotation);
	}

	void TextActor2D::setScale(const Vector2f& v)
	{
		if (m_texture)
		{
			m_transform.setTranslation(m_transform.getTranslation() - Vector2f((GLfloat)m_texture->getWidth() / 2.0f, (GLfloat)m_texture->getHeight() / 2.0f)*m_transform.getScale());
			m_transform.setScale(v);
			setPosition(m_transform.getTranslation());
		}
		else
		{
			m_transform.setScale(v);
		}
		
	}

	void TextActor2D::setScale(const GLfloat& x, const GLfloat& y)
	{
		setScale(Vector2f(x,y));
	}

	void TextActor2D::addPosition(const Vector2f& pos)
	{
		m_transform.setTranslation(m_transform.getTranslation() + pos);
	}

	void TextActor2D::addPosition(const GLfloat& x, const GLfloat& y)
	{
		m_transform.setTranslation(m_transform.getTranslation()+Vector2f(x,y));
	}

	void TextActor2D::addScale(const Vector2f& v)
	{
		m_transform.setScale(m_transform.getScale() + v);
	}

	void TextActor2D::addScale(const GLfloat& x, const GLfloat& y)
	{
		m_transform.setScale(m_transform.getScale() + Vector2f(x, y));
	}
    
	Vector2f TextActor2D::getPosition() const
	{
		if (m_texture)
			return m_transform.getTranslation() - Vector2f((GLfloat)m_texture->getWidth() / 2.0f, (GLfloat)m_texture->getHeight() / 2.0f)*m_transform.getScale();
		else
			return m_transform.getTranslation();
	}

	void TextActor2D::generateText()
    {
        if(m_mainClass)
        {
			if(m_texture)
				m_transform.setTranslation(m_transform.getTranslation() - Vector2f((GLfloat)m_texture->getWidth()/2.0f,(GLfloat)m_texture->getHeight()/2.0f)*m_transform.getScale());

            if(m_texture)
            {
                delete m_texture;
                m_texture = nullptr;
            }
            
			SDL_Surface* sur = TTF_RenderText_Blended_Wrapped(m_font, m_text.c_str(), m_color, INT_MAX);

			m_texture = Texture::SDL_SurfaceToTexture(sur);

            SDL_FreeSurface(sur);

			setPosition(m_transform.getTranslation());
        }
        
    }
    
}
