#include "WindowHandle.h"
#include "MainClass.h"
#include "Actor.h"

namespace SDL
{
    WindowHandle::WindowHandle(MainClass* mClass,const char* title,int x,int y,int w,int h,Uint32 flags) :
        m_mainClass(mClass)
    {
        m_window = SDL_CreateWindow(title,x,y,w,h,flags);
        m_res = {w,h};
    }

    WindowHandle::~WindowHandle()
    {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }

    void WindowHandle::setFullscreen(bool b,Uint32 flag)
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

    void WindowHandle::setBorderless(bool b)
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

    const SDL_Point WindowHandle::getResolution()
    {
        SDL_Point p;
        SDL_GetWindowSize(m_window,&p.x,&p.y);

        return p;
    }

    void WindowHandle::setTitle(const char* title)
    {
        SDL_SetWindowTitle(m_window,title);
    }

    void WindowHandle::setResolution(const SDL_Point& p )
    {
        setResolution(p.x,p.y);
    }

    void WindowHandle::setResolution(int w, int h)
    {
        SDL_SetWindowSize(m_window,w,h);
        m_res.x = w;
        m_res.y = h;
        m_mainClass->onResize(w,h);
    }

    void WindowHandle::setPosition(const SDL_Point& p)
    {
        setPosition(p.x,p.y);
    }

    void WindowHandle::setPosition(int x, int y)
    {
        SDL_SetWindowPosition(m_window,x,y);
    }

    bool WindowHandle::isBorderless()
    {
        Uint32 flags = SDL_GetWindowFlags(m_window);
        return (bool)(flags & SDL_WINDOW_BORDERLESS);
    }

    bool WindowHandle::isFullscreen()
    {
        Uint32 flags = SDL_GetWindowFlags(m_window);
        return (bool)(flags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_FULLSCREEN_DESKTOP));
    }
    
    SDL_Point WindowHandle::getScreenResolution()
    {
        SDL_DisplayMode dm;
        SDL_GetCurrentDisplayMode(0,&dm);
        
        SDL_Point res = {dm.w,dm.h};
        
        return res;
    }
    
    Uint32 WindowHandle::getPixelFormat()
    {
        return SDL_GetWindowPixelFormat(m_window);
    }
}





