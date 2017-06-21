#include "TextActor.h"
#include "MainClass.h"
#include <iostream>
#include "Texture.h"

namespace SDL
{
    TextActor::TextActor(TTF_Font* font,const SDL_Color& color,const std::string& text) : Actor("TextActor"),
        m_text(text),
        m_font(font),
        m_color(color)
    {
        setName(text.c_str());
		m_castsShadows = false;
    }
    
    TextActor::~TextActor()
    {
        
    }
    
    bool TextActor::init()
    {
		Texture::initTexture2DShader(m_mainClass);
		Texture::initTexture2DBuffers();

		setShader(Texture::getTexture2DShader());

        generateText();
        return true;
    }
    
    bool TextActor::update()
    {
        if(m_needsUpdate)
        {
            generateText();
            m_needsUpdate = false;
        }
        return true;
    }

	bool TextActor::render()
	{
		Texture::renderTexture2D(m_texture, glm::vec2(m_transform.getTranslation()), m_textureWidth, m_textureHeight);

		return true;
	}
    
    void TextActor::generateText()
    {
        if(m_mainClass)
        {
            if(m_texture)
            {
                delete m_texture;
                m_texture = nullptr;
            }
            
			SDL_Surface* sur = TTF_RenderText_Blended_Wrapped(m_font, m_text.c_str(), m_color, INT_MAX);

			m_textureWidth = sur->w;
			m_textureHeight = sur->h;
			m_texture = Texture::SDL_SurfaceToTexture(sur);

            SDL_FreeSurface(sur);
            
        }
        
    }
    
}
