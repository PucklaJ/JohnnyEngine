#pragma once
#include <SDL2/SDL.h>
#include <string>

#define ERROR_OUT(func,errorText) if(func<0)Johnny::LogManager::error(std::string(errorText) + std::string(SDL_GetError()))

namespace Johnny
{
	/*! \brief A class which handles some basic OpenGL stuff DEPRECATED
	 *
	 */
	class RenderUtil
	{
	public:
		RenderUtil();
		~RenderUtil();

		/*! \brief Clears the screen with the clear color
		 *
		 */
		static void clearScreen();
		/*! \brief Initialises OpenGL
		 *  \param r The r value of the clear color
		 *  \param g The g value of the clear color
		 *  \param b The b value of the clear color
		 *  \param a The a value of the clear color
		 */
		static bool initGraphics(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 0.0f);
		/*! \brief initialises the OpenGL variables for the window
		 *
		 */
		static void initWindow();
		/*! \brief Swaps the buffers of a window
		 *  \param w The window which should be swapped
		 */
		static void swapWindow(SDL_Window* w);
		/*! \return The OpenGL version string
		 *
		 */
		static std::string getOpenGLVersion();
	};
}

