#ifndef Window_H
#define Window_H
#include "../include/Actor.h"
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_stdinc.h>
#include "../include/Vector2.h"
#include <GL/glew.h>

namespace Johnny
{
    class MainClass;
    class Texture;
    class TextureData;
    class Framework;
    
    /*! \brief A class which represents a window on a screen 
     *
     */
    class Window
    {
        public:
			Window(void* handle);
            virtual ~Window();

            /*! \brief Sets the Window into fullscreen mode or windowed mode
             *  \param full if true the Window goes into fullscreen or stays in fullscreen, if false the Window goes into windowed mode or stays in windowed mode
             *  \param flags The flags for the fullscreen transition
             */
            void setFullscreen(bool full = true,bool desktop = true);
            /*! \brief Sets the window into borderless mode
             *  \param border if true the window switches into borderless mode or stays in borderless mode
             */
            void setBorderless(bool border = true);
            /*! \brief Sets the title of the Window
             *  \param title The title of the Window
             */
            void setTitle(const std::string& title);
            /*! \brief Sets the resolution of the Window
             *  \param res The new resolution
             */
            void setResolution(const Vector2i& res);
            /*! \brief Sets the resolution of the Window
             *  \param w The new width of the Window in pixels
             *  \param h The new height of the Window in pixels
             */
            void setResolution(int w,int h);
            /*! \brief Sets the position of the Window on the screen
             *  \param pos The new position
             */
            void setPosition(const Vector2i& pos);
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
             */
            void setIcon(TextureData* tex);
            /*! \return The resolution of the Window
             *
             */
            const Vector2i getResolution();
            /*! \brief Checks if the Window is borderless
             *  \return true if the Window is borderless and false otherwhise
             */
            bool isBorderless();
            /*! \brief Checks if the Window is in fullscreen
             *  \return true if the Window is in fullscreen and false otherwhise
             */
            bool isFullscreen();
            
            void setHandle(void* handle) {m_handle = handle;}
            void* getHandle() {return m_handle;}
            
            bool swap();
            
        private:
            MainClass* m_mainClass = nullptr; //!< The MainClass which was passed through the constructor
            Vector2i m_res;        //!< The resolution of the Window
            void* m_handle = nullptr; //!< The handle of the window of the framework
    };
}


#endif // Window_H
