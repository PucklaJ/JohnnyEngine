#ifndef Window_H
#define Window_H
#include "../include/Actor.h"
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_stdinc.h>
#include <GL/glew.h>

namespace Johnny
{
    class MainClass;
    class Texture;
    class TextureData;
    
    /*! \brief A class which represents a window on a screen 
     *
     */
    class Window
    {
        public:
            /*! \brief Creates a new Window
             *  \param m The MainClass to use for listening to the onFullscreen and onResize events
             *  \param title The title of the Window
             *  \param x The x position on the screen of the Window
             *  \param y The y position on the screen of the Window
             *  \param w The width of the Window in pixels
             *  \param h The height of the Window in pixels
             *  \param flags The WindowFlags for the Window whicch define different things like the resizability
             */
			Window(MainClass* m,const char* title = "Window Title",int x = SDL_WINDOWPOS_CENTERED,int y = SDL_WINDOWPOS_CENTERED,int w = NORM_W,int h = NORM_H,Uint32 flags = SDL_WINDOW_SHOWN);
            virtual ~Window();

            /*! \brief Sets the Window into fullscreen mode or windowed mode
             *  \param full if true the Window goes into fullscreen or stays in fullscreen, if false the Window goes into windowed mode or stays in windowed mode
             *  \param flags The flags for the fullscreen transition
             */
            void setFullscreen(bool full,Uint32 flags = SDL_WINDOW_FULLSCREEN_DESKTOP);
            /*! \brief Sets the window into borderless mode
             *  \param border if true the window switches into borderless mode or stays in borderless mode
             */
            void setBorderless(bool border);
            /*! \brief Sets the title of the Window
             *  \param title The title of the Window
             */
            void setTitle(const char* title);
            /*! \brief Sets the resolution of the Window
             *  \param res The new resolution
             */
            void setResolution(const SDL_Point& res);
            /*! \brief Sets the resolution of the Window
             *  \param w The new width of the Window in pixels
             *  \param h The new height of the Window in pixels
             */
            void setResolution(int w,int h);
            /*! \brief Sets the position of the Window on the screen
             *  \param pos The new position
             */
            void setPosition(const SDL_Point& pos);
             /*! \brief Sets the position of the Window on the screen
             *  \param x The new x position
             *  \param y The new y position
             */
            void setPosition(int x,int y);
            /*! \brief Sets the icon of the Window
             *  \param tex The texture to use as icon
             *  \param target The target to which the Texture should be bound
             *  \param format The pixel format of the Texture
             *  \param type The type in which the pixel channels of the Texture are stored
             */
            void setIcon(Texture* tex,GLenum target = GL_TEXTURE_2D,GLenum format = GL_RGBA, GLenum type = GL_UNSIGNED_BYTE);
            /*! \brief Sets the icon of the Window
             *  \param tex The TextureData to use as icon
             *  \param pixelformat The SDL_Pixelformat with which the pixels are stored
             */
            void setIcon(TextureData* tex,Uint32 pixelFormat = SDL_PIXELFORMAT_RGBA8888);
            /*! \brief Sets the icon of the Window
             *  \param sur The SDL_Surface to use as icon
             */
            void setIcon(SDL_Surface* sur);

            /*! \brief Gets the SDL_Window handle
             *  \return The SDL_Window of the Window
             */
            SDL_Window* getWindow() {return m_window;}
            /*! \return The resolution of the Window
             *
             */
            const SDL_Point getResolution();
            /*! \return The SDL_Pixelformat of the Window
             *
             */
            Uint32 getPixelFormat();
            /*! \brief Checks if the Window is borderless
             *  \return true if the Window is borderless and false otherwhise
             */
            bool isBorderless();
            /*! \brief Checks if the Window is in fullscreen
             *  \return true if the Window is in fullscreen and false otherwhise
             */
            bool isFullscreen();
            
            /*! \return The resolution of the screen (not the window)
             *
             */
            static SDL_Point getScreenResolution();
        private:
            SDL_Window* m_window;   //!< The SDL_Window handle
            MainClass* m_mainClass; //!< The MainClass which was passed through the constructor
            SDL_Point m_res;        //!< The resolution of the Window
    };
}


#endif // Window_H
