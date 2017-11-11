#include "../include/SDLFramework.h"
#include "../include/Window.h"
#include "../include/LogManager.h"
#include "../include/MainClass.h"
#include "../include/Settings.h"
#include "../include/Texture.h"
#include "../include/ResourceManager.h"

namespace Johnny
{
    bool SDLFramework::init(FrameworkInitFlags flags)
    {
        Uint32 initFlags = initFlagsToSDLFlags(flags);
        
        if(SDL_Init(initFlags)<0)
        {
            return false;
        }
        
        return true;
    }
    
    bool SDLFramework::quit()
    {
        SDL_Quit();
        return true;
    }
    
    bool SDLFramework::initWindow()
    {
        ERROR_OUT(SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1),"Couldn't enable double buffering: ");

		if (Settings::getb(SettingName::MSAA))
		{
			ERROR_OUT(SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1),"Couldn't enable Multisampling: ");
			ERROR_OUT(SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, Settings::geti(SettingName::MSAA_SAMPLES)),"Couldn't set the multisampling samples: ");
		}
		

		ERROR_OUT(SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE),"Couldn't set the profile mask: ");
		ERROR_OUT(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3),"Couldn't set the context major version: ");
		ERROR_OUT(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3),"Couldn't set the context minor version: ");
	
        
        return true;
    }
    
    bool SDLFramework::initGraphics()
    {
        if (Settings::getb(SettingName::VSYNC))
		{
			if (SDL_GL_SetSwapInterval(-1)<0)
				ERROR_OUT(SDL_GL_SetSwapInterval(1),"Couldn't enable VSNYC: ");
		}
        return true;
    }
    
    bool SDLFramework::createOpenGLContext()
    {
        SDL_GLContext context = SDL_GL_CreateContext((SDL_Window*)MainClass::getInstance()->getWindow()->getHandle());
        if(!context)
            return false;
        return true;
    }
    
    Window* SDLFramework::createWindow(const std::string& title,unsigned int x,unsigned int y,unsigned int w,unsigned int h,WindowFlags flags)
    {
        Window* window = nullptr;
        SDL_Window* sdlWindow = nullptr;
        Uint32 windowFlags = 0;
        
        windowFlags = windowFlagsToSDLFlags(flags);
        
        sdlWindow = SDL_CreateWindow(title.c_str(),x,y,w,h,windowFlags);
        if(!sdlWindow)
            return nullptr;
        
        window = new Window(sdlWindow);
        
        return window;
    }
    
    bool SDLFramework::swapWindow(Window* window)
    {
        SDL_GL_SwapWindow((SDL_Window*)window->getHandle());
        return true;
    }
    
    bool SDLFramework::destroyWindow(Window* window)
    {
        SDL_DestroyWindow((SDL_Window*)window->getHandle());
        return true;
    }
    
    std::string SDLFramework::getError()
    {
        return std::string(SDL_GetError());
    }
    
    bool SDLFramework::pollEvent()
    {
        bool res = SDL_PollEvent(&m_event);
        
        if(res)
        {
            toJohnnyEvent(m_event,&event);
        }
        
        return res;
    }
    
    bool SDLFramework::setWindowTitle(Window* window,const std::string& title)
    {
        SDL_SetWindowTitle((SDL_Window*)window->getHandle(),title.c_str());
        return true;
    }
    bool SDLFramework::setWindowResolution(Window* window,const Vector2i& res)
    {
        SDL_SetWindowSize((SDL_Window*)window->getHandle(),res.x,res.y);
        return true;
    }
    bool SDLFramework::setWindowPosition(Window* window,const Vector2i& pos)
    {
        SDL_SetWindowPosition((SDL_Window*)window->getHandle(),pos.x,pos.y);
        return true;
    }
    bool SDLFramework::setWindowFullscreen(Window* window,bool fullscreen,bool desktop)
    {
        if(SDL_SetWindowFullscreen((SDL_Window*)window->getHandle(),fullscreen ? (desktop ? SDL_WINDOW_FULLSCREEN_DESKTOP : SDL_WINDOW_FULLSCREEN) : 0)<0)
            return false;
        return true;
    }
    bool SDLFramework::setWindowBorderless(Window* window,bool borderless)
    {
        SDL_SetWindowBordered((SDL_Window*)window->getHandle(),borderless ? SDL_TRUE : SDL_FALSE);
        return true;
    }
    bool SDLFramework::setWindowIcon(Window* window,Texture* tex,GLenum target,GLenum format, GLenum type)
    {
        SDL_Surface* sur = tex->toSDLSurface(target,format,type);
        
        SDL_SetWindowIcon((SDL_Window*)window->getHandle(),sur);
        
        SDL_FreeSurface(sur);
        
        return true;
    }
    bool SDLFramework::setWindowIcon(Window* window,TextureData* texdata)
    {
        SDL_Surface* sur = texdata->toSDL_Surface(SDL_PIXELFORMAT_RGBA8888);
        
        SDL_SetWindowIcon((SDL_Window*)window->getHandle(),sur);
        
        SDL_FreeSurface(sur);
        
        return true;
    }
    
    std::string SDLFramework::getWindowTitle(Window* window)
    {
        std::string title;
        
        title = SDL_GetWindowTitle((SDL_Window*)window->getHandle());
        
        return title;
    }
    Vector2i SDLFramework::getWindowResolution(Window* window)
    {
        Vector2i res;
        
        SDL_GetWindowSize((SDL_Window*)window->getHandle(),&res.width,&res.height);
        
        return res;
    }
    Vector2i SDLFramework::getScreenResolution()
    {
        SDL_DisplayMode dm;
        SDL_GetCurrentDisplayMode(0,&dm);
        
        Vector2i res(dm.w,dm.h);
        
        return res;
    }
    bool SDLFramework::isWindowFullscreen(Window* window)
    {
        Uint32 flags = SDL_GetWindowFlags((SDL_Window*)window->getHandle());
        
        if((flags & SDL_WINDOW_FULLSCREEN) || (flags & SDL_WINDOW_FULLSCREEN_DESKTOP))
            return true;
        else
            return false;
    }
    bool SDLFramework::isWindowBorderless(Window* window)
    {
        Uint32 flags = SDL_GetWindowFlags((SDL_Window*)window->getHandle());
        
        if((flags & SDL_WINDOW_BORDERLESS))
            return true;
        else
            return false;
    }
    
    int SDLFramework::getControllerID(void* handle)
    {
        return SDL_JoystickInstanceID(SDL_GameControllerGetJoystick((SDL_GameController*)handle));
    }
    
    bool equal(Uint8 u1[], Uint8 u2[])
    {
        int size = sizeof((Uint8*)u1)/sizeof(*u1);
        for(int i = 0;i<size;i++)
        {
            if(u1[i] != u2[i])
            {
                return false;
            }
        }
        return true;
    }
    
    bool SDLFramework::isSameController(void* handle1,void* handle2)
    {
        return equal(SDL_JoystickGetGUID(SDL_GameControllerGetJoystick((SDL_GameController*)handle1)).data,
                     SDL_JoystickGetGUID(SDL_GameControllerGetJoystick((SDL_GameController*)handle2)).data);
    }
    
    void* SDLFramework::openController(int id)
    {
        return (void*)SDL_GameControllerOpen(id);
    }
    
    void SDLFramework::closeController(void* handle)
    {
        SDL_GameControllerClose((SDL_GameController*)handle);
    }

    bool SDLFramework::isAttachedController(void* handle)
    {
        return SDL_GameControllerGetAttached((SDL_GameController*)handle) == SDL_TRUE ? true : false;
    }
    
    Uint32 SDLFramework::initFlagsToSDLFlags(FrameworkInitFlags flags)
    {
        Uint32 sdlFlags = 0;
        
        if(flags & FlagsInitFramework::Measure_Time)
            sdlFlags |= SDL_INIT_TIMER;
        if(flags & FlagsInitFramework::Audio)
            sdlFlags |= SDL_INIT_AUDIO;
        if(flags & FlagsInitFramework::Video)
            sdlFlags |= SDL_INIT_VIDEO;
        if(flags & FlagsInitFramework::Joystick)
            sdlFlags |= SDL_INIT_JOYSTICK;
        if(flags & FlagsInitFramework::Haptic)
            sdlFlags |= SDL_INIT_HAPTIC;
        if(flags & FlagsInitFramework::GameController)
            sdlFlags |= SDL_INIT_GAMECONTROLLER;
        if(flags & FlagsInitFramework::Events)
            sdlFlags |= SDL_INIT_EVENTS;
        if(flags & FlagsInitFramework::NoParachute)
            sdlFlags |= NoParachute;
            
        return sdlFlags;
    }
    
    Uint32 SDLFramework::windowFlagsToSDLFlags(WindowFlags flags)
    {
        Uint32 sdlFlags = 0;
        
        if(flags & FlagsWindow::Fullscreen)
            sdlFlags |= SDL_WINDOW_FULLSCREEN;
        if(flags & FlagsWindow::Fullscreen_Desktop)
            sdlFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
        if(flags & FlagsWindow::OpenGL)
            sdlFlags |= SDL_WINDOW_OPENGL;
        if(flags & FlagsWindow::Shown)
            sdlFlags |= SDL_WINDOW_SHOWN;
        if(flags & FlagsWindow::Hidden)
            sdlFlags |= SDL_WINDOW_HIDDEN;
        if(flags & FlagsWindow::Borderless)
            sdlFlags |= SDL_WINDOW_BORDERLESS;
        if(flags & FlagsWindow::Resizeable)
            sdlFlags |= SDL_WINDOW_RESIZABLE;
        if(flags & FlagsWindow::Minimized)
            sdlFlags |= SDL_WINDOW_MINIMIZED;
        if(flags & FlagsWindow::Maximized)
            sdlFlags |= SDL_WINDOW_MAXIMIZED;
        if(flags & FlagsWindow::Input_Grapped)
            sdlFlags |= SDL_WINDOW_INPUT_GRABBED;
        if(flags & FlagsWindow::Input_Focus)
            sdlFlags |= SDL_WINDOW_INPUT_FOCUS;
        if(flags & FlagsWindow::Mouse_Focus)
            sdlFlags |= SDL_WINDOW_MOUSE_FOCUS;
        if(flags & FlagsWindow::Foreign)
            sdlFlags |= SDL_WINDOW_FOREIGN;
        if(flags & FlagsWindow::Allow_HighDPI)
            sdlFlags |= SDL_WINDOW_ALLOW_HIGHDPI;
        if(flags & FlagsWindow::Mouse_Capture)
            sdlFlags |= SDL_WINDOW_MOUSE_CAPTURE;
        if(flags & FlagsWindow::Always_On_Top)
            sdlFlags |= SDL_WINDOW_ALWAYS_ON_TOP;
        if(flags & FlagsWindow::Skip_Taskbar)
            sdlFlags |= SDL_WINDOW_SKIP_TASKBAR;
        if(flags & FlagsWindow::Utility)
            sdlFlags |= SDL_WINDOW_UTILITY;
        if(flags & FlagsWindow::Tooltip)
            sdlFlags |= SDL_WINDOW_TOOLTIP;
        if(flags & FlagsWindow::Popup_Menu)
            sdlFlags |= SDL_WINDOW_POPUP_MENU;
            
        return sdlFlags;
    }

	EventType SDLFramework::toJohnnyEventType(unsigned int type)
	{
		switch (type)
		{
			case SDL_QUIT: return EventType::Quit;
			case SDL_WINDOWEVENT: return EventType::WindowEvent;
			case SDL_SYSWMEVENT: return EventType::SysWMEvent;
			case SDL_KEYDOWN: return EventType::KeyDown;
			case SDL_KEYUP: return EventType::KeyUp;
			case SDL_TEXTEDITING: return EventType::TextEditing;
			case SDL_TEXTINPUT: return EventType::TextInput;
			case SDL_KEYMAPCHANGED: return EventType::KeyMapChanged;
			case SDL_MOUSEMOTION: return EventType::MouseMotion;
			case SDL_MOUSEBUTTONDOWN: return EventType::MouseButtonDown;
			case SDL_MOUSEBUTTONUP: return EventType::MouseButtonUp;
			case SDL_MOUSEWHEEL: return EventType::MouseWheel;
			case SDL_JOYAXISMOTION: return EventType::JoyAxisMotion;
			case SDL_JOYBALLMOTION: return EventType::JoyBallMotion;
			case SDL_JOYHATMOTION: return EventType::JoyHatMotion;
			case SDL_JOYBUTTONDOWN: return EventType::JoyButtonDown;
			case SDL_JOYBUTTONUP: return EventType::JoyButtonUp;
			case SDL_JOYDEVICEADDED: return EventType::JoyDeviceAdded;
			case SDL_JOYDEVICEREMOVED: return EventType::JoyDeviceRemoved;
			case SDL_CONTROLLERAXISMOTION: return EventType::ControllerAxisMotion;
			case SDL_CONTROLLERBUTTONDOWN: return EventType::ControllerButtonDown;
			case SDL_CONTROLLERBUTTONUP: return EventType::ControllerButtonUp;
			case SDL_CONTROLLERDEVICEADDED: return EventType::ControllerDeviceAdded;
			case SDL_CONTROLLERDEVICEREMOVED: return EventType::ControllerDeviceRemoved;
			case SDL_CONTROLLERDEVICEREMAPPED: return EventType::ControllerDeviceRemapped;
			case SDL_FINGERDOWN: return EventType::FingerDown;
			case SDL_FINGERUP: return EventType::FingerUp;
			case SDL_FINGERMOTION: return EventType::FingerMotion;
			case SDL_DOLLARGESTURE: return EventType::DollarGesture;
			case SDL_DOLLARRECORD: return EventType::DollarRecord;
			case SDL_MULTIGESTURE: return EventType::MultiGesture;
			case SDL_CLIPBOARDUPDATE: return EventType::ClipboardUpdate;
			case SDL_DROPFILE: return EventType::DropFile;
			case SDL_DROPTEXT: return EventType::DropText;
			case SDL_DROPBEGIN: return EventType::DropBegin;
			case SDL_DROPCOMPLETE: return EventType::DropComplete;
			case SDL_AUDIODEVICEADDED: return EventType::AudioDeviceAdded;
			case SDL_AUDIODEVICEREMOVED: return EventType::AudioDeviceRemoved;
			case SDL_RENDER_TARGETS_RESET: return EventType::RenderTargetsReset;
			case SDL_RENDER_DEVICE_RESET: return EventType::RenderDeviceReset;
			case SDL_USEREVENT: return EventType::UserEvent;
			default: return EventType::Undefined;
		}
	}

	WindowEventType SDLFramework::toJohnnyWindowEventType(Uint8 id)
	{
		switch (id)
		{
			case SDL_WINDOWEVENT_SHOWN: return WindowEventType::Shown;
			case SDL_WINDOWEVENT_HIDDEN: return WindowEventType::Hidden;
			case SDL_WINDOWEVENT_EXPOSED: return WindowEventType::Exposed;
			case SDL_WINDOWEVENT_MOVED: return WindowEventType::Moved;
			case SDL_WINDOWEVENT_RESIZED: return WindowEventType::Resized;
			case SDL_WINDOWEVENT_SIZE_CHANGED: return WindowEventType::SizeChanged;
			case SDL_WINDOWEVENT_MINIMIZED: return WindowEventType::Minimized;
			case SDL_WINDOWEVENT_MAXIMIZED: return WindowEventType::Maximized;
			case SDL_WINDOWEVENT_RESTORED: return WindowEventType::Restored;
			case SDL_WINDOWEVENT_ENTER: return WindowEventType::Enter;
			case SDL_WINDOWEVENT_LEAVE: return WindowEventType::Leave;
			case SDL_WINDOWEVENT_FOCUS_GAINED: return WindowEventType::FocusGained;
			case SDL_WINDOWEVENT_FOCUS_LOST: return WindowEventType::FocusLost;
			case SDL_WINDOWEVENT_CLOSE: return WindowEventType::Close;
			case SDL_WINDOWEVENT_TAKE_FOCUS: return WindowEventType::TakeFocus;
			case SDL_WINDOWEVENT_HIT_TEST: return WindowEventType::HitTest;
			default: return WindowEventType::Undefined;
		}
	}
    
    void SDLFramework::toJohnnyEvent(const SDL_Event& e,Event* event)
    {
        event->type = toJohnnyEventType(e.type);
        
        event->common.type = toJohnnyEventType(e.common.type);
        event->common.timestamp = e.common.timestamp;
        
        event->window.type = toJohnnyEventType(e.window.type);
        event->window.timestamp = e.window.timestamp;
        event->window.windowID = e.window.windowID;
        event->window.event = toJohnnyWindowEventType(e.window.event);
        event->window.data1 = e.window.data1;
        event->window.data2 = e.window.data2;
        
        event->key.type = toJohnnyEventType(e.key.type);
        event->key.timestamp = e.key.timestamp;
        event->key.windowID = e.key.windowID;
        event->key.key = InputManager::convertSDL(e.key.keysym.sym);
        event->key.state = e.key.state;
        event->key.repeat = e.key.repeat;
        
        event->edit.type = toJohnnyEventType(e.edit.type);
        event->edit.timestamp = e.edit.timestamp;
        memcpy(event->edit.text,e.edit.text,TEXTEDITINGEVENT_TEXT_SIZE);
        event->edit.start = e.edit.start;
        event->edit.length = e.edit.length;
        event->edit.windowID = e.edit.windowID;
        
        event->text.type = toJohnnyEventType(e.text.type);
        event->text.timestamp = e.text.timestamp;
        memcpy(event->text.text,e.text.text,TEXTINPUTEVENT_TEXT_SIZE);
        event->text.windowID = e.text.windowID;
        
        event->motion.type = toJohnnyEventType(e.motion.type);
        event->motion.timestamp = e.motion.timestamp;
        event->motion.windowID = e.motion.windowID;
        event->motion.state = e.motion.state;
        event->motion.which = e.motion.which;
        event->motion.x = e.motion.x;
        event->motion.xrel = e.motion.xrel;
        event->motion.y = e.motion.y;
        event->motion.yrel = e.motion.yrel;
        
        event->button.button = InputManager::convertSDL(e.button.button);
        event->button.clicks = e.button.clicks;
        event->button.state = e.button.state;
        event->button.timestamp = e.button.timestamp;
        event->button.type = toJohnnyEventType(e.button.type);
        event->button.which = e.button.which;
        event->button.windowID = e.button.windowID;
        event->button.x = e.button.x;
        event->button.y = e.button.y;
        
        event->wheel.direction = e.wheel.direction;
        event->wheel.timestamp = e.wheel.timestamp;
        event->wheel.type = toJohnnyEventType(e.wheel.type);
        event->wheel.which = e.wheel.which;
        event->wheel.windowID = e.wheel.windowID;
        event->wheel.x = e.wheel.x;
        event->wheel.y = e.wheel.y;
        
        event->jaxis.axis = (Axis)e.jaxis.axis;
        event->jaxis.timestamp = e.jaxis.timestamp;
        event->jaxis.type = toJohnnyEventType(e.jaxis.type);
        event->jaxis.which = e.jaxis.which;
        event->jaxis.value = e.jaxis.value;
        
        event->jball.ball = e.jball.ball;
        event->jball.timestamp = e.jball.timestamp;
        event->jball.type = toJohnnyEventType(e.jball.type);
        event->jball.which = e.jball.which;
        event->jball.xrel = e.jball.xrel;
        event->jball.yrel = e.jball.yrel;
        
        event->jhat.hat = e.jhat.hat;
        event->jhat.timestamp = e.jhat.timestamp;
        event->jhat.type = toJohnnyEventType(e.jhat.type);
        event->jhat.value = e.jhat.value;
        event->jhat.which = e.jhat.which;
        
        event->jbutton.button = (Buttons)e.jbutton.button;
        event->jbutton.state = e.jbutton.state;
        event->jbutton.timestamp = e.jbutton.timestamp;
        event->jbutton.type = toJohnnyEventType(e.jbutton.type);
        event->jbutton.which = e.jbutton.which;
        
        event->jdevice.timestamp = e.jdevice.timestamp;
        event->jdevice.type = toJohnnyEventType(e.jdevice.type);
        event->jdevice.which = e.jdevice.which;
        
        event->caxis.axis = (Axis)e.caxis.axis;
        event->caxis.timestamp = e.caxis.timestamp;
        event->caxis.type = toJohnnyEventType(e.caxis.type);
        event->caxis.value = e.caxis.value;
        event->caxis.which = e.caxis.which;
        
        event->cbutton.button = (Buttons)e.cbutton.button;
        event->cbutton.state = e.cbutton.state;
        event->cbutton.timestamp = e.cbutton.timestamp;
        event->cbutton.type = toJohnnyEventType(e.cbutton.type);
        event->cbutton.which = e.cbutton.which;
        
        event->cdevice.timestamp = e.cdevice.timestamp;
        event->cdevice.type = toJohnnyEventType(e.cdevice.type);
        event->cdevice.which = e.cdevice.which;
        
        event->adevice.iscapture = e.adevice.iscapture;
        event->adevice.timestamp = e.adevice.timestamp;
        event->adevice.type = toJohnnyEventType(e.adevice.type);
        event->adevice.which = e.adevice.which;
        
        event->quit.timestamp = e.quit.timestamp;
        event->quit.type = toJohnnyEventType(e.quit.type);
        
        event->user.code = e.user.code;
        event->user.data1 = e.user.data1;
        event->user.data2 = e.user.data2;
        event->user.timestamp = e.user.timestamp;
        event->user.type = toJohnnyEventType(e.user.type);
        event->user.windowID = e.user.windowID;
        
        event->syswm.msg = (SysWMmsg*)e.syswm.msg;
        event->syswm.timestamp = e.syswm.timestamp;
        event->syswm.type = toJohnnyEventType(e.syswm.type);
        
        event->tfinger.dx = e.tfinger.dx;
        event->tfinger.dy = e.tfinger.dy;
        event->tfinger.fingerID = e.tfinger.fingerId;
        event->tfinger.pressure = e.tfinger.pressure;
        event->tfinger.timestamp = e.tfinger.timestamp;
        event->tfinger.touchID = e.tfinger.touchId;
        event->tfinger.type = toJohnnyEventType(e.tfinger.type);
        event->tfinger.x = e.tfinger.x;
        event->tfinger.y = e.tfinger.y;
        
        event->mgesture.dDist = e.mgesture.dDist;
        event->mgesture.dTheta = e.mgesture.dTheta;
        event->mgesture.numFingers = e.mgesture.numFingers;
        event->mgesture.timestamp = e.mgesture.timestamp;
        event->mgesture.touchID = e.mgesture.touchId;
        event->mgesture.type = toJohnnyEventType(e.mgesture.type);
        event->mgesture.x = e.mgesture.x;
        event->mgesture.y = e.mgesture.y;
        
        event->dgesture.error = e.dgesture.error;
        event->dgesture.gestureID = e.dgesture.gestureId;
        event->dgesture.numFingers = e.dgesture.numFingers;
        event->dgesture.timestamp = e.dgesture.timestamp;
        event->dgesture.touchID = e.dgesture.touchId;
        event->dgesture.type = toJohnnyEventType(e.dgesture.type);
        event->dgesture.x = e.dgesture.x;
        event->dgesture.y = e.dgesture.y;
        
        event->drop.file = e.drop.file;
        event->drop.timestamp = e.drop.timestamp;
        event->drop.type = toJohnnyEventType(e.drop.type);
        event->drop.windowID = e.drop.windowID;
    }
}