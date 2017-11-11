#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include "Vector2.h"
#include <GL/glew.h>
#include "Events.h"
#include "JoystickListener.h"

#define ERROR_OUT(func,errorText) if(func<0)Johnny::LogManager::error(std::string(errorText) + MainClass::getInstance()->getFramework()->getError())

namespace Johnny
{
    typedef unsigned int WindowFlags;
    typedef unsigned int FrameworkInitFlags;
    
    enum FlagsWindow : WindowFlags
    {
        Fullscreen = 1 << 0,
        Fullscreen_Desktop = 1 << 1,
        OpenGL = 1 << 2,
        Shown = 1 << 3,
        Hidden = 1 << 4,
        Borderless = 1 << 5,
        Resizeable = 1 << 6,
        Minimized = 1 << 7,
        Maximized = 1 << 8,
        Input_Grapped = 1 << 9,
        Input_Focus = 1 << 10,
        Mouse_Focus = 1 << 11,
        Foreign = 1 << 12,
        Allow_HighDPI = 1 << 13,
        Mouse_Capture = 1 << 14,
        Always_On_Top = 1 << 15,
        Skip_Taskbar = 1 << 16,
        Utility = 1 << 17,
        Tooltip = 1 << 18,
        Popup_Menu = 1 << 19
    };
    
    enum FlagsInitFramework : FrameworkInitFlags
    {
        Measure_Time = 1 << 0,
        Audio = 1 << 1,
        Events = 1 << 6,
        Video = 1 << 2 | Events,
        Joystick = 1 << 3 | Events,
        Haptic = 1 << 4,
        GameController = 1 << 5 | Joystick,
        NoParachute = 1 << 7,
        Everything = Measure_Time | Audio | Video | Joystick | Haptic | GameController | Events | NoParachute
    };
    
    enum class Frameworks
    {
        SDL,
        GLFW
    };
    
    class Window;
    class Texture;
    class TextureData;
    class Event;
    
    class Framework
    {
    public:
        static Framework* createFramework(Frameworks fw); 
    
        virtual bool init(FrameworkInitFlags flags) = 0;
        virtual bool quit() = 0;
        virtual bool initWindow() = 0;
        virtual bool initGraphics() = 0;
        virtual bool createOpenGLContext() = 0;
        
        /*! \brief Creates a new Window
         *  \param title The title of the Window
         *  \param x The x position on the screen of the Window
         *  \param y The y position on the screen of the Window
         *  \param w The width of the Window in pixels
         *  \param h The height of the Window in pixels
         *  \param flags The WindowFlags for the Window which define different things like the resizability
         */
        virtual Window* createWindow(const std::string& title,unsigned int x,unsigned int y,unsigned int w,unsigned int h,WindowFlags flags) = 0;
        virtual bool swapWindow(Window* window) = 0;
        virtual bool destroyWindow(Window* window) = 0;
        
        virtual std::string getError() = 0;
        
        virtual bool pollEvent() = 0;
        
        virtual bool setWindowTitle(Window* window,const std::string& title) = 0;
        virtual bool setWindowResolution(Window* window,const Vector2i& res) = 0;
        virtual bool setWindowPosition(Window* window,const Vector2i& pos) = 0;
        virtual bool setWindowFullscreen(Window* window,bool fullscreen = true,bool desktop = true) = 0;
        virtual bool setWindowBorderless(Window* window,bool borderless = true) = 0;
        virtual bool setWindowIcon(Window* window,Texture* tex,GLenum target = GL_TEXTURE_2D,GLenum format = GL_RGBA, GLenum type = GL_UNSIGNED_BYTE) = 0;
        virtual bool setWindowIcon(Window* window,TextureData* texdata) = 0;
        
        virtual std::string getWindowTitle(Window* window) = 0;
        virtual Vector2i getWindowResolution(Window* window) = 0;
        virtual Vector2i getScreenResolution() = 0;
        virtual bool isWindowFullscreen(Window* window) = 0;
        virtual bool isWindowBorderless(Window* window) = 0;
        
        virtual int getControllerID(void* handle) = 0;
        virtual bool isSameController(void* handle1,void* handle2) = 0;
        virtual void* openController(int id) = 0;
        virtual void closeController(void* handle) = 0;
        virtual bool isAttachedController(void* handle)=0;
        
        Event event;
    };
}

#endif