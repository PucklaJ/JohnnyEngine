#include "../include/GLFWFramework.h"
#include "../include/Settings.h"
#include "../include/MainClass.h"
#include "../include/Texture.h"
#include "../include/ResourceManager.h"
#include "../include/LogManager.h"
#include "../include/Events.h"

namespace Johnny
{
	std::string GLFWFramework::errorString = "";
	bool GLFWFramework::wasEvent = false;
	bool GLFWFramework::polledEvents = false;
	std::queue<Event> GLFWFramework::events;
    Vector2d GLFWFramework::m_prevMousePos;

	bool GLFWFramework::init(FrameworkInitFlags flags)
	{
		glfwSetErrorCallback(onError);

		if (!glfwInit())
			return false;
            
        return true;
	}
	bool GLFWFramework::quit()
	{
		glfwTerminate();
		return true;
	}
	bool GLFWFramework::initWindow()
	{
		glfwWindowHint(GLFW_DOUBLEBUFFER, 1);

		if (Settings::getb(SettingName::MSAA))
		{
			glfwWindowHint(GLFW_SAMPLES, Settings::geti(SettingName::MSAA_SAMPLES));
		}

		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

		return true;
	}
	bool GLFWFramework::initGraphics()
	{
		if (Settings::getb(SettingName::VSYNC))
		{
			glfwSwapInterval(-1);
		}

		return true;
	}
	bool GLFWFramework::createOpenGLContext()
	{
		glfwMakeContextCurrent((GLFWwindow*)MainClass::getInstance()->getWindow()->getHandle());
		return true;
	}

	Window* GLFWFramework::createWindow(const std::string& title, unsigned int x, unsigned int y, unsigned int w, unsigned int h, WindowFlags flags)
	{
		Window* window = nullptr;
		GLFWwindow* handle = nullptr;

		glfwWindowHint(GLFW_RESIZABLE, flags & FlagsWindow::Resizeable ? GLFW_TRUE : GLFW_FALSE);
		glfwWindowHint(GLFW_VISIBLE, flags & FlagsWindow::Shown ? GLFW_TRUE : GLFW_FALSE);
		glfwWindowHint(GLFW_DECORATED, flags & FlagsWindow::Borderless ? GLFW_FALSE : GLFW_TRUE);
		glfwWindowHint(GLFW_FOCUSED, flags & FlagsWindow::Input_Focus ? GLFW_TRUE : GLFW_FALSE);

		handle = glfwCreateWindow(w, h, title.c_str(),(flags & FlagsWindow::Fullscreen) ? glfwGetPrimaryMonitor() : nullptr, nullptr);
		if (handle == nullptr)
			return nullptr;

		window = new Window(handle);

		window->setPosition(x, y);

		glfwSetKeyCallback(handle, onKey);
		glfwSetWindowSizeCallback(handle, onResize);
        glfwSetCursorPosCallback(handle,onMouseMove);
        glfwSetMouseButtonCallback(handle,onMouseButton);
		
		return window;
	}
	bool GLFWFramework::swapWindow(Window * window)
	{
		glfwSwapBuffers((GLFWwindow*)window->getHandle());
		return true;
	}
	bool GLFWFramework::destroyWindow(Window * window)
	{
		glfwDestroyWindow((GLFWwindow*)window->getHandle());
		return false;
	}
	std::string GLFWFramework::getError()
	{
		return errorString;
	}
	bool GLFWFramework::pollEvent()
	{
		wasEvent = false;
		if (!polledEvents)
		{
			glfwPollEvents();
			if (glfwWindowShouldClose((GLFWwindow*)MainClass::getInstance()->getWindow()->getHandle()))
			{
				Event event;
				event.type = EventType::Quit;
				events.push(event);
			}

			polledEvents = true;
		}
		
		if (!events.empty())
		{
			event = events.front();
			events.pop();
			wasEvent = true;
		}
		else
		{
			polledEvents = false;
		}
        
        glfwGetCursorPos((GLFWwindow*)MainClass::getInstance()->getWindow()->getHandle(),&m_prevMousePos.x,&m_prevMousePos.y);
        
		return wasEvent;
	}
	bool GLFWFramework::setWindowTitle(Window * window, const std::string & title)
	{
		glfwSetWindowTitle((GLFWwindow*)window->getHandle(), title.c_str());
		return true;
	}
	bool GLFWFramework::setWindowResolution(Window * window, const Vector2i & res)
	{
		glfwSetWindowSize((GLFWwindow*)window->getHandle(), res.width, res.height);
		return true;
	}
	bool GLFWFramework::setWindowPosition(Window * window, const Vector2i & pos)
	{
		glfwSetWindowPos((GLFWwindow*)window->getHandle(), pos.x, pos.y);
		return true;
	}
	bool GLFWFramework::setWindowFullscreen(Window * window, bool fullscreen, bool desktop)
	{
		Vector2i monitorRes;
		Vector2i pos;
		Vector2i res = window->getResolution();
		glfwGetWindowPos((GLFWwindow*)window->getHandle(), &pos.x, &pos.y);
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		glfwSetWindowMonitor((GLFWwindow*)window->getHandle(), fullscreen ? glfwGetPrimaryMonitor() : nullptr,fullscreen ? 0 : 150,fullscreen ? 0 : 150,fullscreen ? mode->width : res.width,fullscreen ? mode->height : res.height, mode->refreshRate);
		return true;
	}
	bool GLFWFramework::setWindowBorderless(Window * window, bool borderless)
	{
		return false;
	}
	bool GLFWFramework::setWindowIcon(Window * window, Texture * tex, GLenum target, GLenum format, GLenum type)
	{
		GLubyte* pixels = tex->readPixels(target, format, type);

		GLFWimage img;
		img.width = tex->getWidth();
		img.height = tex->getHeight();
		img.pixels = pixels;

		glfwSetWindowIcon((GLFWwindow*)window->getHandle(), 1, &img);

		delete pixels;

		return true;
	}
	bool GLFWFramework::setWindowIcon(Window * window, TextureData * texdata)
	{
		GLFWimage img;
		img.width = texdata->width;
		img.height = texdata->height;
		img.pixels = texdata->data;

		glfwSetWindowIcon((GLFWwindow*)window->getHandle(), 1, &img);

		return true;
	}
	std::string GLFWFramework::getWindowTitle(Window * window)
	{
		return "GLFW can't get the title";
	}
	Vector2i GLFWFramework::getWindowResolution(Window * window)
	{
		Vector2i res;
		glfwGetWindowSize((GLFWwindow*)window->getHandle(), &res.width, &res.height);

		return res;
	}
	Vector2i GLFWFramework::getScreenResolution()
	{
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		
		return Vector2i(mode->width,mode->height);
	}
	bool GLFWFramework::isWindowFullscreen(Window * window)
	{
		return glfwGetWindowMonitor((GLFWwindow*)window->getHandle());
	}
	bool GLFWFramework::isWindowBorderless(Window * window)
	{
		return glfwGetWindowAttrib((GLFWwindow*)window->getHandle(),GLFW_DECORATED) == GLFW_FALSE;
	}
	int GLFWFramework::getControllerID(void * handle)
	{
		return 0;
	}
	bool GLFWFramework::isSameController(void * handle1, void * handle2)
	{
		return false;
	}
	void * GLFWFramework::openController(int id)
	{
		return nullptr;
	}
	void GLFWFramework::closeController(void * handle)
	{
	}
	bool GLFWFramework::isAttachedController(void * handle)
	{
		return false;
	}
    
    void GLFWFramework::lockAndHideCursor()
    {
        glfwSetInputMode((GLFWwindow*)MainClass::getInstance()->getWindow()->getHandle(),GLFW_CURSOR,GLFW_CURSOR_DISABLED);
    }
    
    void GLFWFramework::hideCursor()
    {
        glfwSetInputMode((GLFWwindow*)MainClass::getInstance()->getWindow()->getHandle(),GLFW_CURSOR,GLFW_CURSOR_HIDDEN);
    }
    
    void GLFWFramework::showCursor()
    {
        glfwSetInputMode((GLFWwindow*)MainClass::getInstance()->getWindow()->getHandle(),GLFW_CURSOR,GLFW_CURSOR_NORMAL);
    }
    
    bool GLFWFramework::isCursorHidden()
    {
        return glfwGetInputMode((GLFWwindow*)MainClass::getInstance()->getWindow()->getHandle(),GLFW_CURSOR) != GLFW_CURSOR_NORMAL;
    }

	void GLFWFramework::onError(int error, const char* description)
	{
		errorString = description;
		//LogManager::error(std::string("An error accoured: ") + to_string(error) + std::string(": ") + std::string(description));
	}

	void GLFWFramework::onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Event e;
		e.type = action == GLFW_PRESS ? EventType::KeyDown : (action == GLFW_RELEASE ? EventType::KeyUp : EventType::Undefined);
		e.key.type = action == GLFW_PRESS ? EventType::KeyDown : (action == GLFW_RELEASE ? EventType::KeyUp : EventType::Undefined);
		e.key.state = action == GLFW_PRESS ? 1 : (action == GLFW_RELEASE ? 0 : 2);
		e.key.windowID = 0;
		e.key.repeat = action == GLFW_REPEAT ? 1 : 0;
		e.key.key = toJohnnyKeys(key);
        
		events.push(e);
		wasEvent = true;
	}

	void GLFWFramework::onResize(GLFWwindow * window, int width, int height)
	{
		MainClass::getInstance()->onResize(width, height);
	}
    
    void GLFWFramework::onMouseMove(GLFWwindow* window, double xpos, double ypos)
    {
        Event e;
        e.type = EventType::MouseMotion;
        e.motion.x = (int)xpos;
        e.motion.y = (int)ypos;
        e.motion.xrel = (int)(xpos - m_prevMousePos.x);
        e.motion.yrel = (int)(ypos - m_prevMousePos.y);
        
        events.push(e);
        wasEvent = true;
    }
    
    void GLFWFramework::onMouseButton(GLFWwindow* window, int button, int action, int mods)
    {
        Event e;
        e.type = action == GLFW_PRESS ? EventType::MouseButtonDown : (action == GLFW_RELEASE ? EventType::MouseButtonUp : EventType::Undefined);
        e.button.button = button == GLFW_MOUSE_BUTTON_LEFT ? Keys::MS_LEFT : (button == GLFW_MOUSE_BUTTON_RIGHT ? Keys::MS_RIGHT : Keys::MS_MIDDLE);
        
        events.push(e);
        wasEvent = true;
    }

	Keys GLFWFramework::toJohnnyKeys(int key)
	{
		switch (key)
		{
		case GLFW_KEY_SPACE: return Keys::SPACE;
		case GLFW_KEY_APOSTROPHE: return Keys::ASTERISK;
		case GLFW_KEY_COMMA: return Keys::COMMA;
		case GLFW_KEY_MINUS: return Keys::MINUS;
		case GLFW_KEY_PERIOD: return Keys::PERIOD;
		case GLFW_KEY_SLASH: return Keys::SLASH;
		case GLFW_KEY_0: return Keys::_0;
		case GLFW_KEY_1: return Keys::_1;
		case GLFW_KEY_2: return Keys::_2;
		case GLFW_KEY_3: return Keys::_3;
		case GLFW_KEY_4: return Keys::_4;
		case GLFW_KEY_5: return Keys::_5;
		case GLFW_KEY_6: return Keys::_6;
		case GLFW_KEY_7: return Keys::_7;
		case GLFW_KEY_8: return Keys::_8;
		case GLFW_KEY_9: return Keys::_9;
		case GLFW_KEY_SEMICOLON: return Keys::SEMICOLON;
		case GLFW_KEY_EQUAL: return Keys::EQUALS;
		case GLFW_KEY_A: return Keys::A;
		case GLFW_KEY_B: return Keys::B;
		case GLFW_KEY_C: return Keys::C;
		case GLFW_KEY_D: return Keys::D;
		case GLFW_KEY_E: return Keys::E;
		case GLFW_KEY_F: return Keys::F;
		case GLFW_KEY_G: return Keys::G;
		case GLFW_KEY_H: return Keys::H;
		case GLFW_KEY_I: return Keys::I;
		case GLFW_KEY_J: return Keys::J;
		case GLFW_KEY_K: return Keys::K;
		case GLFW_KEY_L: return Keys::L;
		case GLFW_KEY_M: return Keys::M;
		case GLFW_KEY_N: return Keys::N;
		case GLFW_KEY_O: return Keys::O;
		case GLFW_KEY_P: return Keys::P;
		case GLFW_KEY_Q: return Keys::Q;
		case GLFW_KEY_R: return Keys::R;
		case GLFW_KEY_S: return Keys::S;
		case GLFW_KEY_T: return Keys::T;
		case GLFW_KEY_U: return Keys::U;
		case GLFW_KEY_V: return Keys::V;
		case GLFW_KEY_W: return Keys::W;
		case GLFW_KEY_X: return Keys::X;
		case GLFW_KEY_Y: return Keys::Y;
		case GLFW_KEY_Z: return Keys::Z;
		case GLFW_KEY_LEFT_BRACKET: return Keys::LEFTBRACKET;
		case GLFW_KEY_BACKSLASH: return Keys::BACKSLASH;
		case GLFW_KEY_RIGHT_BRACKET: return Keys::RIGHTBRACKET;
		case GLFW_KEY_GRAVE_ACCENT: return Keys::BACKQUOTE;
		case GLFW_KEY_WORLD_1: return Keys::UNDEFINED;
		case GLFW_KEY_WORLD_2: return Keys::UNDEFINED;
		case GLFW_KEY_ESCAPE: return Keys::ESCAPE;
		case GLFW_KEY_ENTER: return Keys::RETURN;
		case GLFW_KEY_TAB: return Keys::TAB;
		case GLFW_KEY_BACKSPACE: return Keys::BACKSPACE;
		case GLFW_KEY_INSERT: return Keys::INSERT;
		case GLFW_KEY_DELETE: return Keys::_DELETE;
		case GLFW_KEY_RIGHT: return Keys::RIGHT;
		case GLFW_KEY_LEFT: return Keys::LEFT;
		case GLFW_KEY_DOWN: return Keys::DOWN;
		case GLFW_KEY_UP: return Keys::UP;
		case GLFW_KEY_PAGE_UP: return Keys::PAGEUP;
		case GLFW_KEY_PAGE_DOWN: return Keys::PAGEDOWN;
		case GLFW_KEY_HOME: return Keys::HOME;
		case GLFW_KEY_END: return Keys::END;
		case GLFW_KEY_CAPS_LOCK: return Keys::CAPSLOCK;
		case GLFW_KEY_SCROLL_LOCK: return Keys::SCROLLLOCK;
		case GLFW_KEY_NUM_LOCK: return Keys::NUMLOCKCLEAR;
		case GLFW_KEY_PRINT_SCREEN: return Keys::PRINTSCREEN;
		case GLFW_KEY_PAUSE: return Keys::PAUSE;
		case GLFW_KEY_F1: return Keys::F1;
		case GLFW_KEY_F2: return Keys::F2;
		case GLFW_KEY_F3: return Keys::F3;
		case GLFW_KEY_F4: return Keys::F4;
		case GLFW_KEY_F5: return Keys::F5;
		case GLFW_KEY_F6: return Keys::F6;
		case GLFW_KEY_F7: return Keys::F7;
		case GLFW_KEY_F8: return Keys::F8;
		case GLFW_KEY_F9: return Keys::F9;
		case GLFW_KEY_F10: return Keys::F10;
		case GLFW_KEY_F11: return Keys::F11;
		case GLFW_KEY_F12: return Keys::F12;
		case GLFW_KEY_F13: return Keys::F13;
		case GLFW_KEY_F14: return Keys::F14;
		case GLFW_KEY_F15: return Keys::F15;
		case GLFW_KEY_F16: return Keys::F16;
		case GLFW_KEY_F17: return Keys::F17;
		case GLFW_KEY_F18: return Keys::F18;
		case GLFW_KEY_F19: return Keys::F19;
		case GLFW_KEY_F20: return Keys::F20;
		case GLFW_KEY_F21: return Keys::F21;
		case GLFW_KEY_F22: return Keys::F22;
		case GLFW_KEY_F23: return Keys::F23;
		case GLFW_KEY_F24: return Keys::F24;
		case GLFW_KEY_F25: return Keys::UNDEFINED;
		case GLFW_KEY_KP_0: return Keys::KP_0;
		case GLFW_KEY_KP_1: return Keys::KP_1;
		case GLFW_KEY_KP_2: return Keys::KP_2;
		case GLFW_KEY_KP_3: return Keys::KP_3;
		case GLFW_KEY_KP_4: return Keys::KP_4;
		case GLFW_KEY_KP_5: return Keys::KP_5;
		case GLFW_KEY_KP_6: return Keys::KP_6;
		case GLFW_KEY_KP_7: return Keys::KP_7;
		case GLFW_KEY_KP_8: return Keys::KP_8;
		case GLFW_KEY_KP_9: return Keys::KP_9;
		case GLFW_KEY_KP_DECIMAL: return Keys::KP_DECIMAL;
		case GLFW_KEY_KP_DIVIDE: return Keys::KP_DIVIDE;
		case GLFW_KEY_KP_MULTIPLY: return Keys::KP_MULTIPLY;
		case GLFW_KEY_KP_SUBTRACT: return Keys::KP_MEMSUBTRACT;
		case GLFW_KEY_KP_ADD: return Keys::KP_MEMADD;
		case GLFW_KEY_KP_ENTER: return Keys::KP_ENTER;
		case GLFW_KEY_KP_EQUAL: return Keys::KP_EQUALS;
		case GLFW_KEY_LEFT_SHIFT: return Keys::LSHIFT;
		case GLFW_KEY_LEFT_CONTROL: return Keys::LCTRL;
		case GLFW_KEY_LEFT_ALT: return Keys::LALT;
		case GLFW_KEY_LEFT_SUPER: return Keys::UNDEFINED;
		case GLFW_KEY_RIGHT_SHIFT: return Keys::RSHIFT;
		case GLFW_KEY_RIGHT_CONTROL: return Keys::RCTRL;
		case GLFW_KEY_RIGHT_ALT: return Keys::RALT;
		case GLFW_KEY_RIGHT_SUPER: return Keys::UNDEFINED;
		case GLFW_KEY_MENU: return Keys::MENU;
		default: return Keys::UNDEFINED;
		}
	}
}