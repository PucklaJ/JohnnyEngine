#ifndef TEXTACTOR_H
#define TEXTACTOR_H
#include "Actor.h"
#include <GL/glew.h>
#ifdef __LINUX__
    #include <SDL2/SDL_ttf.h>
#else
#ifdef _WIN32
    #include <TTF/SDL_ttf.h>
#else
    #include <SDL2/SDL_ttf.h>
#endif
#endif
#include <string>

class Texture;

namespace SDL
{
    class TextActor : public SDL::Actor
    {
    public:
        TextActor(TTF_Font*,const SDL_Color& color = {0,0,0,255},const std::string& text = "");
        ~TextActor();
        
        bool init() override;
        bool update() override;
		bool render() override;
        
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
		Texture* m_texture = nullptr;
		GLsizei m_textureWidth = 0;
		GLsizei m_textureHeight = 0;
        SDL_Color m_color;
        bool m_needsUpdate = false;
    };
}


#endif