#ifndef TEXTACTOR_H
#define TEXTACTOR_H
#include "../include/Actor.h"
#include <GL/glew.h>
#ifdef __linux__
    #include <SDL2/SDL_ttf.h>
#else
#ifdef _WIN32
    #include <TTF/SDL_ttf.h>
#else
    #include <SDL2_ttf/SDL_ttf.h>
#endif
#endif
#include <string>
#include "Sprite2D.h"



namespace Johnny
{
	class Texture;

    class TextActor2D : public Sprite2D
    {
    public:
		TextActor2D(TTF_Font*,const SDL_Color& color = {0,0,0,255},const std::string& text = "");
        ~TextActor2D();
        
        bool init() override;
        bool update() override;

        void setText(const std::string& str){m_text = str;m_needsUpdate = true;setName(str.c_str());}
        void setColor(const SDL_Color& color){m_color = color;m_needsUpdate = true;}
        void setFont(TTF_Font* font){m_font = font;m_needsUpdate = true;}
        
        const std::string& getText() const {return m_text;}
        const SDL_Color& getColor() const {return m_color;}
        TTF_Font* getFont() {return m_font;}
        
    private:
        void generateText();

        std::string m_text = "";
        TTF_Font* m_font = nullptr;
        SDL_Color m_color;
        bool m_needsUpdate = false;
    };
}


#endif
