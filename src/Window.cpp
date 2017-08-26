#include "../include/Window.h"
#include "../include/MainClass.h"
#include "../include/Actor.h"
#include <SDL2/SDL_surface.h>
#include "../include/Texture.h"
#include "../include/ResourceManager.h"

namespace Johnny
{
    Window::Window(MainClass* mClass,const char* title,int x,int y,int w,int h,Uint32 flags) :
        m_mainClass(mClass)
    {
        m_window = SDL_CreateWindow(title,x,y,w,h,flags);
        m_res = {w,h};
    }

    Window::~Window()
    {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }

    void Window::setFullscreen(bool b,Uint32 flag)
    {
        Uint32 flags = SDL_GetWindowFlags(m_window);

        if((flags & SDL_WINDOW_FULLSCREEN) && b)
        {
            return;
        }
        else if((flags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_FULLSCREEN_DESKTOP)) && !b)
        {
            SDL_SetWindowFullscreen(m_window,0);
            if(flag == SDL_WINDOW_FULLSCREEN_DESKTOP)
                SDL_SetWindowSize(m_window,m_res.x,m_res.y);
        }
        else if(!(flags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_FULLSCREEN_DESKTOP)) && !b)
        {
            return;
        }
        else
        {
            SDL_SetWindowFullscreen(m_window,flag);
        }
        
        m_mainClass->onFullscreen(b);

    }

    void Window::setBorderless(bool b)
    {
        Uint32 flags = SDL_GetWindowFlags(m_window);

        if((flags & SDL_WINDOW_BORDERLESS) && b)
        {
            return;
        }
        else if((flags & SDL_WINDOW_BORDERLESS) && !b)
        {
            SDL_SetWindowBordered(m_window,SDL_FALSE);
        }
        else if(!(flags & SDL_WINDOW_BORDERLESS) && !b)
        {
            return;
        }
        else
        {
            SDL_SetWindowBordered(m_window,SDL_TRUE);
        }
    }

    const SDL_Point Window::getResolution()
    {
        SDL_Point p;
        SDL_GetWindowSize(m_window,&p.x,&p.y);

        return p;
    }

    void Window::setTitle(const char* title)
    {
        SDL_SetWindowTitle(m_window,title);
    }

    void Window::setResolution(const SDL_Point& p )
    {
        setResolution(p.x,p.y);
    }

    void Window::setResolution(int w, int h)
    {
        SDL_SetWindowSize(m_window,w,h);
        m_res.x = w;
        m_res.y = h;
        m_mainClass->onResize(w,h);
    }

    void Window::setPosition(const SDL_Point& p)
    {
        setPosition(p.x,p.y);
    }

    void Window::setPosition(int x, int y)
    {
        SDL_SetWindowPosition(m_window,x,y);
    }
    
    void Window::setIcon(Texture* tex,GLenum target,GLenum format, GLenum type)
    {
        SDL_Surface* sur = tex->toSDLSurface(target,format,type);
        
        SDL_SetWindowIcon(m_window,sur);
        
        SDL_FreeSurface(sur);
    }
    
    void Window::setIcon(TextureData* texD,Uint32 pixelFormat)
    {
        SDL_Surface* sur = texD->toSDL_Surface(pixelFormat);
        
        SDL_SetWindowIcon(m_window,sur);
        
        SDL_FreeSurface(sur);
    }
    
    void Window::setIcon(SDL_Surface* sur)
    {   
        SDL_SetWindowIcon(m_window,sur);
    }

    bool Window::isBorderless()
    {
        Uint32 flags = SDL_GetWindowFlags(m_window);
        return (flags & SDL_WINDOW_BORDERLESS) != 0;
    }

    bool Window::isFullscreen()
    {
        Uint32 flags = SDL_GetWindowFlags(m_window);
        return (flags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_FULLSCREEN_DESKTOP)) != 0;
    }
    
    SDL_Point Window::getScreenResolution()
    {
        SDL_DisplayMode dm;
        SDL_GetCurrentDisplayMode(0,&dm);
        
        SDL_Point res = {dm.w,dm.h};
        
        return res;
    }
    
    Uint32 Window::getPixelFormat()
    {
        return SDL_GetWindowPixelFormat(m_window);
    }
}





