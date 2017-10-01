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

    /*! \brief A class which represents a text rendered to the screen
     *
     */
    class TextActor2D : public Sprite2D
    {
    public:
        /*! \brief Creates a new TextActor2D
         *  \param font The font to use for the text
         *  \param color The color of the text
         *  \param text The text which will be rendered
         */
		TextActor2D(TTF_Font* font,const SDL_Color& color = {0,0,0,255},const std::string& text = "");
        ~TextActor2D();
        
        /*! \brief The init method
         *
         *
         * It is overriding the method from Sprite2D
         */
        bool init() override;
        /*! \brief The update method
         *
         *
         * It is overriding the method from Sprite2D
         */
        bool update() override;
		/*! \brief The quit method
		 *
		 *
		 * It is overriding the method from Sprite2D
		 */
		void quit() override;
        /*! \brief Sets the text which will be rendered
         *  \param str The text which will e rendered
         */
        void setText(const std::string& str){m_text = str;m_needsUpdate = true;setName(str.c_str());}
        /*! \brief Sets the color of the text
         *  \param color The color to set
         */
        void setColor(const SDL_Color& color){m_color = color;m_needsUpdate = true;}
        /*! \brief Sets the font of the text
         *  \param font The font to set
         */
        void setFont(TTF_Font* font){m_font = font;m_needsUpdate = true;}
        
        /*! \return The text which is rendered
         *
         */
        const std::string& getText() const {return m_text;}
        /*! \return The color of the text
         *
         */
        const SDL_Color& getColor() const {return m_color;}
        /*! \return The font of the text
         *
         */
        TTF_Font* getFont() {return m_font;}
        
    private:
        /*! \brief Generates the text as a texture
         *
         */
        void generateText();

        std::string m_text = "";    //!< The text which will be rendered
        TTF_Font* m_font = nullptr; //!< The font of the text
        SDL_Color m_color;          //!< The color of the text
        bool m_needsUpdate = false; //!< true if the text, font or color has been updated
    };
}


#endif
