#ifndef GLFWFRAMEWORK_H
#define GLFWFRAMEWORK_H
#include "Framework.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Events.h"
#include <queue>

namespace Johnny
{
	class GLFWFramework : public Framework
	{
	public:
		bool init(FrameworkInitFlags flags) override;
		bool quit() override;
		bool initWindow() override;
		bool initGraphics() override;
		bool createOpenGLContext() override;

		Window* createWindow(const std::string& title, unsigned int x, unsigned int y, unsigned int w, unsigned int h, WindowFlags flags) override;
		bool swapWindow(Window* window) override;
		bool destroyWindow(Window* window) override;

		std::string getError() override;

		bool pollEvent() override;

		bool setWindowTitle(Window* window, const std::string& title) override;
		bool setWindowResolution(Window* window, const Vector2i& res) override;
		bool setWindowPosition(Window* window, const Vector2i& pos) override;
		bool setWindowFullscreen(Window* window, bool fullscreen = true, bool desktop = true) override;
		bool setWindowBorderless(Window* window, bool borderless = true) override;
		bool setWindowIcon(Window* window, Texture* tex, GLenum target = GL_TEXTURE_2D, GLenum format = GL_RGBA, GLenum type = GL_UNSIGNED_BYTE) override;
		bool setWindowIcon(Window* window, TextureData* texdata) override;

		std::string getWindowTitle(Window* window) override;
		Vector2i getWindowResolution(Window* window) override;
		Vector2i getScreenResolution() override;
		bool isWindowFullscreen(Window* window) override;
		bool isWindowBorderless(Window* window) override;

		int getControllerID(void* handle) override;
		bool isSameController(void* handle1, void* handle2) override;
		void* openController(int id) override;
		void closeController(void* handle) override;
		bool isAttachedController(void* handle) override;
        
        void lockAndHideCursor() override;
        void hideCursor() override;
        void showCursor() override;
        bool isCursorHidden() override;
	private:
		static void onError(int error, const char* description);
		static void onKey(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void onResize(GLFWwindow* window, int width, int height);
        static void onMouseMove(GLFWwindow* window, double xpos, double ypos);
        static void onMouseButton(GLFWwindow* window, int button, int action, int mods);

		static Keys toJohnnyKeys(int key);

		static std::string errorString;
		static std::queue<Event> events;

		static bool wasEvent;
		static bool polledEvents;
        
        static Vector2d m_prevMousePos;
	};
}

#endif
