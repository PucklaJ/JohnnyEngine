#include "../include/MainClass.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "../include/InputManager.h"
#include "../include/ResourceManager.h"
#include "../include/Camera3D.h"
#include "../include/LogManager.h"
#include "../include/JoystickManager.h"
#include "../include/operators.h"
#include "../include/Colors.h"
#include "../include/RenderUtil.h"
#include "../include/Light3D.h"
#include "../include/ShadowMap3D.h"
#include "../include/Shader.h"
#include "../include/RenderManager.h"
#include "../include/Texture.h"
#include "../include/FrameBuffer.h"
#include "../include/RenderBuffer.h"
#include "../include/Mesh3D.h"
#include "../include/Skybox.h"
#include "../include/Settings.h"
#include "../include/Camera2D.h"
#ifdef _WIN32
#include <TTF/SDL_ttf.h>
#endif
#ifdef __linux__
#include <SDL2/SDL_ttf.h>
#endif
#ifdef __APPLE__
#include <SDL2_ttf/SDL_ttf.h>
#endif
#include "../include/Timer.h"
//#define DEBUG_OUTPUTS

namespace Johnny
{
    MainClass* MainClass::instance = nullptr;

    MainClass::MainClass(Uint32 initFlags,const char* title,int width,int height,Uint32 windowFlags) : Actor("MainClass"),
                                                                   m_windowTitle(title),
                                                                   m_windowWidth(width),
                                                                   m_windowHeight(height),
																   m_scaleW(1.0f),
																   m_scaleH(1.0f),
																   m_initWindowFlags(windowFlags),
																   m_initFlags(initFlags)

    {
        if(instance == nullptr)
        {
            instance = this;
        }

        m_isAffectedByCamera = false;
        m_mainClass = this;
		m_castsShadows = false;
    }

    MainClass::~MainClass()
    {

    }

    void MainClass::run()
    {
        try
        {
            m_init();
			if (init())
			{
				afterInit();
				mainLoop();
			}
                

            m_all_quit();
        }
        catch(std::exception& e)
        {
			LogManager::error(std::string("An error accoured!\n") + e.what() + "\n");
        }

    }

    void MainClass::quit()
    {

    }

	void MainClass::init3D()
	{
		m_camera3D = new Camera3D();
		addChild(m_camera3D);
		m_lighting3D = new Lighting3D();
	}

	void MainClass::init2D()
	{
		m_camera2D = new Camera2D();
	}

	void MainClass::afterInit()
	{
		addChild(m_skybox);
	}

	void MainClass::m_quit()
    {
        Actor::m_quit();
        
        if(m_joystickManager)
        {
            delete m_joystickManager;
            m_joystickManager = nullptr;
        }

        removeChild(m_inputManager);
        m_resourceManager->clear();
        
		RenderManager::unload();
		Skybox::clear();

		delete m_renderManager;
        delete m_resourceManager;
		delete m_timer;
		if (m_lighting3D)
		{
			delete m_lighting3D;
			m_lighting3D = nullptr;
		}

		if (m_camera2D)
		{
			delete m_camera2D;
			m_camera2D = nullptr;
		}

		delete m_frameBufferTex;
		delete m_frameBufferTexMulti;
		delete m_renderBuffer;
		delete m_renderBufferMulti;
		delete m_frameBuffer;
		delete m_frameBufferMulti;
		delete m_frameBufferMesh;

        delete m_window;

        SDL_Quit();

        delete Colors::m_COLOR_KEY;
    }

    void MainClass::m_init()
    {
        LogManager::log("Initializing Engine");
        
        if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
        {
            LogManager::error(std::string("Initializing SDL: ") + SDL_GetError());
        }
		if (TTF_Init() < 0)
		{
			LogManager::error(std::string("Initializing SDL_ttf: ") + TTF_GetError());
		}
		RenderUtil::initWindow();

        m_window = new Window(this,m_windowTitle,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,m_windowWidth,m_windowHeight,SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | m_initWindowFlags);
        if(!m_window->getWindow())
        {
            LogManager::error(std::string("Creating Window: ") + std::string(SDL_GetError()));
        }
		SDL_GLContext glContext = SDL_GL_CreateContext(m_window->getWindow());
		if (!glContext)
		{
			LogManager::error("Couldn't create SDL_GL_Context");
		}
		if (!RenderUtil::initGraphics(0.0f, 0.0f, 0.0f))
		{
		}

		Settings::m_initialized = true;
        
        m_nativeResolution = glm::vec2(m_windowWidth, m_windowHeight);

        m_scaleW = m_windowWidth/m_nativeResolution.x;
        m_scaleH = m_windowHeight/m_nativeResolution.y;

        m_inputManager = new InputManager;
        m_inputManager->setMainClass(this);
        m_inputManager->setParent(this);
        m_inputManager->init();

		m_resourceManager = new ResourceManager();
		m_renderManager = new RenderManager();
		m_skybox = new Skybox();

		m_frameBuffer = new FrameBuffer();
		m_frameBufferMulti = new FrameBuffer();
		m_frameBufferTex = new Texture(nullptr, (GLsizei)m_nativeResolution.x, (GLsizei)m_nativeResolution.y, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, GL_TEXTURE_2D);
		m_frameBufferTexMulti = new Texture(nullptr, (GLsizei)m_nativeResolution.x, (GLsizei)m_nativeResolution.y, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, GL_TEXTURE_2D_MULTISAMPLE);
		m_renderBuffer = new RenderBuffer((GLsizei)m_nativeResolution.x, (GLsizei)m_nativeResolution.y, GL_DEPTH24_STENCIL8, GL_RENDERBUFFER, false);
		m_renderBufferMulti = new RenderBuffer((GLsizei)m_nativeResolution.x, (GLsizei)m_nativeResolution.y, GL_DEPTH24_STENCIL8, GL_RENDERBUFFER, true);
		m_frameBuffer->addTexture(m_frameBufferTex, GL_COLOR_ATTACHMENT0, GL_FRAMEBUFFER, GL_TEXTURE_2D);
		m_frameBuffer->addRenderBuffer(m_renderBuffer, GL_DEPTH_STENCIL_ATTACHMENT, GL_FRAMEBUFFER);
		m_frameBufferMulti->addTexture(m_frameBufferTexMulti, GL_COLOR_ATTACHMENT0, GL_FRAMEBUFFER, GL_TEXTURE_2D_MULTISAMPLE);
		m_frameBufferMulti->addRenderBuffer(m_renderBufferMulti, GL_DEPTH_STENCIL_ATTACHMENT, GL_FRAMEBUFFER);
		m_frameBuffer->checkStatus();
		m_frameBufferMulti->checkStatus();
		m_frameBufferMesh = Texture::createTexturePlane(2.0,2.0);
        
        // FPS Manager
		m_timer = new Timer();

		Transform3D::setProjection(70.0f, m_nativeResolution.x, m_nativeResolution.y, 0.1f, 1000.0f);

		if ((m_initFlags & InitFlags::INIT_3D) != 0)
			init3D();
		if ((m_initFlags & InitFlags::INIT_2D) != 0)
			init2D();
		if ((m_initFlags & InitFlags::JOYSTICK) != 0)
			activateJoystick();

        LogManager::log("Finished Initializing Engine");
    }


    bool MainClass::init()
    {
        return true;
    }

    void MainClass::mainLoop()
    {
        
        while(true)
        {
#ifdef DEBUG_OUTPUTS
        	std::cout << "Start of mainLoop" << std::endl;
#endif
					m_timer->startTimeMeasure();
#ifdef DEBUG_OUTPUTS
                	std::cout << "PollEvents" << std::endl;
#endif
                    if(!pollEvents())
                    {
                        break;
                    }
#ifdef DEBUG_OUTPUTS
                    std::cout << "End of Pollevents" << std::endl;
#endif
                    if(!m_all_update())
                    {
                        break;
                    }
                    m_inputManager->m_all_update();
#ifdef DEBUG_OUTPUTS
                    std::cout << "Updating joystickManager" << std::endl;
#endif
                    if(m_joystickManager)
                        m_joystickManager->update();
#ifdef DEBUG_OUTPUTS
                    std::cout << "Updated JoystickManager" << std::endl;
#endif
					glEnable(GL_DEPTH_TEST);
					m_frameBufferMulti->bind();
					RenderUtil::clearScreen();

					m_lighting3D->renderShadowMaps(this, RenderManager::DEFAULT_SHADOWMAP_SHADER);
					render();
					m_renderManager->render(this);
					
					m_frameBufferMulti->blit(m_frameBuffer, 0, 0, (GLint)m_nativeResolution.x, (GLint)m_nativeResolution.y, 0, 0, (GLint)m_nativeResolution.x, (GLint)m_nativeResolution.y);
					m_frameBufferMulti->unbind();

					RenderUtil::clearScreen();
					glDisable(GL_DEPTH_TEST);
					glViewport(m_viewportOffsetX,m_viewportOffsetY,m_windowWidth,m_windowHeight);
					RenderManager::DEFAULT_POST_PROCESSING_SHADER->bind();
					m_frameBufferTex->bind(RenderManager::DEFAULT_POST_PROCESSING_SHADER, "frameBuffer");

					m_frameBufferMesh->render();

					m_frameBufferTex->unbind();
					glViewport(0, 0, (GLsizei)m_nativeResolution.x, (GLsizei)m_nativeResolution.y);

					RenderUtil::swapWindow(m_window->getWindow());

					m_timer->endTimeMeasure();
#ifdef DEBUG_OUTPUTS
                std::cout << "End of mainLoop" << std::endl;
#endif
        }
    }

    bool MainClass::pollEvents()
    {
        SDL_Event e;
        m_inputManager->setMouseWheel(0,0);
        while(SDL_PollEvent(&e))
        {
#ifdef DEBUG_OUTPUTS
        	std::cout << "Polling an event" << std::endl;
#endif
            switch(e.type)
            {
                case SDL_QUIT:
                    return false;
                case SDL_KEYDOWN:
                    m_inputManager->pressKey(InputManager::convertSDL(e.key.keysym.sym));
                    break;
                case SDL_KEYUP:
                    m_inputManager->releaseKey(InputManager::convertSDL(e.key.keysym.sym));
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    m_inputManager->pressKey(InputManager::convertSDL(e.button.button));
                    break;
                case SDL_MOUSEBUTTONUP:
                    m_inputManager->releaseKey(InputManager::convertSDL(e.button.button));
                    break;
                case SDL_MOUSEMOTION:
                    m_inputManager->setMouseCoords(e.motion.x,e.motion.y);
					m_inputManager->setMouseRel(e.motion.xrel, e.motion.yrel);
                    break;
                case SDL_MOUSEWHEEL:
                    m_inputManager->setMouseWheel(e.wheel.x,e.wheel.y);
                    break;
				case SDL_WINDOWEVENT:
					switch (e.window.event)
					{
					case SDL_WINDOWEVENT_SIZE_CHANGED:
						onResize(e.window.data1, e.window.data2);
					}
            }

#ifdef DEBUG_OUTPUTS
            std::cout << "Polling Joystickevents" << std::endl;
#endif
            if(m_joystickManager)
                m_joystickManager->pollEvents(e);
#ifdef DEBUG_OUTPUTS
            std::cout << "Polled Joystickevents" << std::endl;
#endif

            if(!pollEvent(e))
            {
                return false;
            }
        }

        return true;
    }

    void MainClass::activateJoystick()
    {
        m_joystickManager = new JoystickManager();
    }


    bool MainClass::pollEvent(const SDL_Event& e)
    {
        return true;
    }

    bool MainClass::render()
    {
        return true;
    }

    bool MainClass::m_update()
    {
        return Actor::m_update();
    }


    bool MainClass::update()
	{
        return true;
    }

    Camera3D* MainClass::getCamera3D()
    {
        return m_camera3D;
    }

	Camera2D * MainClass::getCamera2D()
	{
		return m_camera2D;
	}
    
    void MainClass::onResize(int w,int h)
    {
        double normScale = m_nativeResolution.x/m_nativeResolution.y;
		double newScale = (double)w / (double)h;

		m_viewportOffsetX = m_viewportOffsetY = 0;

		if (((normScale / newScale) > 0.999 && (normScale / newScale) < 1.001))
		{
			m_windowWidth = w;
			m_windowHeight = h;
		}
		else
		{
			m_windowWidth = w;
			m_windowHeight = (int)((double)w / normScale);
			
			if (h > m_windowHeight)
				m_viewportOffsetY = (GLint)(((float)h - (float)m_windowHeight) / 2.0f);
			else
			{
				m_windowWidth = (int)((double)h * normScale);
				m_windowHeight = h;
				m_viewportOffsetX = (GLint)(((float)w - (float)m_windowWidth) / 2.0f);
			}
		}

		
    }
    
    void MainClass::onFullscreen(bool full)
    {
        SDL_Point newRes = m_window->getResolution();
        
        double normScale = m_nativeResolution.x/m_nativeResolution.y;
		double newScale = (double)newRes.x / (double)newRes.y;

		m_viewportOffsetX = m_viewportOffsetY = 0;

		if (((normScale / newScale) > 0.999 && (normScale / newScale) < 1.001))
		{
			m_windowWidth = newRes.x;
			m_windowHeight = newRes.y;
		}
		else
		{
			m_windowWidth = newRes.x;
			m_windowHeight = (int)((double)newRes.x / normScale);

			if (newRes.y > m_windowHeight)
				m_viewportOffsetY = (GLint)(((float)newRes.y - (float)m_windowHeight) / 2.0f);
			else
			{
				m_windowWidth = (int)((double)newRes.y * normScale);
				m_windowHeight = newRes.y;
				m_viewportOffsetX = (GLint)(((float)newRes.x - (float)m_windowWidth) / 2.0f);
			}
		}
    }
    
    void MainClass::setAmbientLight3D(const SDL_Color& col)
    {
		Lighting3D::ambientLight = glm::vec4((float)col.r / 255.0f,(float)col.g / 255.0f, (float)col.b / 255.0f, (float)col.a / 255.0f);
    }
    
    void MainClass::setNativeRes(const glm::vec2& v)
    {
        m_nativeResolution = v;

		delete m_frameBuffer;
		delete m_frameBufferMulti;
		delete m_frameBufferTex;
		delete m_frameBufferTexMulti;
		delete m_renderBuffer;
		delete m_renderBufferMulti;

		m_frameBuffer = new FrameBuffer();
		m_frameBufferMulti = new FrameBuffer();
		m_frameBufferTex = new Texture(nullptr, (GLsizei)m_nativeResolution.x, (GLsizei)m_nativeResolution.y, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, GL_TEXTURE_2D);
		m_frameBufferTexMulti = new Texture(nullptr, (GLsizei)m_nativeResolution.x, (GLsizei)m_nativeResolution.y, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, GL_TEXTURE_2D_MULTISAMPLE);
		m_renderBuffer = new RenderBuffer((GLsizei)m_nativeResolution.x, (GLsizei)m_nativeResolution.y, GL_DEPTH24_STENCIL8, GL_RENDERBUFFER, false);
		m_renderBufferMulti = new RenderBuffer((GLsizei)m_nativeResolution.x, (GLsizei)m_nativeResolution.y, GL_DEPTH24_STENCIL8, GL_RENDERBUFFER, true);

		m_frameBuffer->addTexture(m_frameBufferTex, GL_COLOR_ATTACHMENT0, GL_FRAMEBUFFER, GL_TEXTURE_2D);
		m_frameBuffer->addRenderBuffer(m_renderBuffer, GL_DEPTH_STENCIL_ATTACHMENT, GL_FRAMEBUFFER);
		m_frameBufferMulti->addTexture(m_frameBufferTexMulti, GL_COLOR_ATTACHMENT0, GL_FRAMEBUFFER, GL_TEXTURE_2D_MULTISAMPLE);
		m_frameBufferMulti->addRenderBuffer(m_renderBufferMulti, GL_DEPTH_STENCIL_ATTACHMENT, GL_FRAMEBUFFER);

		m_frameBuffer->checkStatus();
		m_frameBufferMulti->checkStatus();

		Transform3D::setProjection(Transform3D::getFOV(), getNativeRes().x, getNativeRes().y, Transform3D::getNearPlane(), Transform3D::getFarPlane());

		onResize(m_window->getResolution().x,m_window->getResolution().y);
    }

    void MainClass::setBackgroundColor(const SDL_Color& col)
    {
    	m_backgroundColor = col;
    }

	void MainClass::renderSceneForShadowMap(Shader* s)
	{
		std::vector<Actor*> actors = Actor::getAllActors();
		Shader* prevShader = nullptr;
	
		for (size_t i = 0; i < actors.size(); i++)
		{
			if (actors[i]->getMainClass() && actors[i]->castsShadows() && actors[i]->isVisible())
			{
				prevShader = actors[i]->getShader();
				actors[i]->setShader(s, false);
				actors[i]->render();
				actors[i]->setShader(prevShader, false);
			}
		}
	}
}
