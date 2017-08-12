#include "../include/TextActor2D.h"
#include "../include/MainClass.h"
#include <iostream>
#include "../include/Texture.h"
#include "../include/Camera2D.h"

namespace Johnny
{
	TextActor2D::TextActor2D(TTF_Font* font,const SDL_Color& color,const std::string& text) : Sprite2D(),
        m_text(text),
        m_font(font),
        m_color(color)
    {
        setName(text.c_str());
    }
    
	TextActor2D::~TextActor2D()
    {
        
    }
    
    bool TextActor2D::init()
    {
		Sprite2D::init();

        generateText();

        return true;
    }
    
    bool TextActor2D::update()
    {
		Sprite2D::update();

        if(m_needsUpdate)
        {
            generateText();
            m_needsUpdate = false;
        }
        return true;
    }

	void TextActor2D::generateText()
    {
        if(m_mainClass)
        {
			if (m_texture)
			{
				delete m_texture;
				m_texture = nullptr;
			}
            
			SDL_Surface* sur = TTF_RenderText_Blended_Wrapped(m_font, m_text.c_str(), m_color, INT_MAX);

			setTexture(Texture::SDL_SurfaceToTexture(sur));

            SDL_FreeSurface(sur);
        }
        
    }
    
}
