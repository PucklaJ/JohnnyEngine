#ifndef WINDOWHANDLE_H
#define WINDOWHANDLE_H
#include "Actor.h"
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_stdinc.h>

namespace SDL
{
    class MainClass;
    
    class WindowHandle
    {
        public:
            WindowHandle(MainClass*,const char* title = "Window Title",int x = SDL_WINDOWPOS_CENTERED,int y = SDL_WINDOWPOS_CENTERED,int w = NORM_W,int h = NORM_H,Uint32 flags = SDL_WINDOW_SHOWN);
            virtual ~WindowHandle();

            void setFullscreen(bool,Uint32 flags = SDL_WINDOW_FULLSCREEN_DESKTOP);
            void setBorderless(bool);
            void setTitle(const char*);
            void setResolution(const SDL_Point&);
            void setResolution(int,int);
            void setPosition(const SDL_Point&);
            void setPosition(int,int);

            SDL_Window* getWindow() {return m_window;}
            const SDL_Point getResolution();
            Uint32 getPixelFormat();
            bool isBorderless();
            bool isFullscreen();
            
            static SDL_Point getScreenResolution();

        protected:

        private:
            SDL_Window* m_window;
            MainClass* m_mainClass;
            SDL_Point m_res;
    };
}


#endif // WINDOWHANDLE_H
