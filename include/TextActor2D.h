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
		void setPosition(const Vector2f& pos);
		void setPosition(const GLfloat& x, const GLfloat& y);
		void setRotation(const GLfloat&);
		void setScale(const Vector2f&);
		void setScale(const GLfloat&, const GLfloat&);

		void addPosition(const Vector2f& pos);
		void addPosition(const GLfloat& x,const GLfloat& y);
		void addRotation(const GLfloat& x) { setRotation(m_transform.getRotation() + x); }
		void addScale(const Vector2f&);
		void addScale(const GLfloat&,const GLfloat&);
        
        const std::string& getText() const {return m_text;}
        const SDL_Color& getColor() const {return m_color;}
        TTF_Font* getFont() {return m_font;}
		Texture* getTexture() { return m_texture; }
		Vector2f getPosition() const;
		const GLfloat& getRotation() const { return m_transform.getRotation(); }
		const Vector2f& getScale() const { return m_transform.getScale(); }
        
    private:
        void generateText();
		Transform2D m_transform;

        std::string m_text = "";
        TTF_Font* m_font = nullptr;
		Texture* m_texture = nullptr;
        SDL_Color m_color;
        bool m_needsUpdate = false;
    };
}


#endif
