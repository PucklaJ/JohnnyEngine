#include <MainClass.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "InputManager.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "LogManager.h"
#include "JoystickManager.h"
#include "operators.h"
#include "Colors.h"
#include "RenderUtil.h"
#include "Light.h"
#include "ShadowMap.h"
#include "Shader.h"
#include "RenderManager.h"
#include "Texture.h"
#include "FrameBuffer.h"
#include "RenderBuffer.h"
#include "Mesh.h"
#include "Skybox.h"
#ifdef _WIN32
#include <TTF/SDL_ttf.h>
#else
#include <SDL2/SDL_ttf.h>
#endif
//#define DEBUG_OUTPUTS

namespace SDL
{
    MainClass* MainClass::instance = nullptr;

    MainClass::MainClass(const char* title,int width,int height,Uint32 windowFlags) : Actor("MainClass"),
                                                                   m_windowTitle(title),
                                                                   m_windowWidth(width),
                                                                   m_windowHeight(height),
																   m_scaleW(1.0f),
																   m_scaleH(1.0f),
																   m_initWindowFlags(windowFlags)

    {
        if(instance == nullptr)
        {
            instance = this;
        }

        m_FPSes[0] = m_FPSes[1] = m_FPSes[2] = 0.0;
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
            std::cerr << "An error accoured!" << std::endl << e.what() << std::endl;
        }

    }

    void MainClass::quit()
    {

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

        if(m_inputManager)
            removeChild(m_inputManager);
        if(m_resourceManager)
            m_resourceManager->clear();
        
		RenderManager::unload();
		Skybox::clear();

        if(m_resourceManager)
            delete m_resourceManager;
        if(m_lighting)
            delete m_lighting;

        if(m_frameBufferTex)
        {
            delete m_frameBufferTex;
            delete m_frameBufferTexMulti;
            delete m_renderBuffer;
            delete m_renderBufferMulti;
            delete m_frameBuffer;
            delete m_frameBufferMulti;
            delete m_frameBufferMesh;
        }
		

        if(m_window)
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
            exit(-1);
        }
		if (TTF_Init() < 0)
		{
			LogManager::error(std::string("Initializing SDL_ttf: ") + TTF_GetError());
			exit(-1);
		}
		RenderUtil::initWindow();

        m_window = new WindowHandle(this,m_windowTitle,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,m_windowWidth,m_windowHeight,SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | m_initWindowFlags);
        if(!m_window->getWindow())
        {
            LogManager::error(std::string("Creating Window: ") + std::string(SDL_GetError()));
            exit(-1);
        }
		SDL_GLContext glContext = SDL_GL_CreateContext(m_window->getWindow());
		if (!glContext)
		{
			LogManager::error("Couldn't create SDL_GL_Context");
			exit(-1);
		}
		if (!RenderUtil::initGraphics(0.0f, 0.0f, 0.0f))
		{
			exit(-1);
		}
        
        m_nativeResolution = glm::vec2(m_windowWidth, m_windowHeight);

        m_scaleW = m_windowWidth/m_nativeResolution.x;
        m_scaleH = m_windowHeight/m_nativeResolution.y;

        m_camera = new Camera();
        addChild(m_camera);

        m_inputManager = new InputManager;
        m_inputManager->setMainClass(this);
        m_inputManager->setParent(this);
        m_inputManager->init();

		m_resourceManager = new ResourceManager();
		m_lighting = new Lighting();
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
        SDL_initFramerate(&m_fpsManager);
        SDL_setFramerate(&m_fpsManager,m_maxFPS);

		Transform::setProjection(70.0f, m_nativeResolution.x, m_nativeResolution.y, 0.1f, 1000.0f);

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
                #ifdef MAX_FPS_LOCK
                if(m_timeForMaxFPS == 0.0)
                {
                #endif
                startTimeMeasure();
                #ifdef MAX_FPS_LOCK
                }
                m_timeForMaxFPS += m_deltaClockTimeForMaxFPS.count() / 1000000.0;
                
                m_startTimeForMaxFPS = high_resolution_clock::now();
                if(m_timeForMaxFPS >= 1.0/1000.0)
                {
                #endif
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

					m_lighting->renderShadowMaps(this, RenderManager::DEFAULT_SHADOWMAP_SHADER);
					render();
					m_renderManager->render(this);

					
					m_frameBufferMulti->blit(m_frameBuffer, 0, 0, (GLint)m_nativeResolution.x, (GLint)m_nativeResolution.y, 0, 0, (GLint)m_nativeResolution.x, (GLint)m_nativeResolution.y);
					m_frameBufferMulti->unbind();

					RenderUtil::clearScreen();
					glDisable(GL_DEPTH_TEST);
					glViewport(m_viewportOffsetX,m_viewportOffsetY,m_windowWidth,m_windowHeight);
					RenderManager::DEFAULT_POST_PROCESSING_SHADER->bind();
					m_frameBufferTex->bind(RenderManager::DEFAULT_POST_PROCESSING_SHADER, "frameBuffer");
					//m_lighting->getSpotLights()[0]->shadowMap->bind(RenderManager::DEFAULT_POST_PROCESSING_SHADER, "frameBuffer");

					m_frameBufferMesh->render();

					m_frameBufferTex->unbind();
					glViewport(0, 0, (GLsizei)m_nativeResolution.x, (GLsizei)m_nativeResolution.y);

					RenderUtil::swapWindow(m_window->getWindow());
                #ifdef MAX_FPS_LOCK
                    m_timeForMaxFPS = 0.0;
                }
                
                m_endTimeForMaxFPS = high_resolution_clock::now();
                
                m_deltaClockTimeForMaxFPS = m_endTimeForMaxFPS-m_startTimeForMaxFPS;
                
                if(m_timeForMaxFPS == 0.0)
                {
                    #endif
                    m_fps = endTimeMeasure();
                    #ifdef MAX_FPS_LOCK
                }
                #endif
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
                    m_inputManager->pressKey(e.key.keysym.sym);
                    break;
                case SDL_KEYUP:
                    m_inputManager->releaseKey(e.key.keysym.sym);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    m_inputManager->pressKey(e.button.button);
                    break;
                case SDL_MOUSEBUTTONUP:
                    m_inputManager->releaseKey(e.button.button);
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

    void MainClass::startTimeMeasure()
    {
        m_startTime = high_resolution_clock::now();
    }

    int MainClass::endTimeMeasure()
    {
        if(m_maxFPS != NO_FPS_LOCK)
            SDL_framerateDelay(&m_fpsManager);
        
        m_endTime = high_resolution_clock::now();
        m_deltaClockTime = m_endTime - m_startTime;
        m_realDeltaTimeInSeconds = m_deltaClockTime.count()/1000000.0;
        
        m_realDeltaTimeSize = getDeltaTimesSize();
        if(m_realDeltaTimeSize == 11)
            moveDeltaTimesOneIndexDown();

        // Set the last frameTime
        m_realDeltaTimes[m_realDeltaTimeSize == 11 ? 10 : m_realDeltaTimeSize] = m_realDeltaTimeInSeconds;

        // Copy Real Frame Times into the smooth ones
        copyRealTimesToSmoothTimes();

        // Calculate the mean Time
        m_smoothDeltaTimeInSeconds = calculateMeanDeltaTime();

        m_FPSes[m_lastFrame] = 1.0/m_smoothDeltaTimeInSeconds;

        m_lastFrame++;
        if(m_lastFrame == 3)
        {
            m_lastFrame = 0;
        }


        return (int)((m_FPSes[0]+m_FPSes[1]+m_FPSes[2])/3.0);
    }

    void MainClass::copyRealTimesToSmoothTimes()
    {
        for(int i = 0;i<11;i++)
        {
            m_smoothDeltaTimes[i] = m_realDeltaTimes[i];
        }
    }


    int MainClass::getDeltaTimesSize()
    {
        for(int i = 0;i<11;i++)
        {
            if(m_realDeltaTimes[i] == -1.0)
                return i;
        }

        return 11;
    }


    void MainClass::moveDeltaTimesOneIndexDown()
    {
        for(int i = 0;i<11;i++)
        {
            if(i > 0)
            m_realDeltaTimes[i-1] = m_realDeltaTimes[i];
        }

        m_realDeltaTimes[10] = -1.0;
    }


    double MainClass::calculateMeanDeltaTime()
    {
        double mean = 0.0;
        int size = 11;

        for(int i = 0;i<11;i++)
        {
            if(m_smoothDeltaTimes[i] == -1.0)
            {
                size = i;
                break;
            }
        }

        if(size > 4)
        {
            takeAwayHighestAndLowestDts();
        }

        for(int i = 0;i<11;i++)
        {
            if(m_smoothDeltaTimes[i] != -1.0)
            {
                mean += m_smoothDeltaTimes[i];
            }
        }

        return mean/(size > 4 ? 7.0 : (double)size);
    }

    void MainClass::takeAwayHighestAndLowestDts()
    {
        int numIndex = 0;
        double num=0;

        // Take away two Lowest
        for(int j = 0;j<2;j++)
        {
            setNum(num,numIndex);
            for(int i = 0;i<11;i++)
            {
                if(m_smoothDeltaTimes[i] != -1.0)
                {
                    if(m_smoothDeltaTimes[i] < num)
                    {
                        num = m_smoothDeltaTimes[i];
                        numIndex = i;
                    }
                }
            }

            m_smoothDeltaTimes[numIndex] = -1.0;

        }


        numIndex = 0;


        //Take away two highest
        for(int j = 0;j<2;j++)
        {
            setNum(num,numIndex);
            for(int i = 0;i<11;i++)
            {
                if(m_smoothDeltaTimes[i] != -1.0)
                {
                    if(m_smoothDeltaTimes[i] > num)
                    {
                        num = m_smoothDeltaTimes[i];
                        numIndex = i;
                    }
                }
            }

            m_smoothDeltaTimes[numIndex] = -1.0;
        }

    }

    void MainClass::setNum(double& num,int& numIndex)
    {
        for(int i = 0;i<11;i++)
        {
            if(m_smoothDeltaTimes[i] != -1.0)
            {
                num = m_smoothDeltaTimes[i];
                numIndex = i;
            }
        }
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

    Camera* MainClass::getCamera()
    {
        return m_camera;
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
    
    
    void MainClass::setMaxFPS(int fps)
    {
        if(fps == NO_FPS_LOCK)
        {
            m_maxFPS = fps;
            return;
        }
        
        if(fps > FPS_UPPER_LIMIT)
        {
            fps = FPS_UPPER_LIMIT;
        }
        else if(fps < FPS_LOWER_LIMIT)
        {
            fps = FPS_LOWER_LIMIT;
        }
        
        m_maxFPS = fps;
        
        if(SDL_setFramerate(&m_fpsManager,m_maxFPS)<0)
        {
            LogManager::error("Setting max FPS");
        }
    }
    
    void MainClass::setAmbientLight(const SDL_Color& col)
    {
		Lighting::ambientLight = glm::vec4((float)col.r / 255.0f,(float)col.g / 255.0f, (float)col.b / 255.0f, (float)col.a / 255.0f);
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

		Transform::setProjection(Transform::getFOV(), getNativeRes().x, getNativeRes().y, Transform::getNearPlane(), Transform::getFarPlane());

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
