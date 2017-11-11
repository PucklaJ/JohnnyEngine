#include "../include/RenderUtil.h"
#include <GL/glew.h>
#include <iostream>
#include "../include/LogManager.h"
#include "../include/Settings.h"
#include "../include/MainClass.h"

namespace Johnny
{
	RenderUtil::RenderUtil()
	{
	}


	RenderUtil::~RenderUtil()
	{
	}

	void RenderUtil::clearScreen()
	{
		glClearDepth(1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	bool RenderUtil::initGraphics(float r, float g, float b, float a)
	{
		if (glewInit() != GLEW_OK)
		{
			LogManager::error("Couldn't inititialize GLEW");
			return false;
		}

		LogManager::log("OpenGL-Version: " + RenderUtil::getOpenGLVersion());

		glClearColor(r, g, b, a);

		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		if (Settings::getb(SettingName::MSAA))
			glEnable(GL_MULTISAMPLE);
		else
			glDisable(GL_MULTISAMPLE);

		//glEnable(GL_FRAMEBUFFER_SRGB);
        
		return MainClass::getInstance()->getFramework()->initGraphics();
	}

	void RenderUtil::initWindow()
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
	}

	void RenderUtil::swapWindow(SDL_Window* w)
	{
		SDL_GL_SwapWindow(w);
	}

	std::string RenderUtil::getOpenGLVersion()
	{
		return std::string((const char*)glGetString(GL_VERSION));
	}

}
