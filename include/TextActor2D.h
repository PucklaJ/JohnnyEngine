#ifndef TEXTACTOR_H
#define TEXTACTOR_H
#include "../include/Actor.h"
#include <GL/glew.h>
#ifdef __LINUX__
    #include <SDL2/SDL_ttf.h>
#else
#ifdef _WIN32
    #include <TTF/SDL_ttf.h>
#else
    #include <SDL2_ttf/SDL_ttf.h>
#endif
#endif
#include <string>
#include "../include/Transform2D.h"



namespace Johnny
{
	class Texture;

    class TextActor2D : public Actor
    {
    public:
		TextActor2D(TTF_Font*,const SDL_Color& color = {0,0,0,255},const std::string& text = "");
        ~TextActor2D();
        
        bool init() override;
        bool update() override;
		bool render() override;
        
        void setText(const std::string& str){m_text = str;m_needsUpdate = true;setName(str.c_str());}
        void setColor(const SDL_Color& color){m_color = color;m_needsUpdate = true;}
        void setFont(TTF_Font* font){m_font = font;m_needsUpdate = true;}
        
        const std::string& getText() const {return m_text;}
        const SDL_Color& getColor() const {return m_color;}
        TTF_Font* getFont() {return m_font;}
		Transform2D& getTransform() { return m_transform; }
		Texture* getTexture() { return m_texture; }
        
    private:
        void generateText();
		Transform2D m_transform;

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