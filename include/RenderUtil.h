#pragma once
#include <SDL2\SDL.h>
#include <string>

#define ERROR_OUT(func) if(func<0)SDL::LogManager::error(SDL_GetError())

class RenderUtil
{
public:
	RenderUtil();
	~RenderUtil();

	static void clearScreen();
	static bool initGraphics(float r = 0.0f,float g = 0.0f,float b = 0.0f,float a = 0.0f);
	static void initWindow();
	static void swapWindow(SDL_Window*);
	static std::string getOpenGLVersion();
};

