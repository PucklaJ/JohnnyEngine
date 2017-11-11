#include "../include/Window.h"
#include "../include/MainClass.h"
#include "../include/Actor.h"
#include <SDL2/SDL_surface.h>
#include "../include/Texture.h"
#include "../include/ResourceManager.h"
#include "../include/Framework.h"

namespace Johnny
{
    Window::Window(void* handle) :
        m_handle(handle),
        m_mainClass(MainClass::getInstance())
    {
        m_res = getResolution();
    }

    Window::~Window()
    {
        m_mainClass->getFramework()->destroyWindow(this);
        m_handle = nullptr;
    }

    void Window::setFullscreen(bool b,bool desktop)
    {
        bool full = isFullscreen();
        
        if(full && b)
            return;
        else if(full && !b)
            m_mainClass->getFramework()->setWindowFullscreen(this,false,desktop);
        else if(!full && !b)
            return;
        else if(!full && b)
            m_mainClass->getFramework()->setWindowFullscreen(this,true,desktop);
            
        /*Uint32 flags = SDL_GetWindowFlags(m_window);

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
        }*/
        
        m_mainClass->onFullscreen(b);

    }

    void Window::setBorderless(bool b)
    {
        bool borderless = isBorderless();
        
        if(borderless && b)
            return;
        else if(borderless && !b)
            m_mainClass->getFramework()->setWindowBorderless(this,false);
        else if(!borderless && !b)
            return;
        else if(!borderless && b)
            m_mainClass->getFramework()->setWindowBorderless(this,true);
        
        /*Uint32 flags = SDL_GetWindowFlags(m_window);

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
        }*/
    }

    const Vector2i Window::getResolution()
    {
        return m_mainClass->getFramework()->getWindowResolution(this);
    }

    void Window::setTitle(const std::string& title)
    {
        m_mainClass->getFramework()->setWindowTitle(this,title);
    }

    void Window::setResolution(const Vector2i& p )
    {
        m_mainClass->getFramework()->setWindowResolution(this,p);
        m_res = p;
        m_mainClass->onResize(p.width,p.height);
    }

    void Window::setResolution(int w, int h)
    {
        setResolution(Vector2i(w,h));
    }

    void Window::setPosition(const Vector2i& p)
    {
        m_mainClass->getFramework()->setWindowPosition(this,p);
    }

    void Window::setPosition(int x, int y)
    {
        setPosition(Vector2i(x,y));
    }
    
    void Window::setIcon(Texture* tex,GLenum target,GLenum format, GLenum type)
    {
        m_mainClass->getFramework()->setWindowIcon(this,tex,target,format,type);
    }
    
    void Window::setIcon(TextureData* texD)
    {
        m_mainClass->getFramework()->setWindowIcon(this,texD);
    }

    bool Window::isBorderless()
    {
        return m_mainClass->getFramework()->isWindowBorderless(this);
    }

    bool Window::isFullscreen()
    {
        return m_mainClass->getFramework()->isWindowFullscreen(this);
    }
    
    bool Window::swap()
    {
        return m_mainClass->getFramework()->swapWindow(this);
    }
}





