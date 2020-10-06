#include "../include/MainClass.h"
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
#include "../include/Physics2D.h"
#include <SDL2/SDL_ttf.h>
#include "../include/Timer.h"
//#define DEBUG_OUTPUTS

namespace Johnny
{
    MainClass* MainClass::instance = nullptr;

    MainClass::MainClass(unsigned int initFlags,const std::string& title,unsigned int width,unsigned int height,WindowFlags windowFlags) : Actor("MainClass"),
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
		m_castsShadows3D = false;
        m_visible = false;
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
			LogManager::error(std::string("An exception accoured!: ") + e.what() + "\n");
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
		m_camera2D->setPosition(getNativeRes()/2.0f);
		Texture::initTexture2DBuffers();
		Texture::initTexture2DShader(this);
		TransformableObject2D::setViewportSize(m_nativeResolution);
		TransformableObject2D::setCenter(Vector2f(-0.5f,-0.5f));
	}

	void MainClass::afterInit()
	{
		if ((m_initFlags & InitFlags::INIT_3D))
		{
			addChild(m_skybox);
			RenderManager::loadDefaultShaders3D(m_resourceManager, m_lighting3D);
            setAllChildrenWithNullShaderToDefaultShader();
		}
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
        
        if(m_renderManager)
            delete m_renderManager;
        if(m_resourceManager)
            delete m_resourceManager;
        if(m_timer)
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
		
		if (m_physics2D)
		{
			delete m_physics2D;
			m_physics2D = nullptr;
		}
        
        if(m_frameBufferTex)
            delete m_frameBufferTex;
        if(m_frameBufferTexMulti)
            delete m_frameBufferTexMulti;
		if(m_renderBuffer)
            delete m_renderBuffer;
		if(m_renderBufferMulti)
            delete m_renderBufferMulti;
		if(m_frameBuffer)
            delete m_frameBuffer;
		if(m_frameBufferMulti)
            delete m_frameBufferMulti;
		if(m_frameBufferMesh)
            delete m_frameBufferMesh;
            
        if(m_window)
            delete m_window;
        
        if(!m_framework->quit())
            LogManager::error(std::string("Error while quitting: ") + m_framework->getError());
    }

    void MainClass::m_init()
    {
        LogManager::log("Initializing Engine");
        
#ifndef __LINUX__
        m_framework = Framework::createFramework(Frameworks::SDL);
#else
#ifdef USE_GLFW
        m_framework = Framework::createFramework(Frameworks::GLFW);
#else
        m_framework = Framework::createFramework(Frameworks::SDL);
#endif
#endif
        if(!m_framework->init(FlagsInitFramework::Everything))
        {
            LogManager::error(std::string("Initializing Framework: ") + m_framework->getError());
        }
		if (TTF_Init() < 0)
		{
			LogManager::error(std::string("Initializing SDL_ttf: ") + TTF_GetError());
		}

		m_framework->initWindow();

        m_window = m_framework->createWindow(m_windowTitle,150,150,m_windowWidth,m_windowHeight,FlagsWindow::Shown | FlagsWindow::OpenGL | m_initWindowFlags);
        
        if(!m_window || !m_window->getHandle())
        {
            LogManager::error(std::string("Creating Window: ") + m_framework->getError());
        }
		if (!m_framework->createOpenGLContext())
		{
			LogManager::error(std::string("Couldn't create OpenGL-Context: ") + m_framework->getError());
		}
		if (!RenderUtil::initGraphics(0.0f, 0.0f, 0.0f))
		{
		}

		Settings::m_initialized = true;
        
        m_nativeResolution = Vector2f((GLfloat)m_windowWidth, (GLfloat)m_windowHeight);

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
		m_frameBufferTex = new Texture(nullptr, (GLsizei)m_nativeResolution.x, (GLsizei)m_nativeResolution.y,Settings::geti(SettingName::BACK_BUFFER_FILTERING), GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, GL_TEXTURE_2D);
		m_frameBufferTexMulti = new Texture(nullptr, (GLsizei)m_nativeResolution.x, (GLsizei)m_nativeResolution.y,Settings::geti(SettingName::BACK_BUFFER_FILTERING), GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, GL_TEXTURE_2D_MULTISAMPLE);
		m_renderBuffer = new RenderBuffer((GLsizei)m_nativeResolution.x, (GLsizei)m_nativeResolution.y, GL_DEPTH24_STENCIL8, GL_RENDERBUFFER, false);
		m_renderBufferMulti = new RenderBuffer((GLsizei)m_nativeResolution.x, (GLsizei)m_nativeResolution.y, GL_DEPTH24_STENCIL8, GL_RENDERBUFFER, true);
		m_frameBuffer->addTexture(m_frameBufferTex, GL_COLOR_ATTACHMENT0, GL_FRAMEBUFFER, GL_TEXTURE_2D);
		m_frameBuffer->addRenderBuffer(m_renderBuffer, GL_DEPTH_STENCIL_ATTACHMENT, GL_FRAMEBUFFER);
		m_frameBufferMulti->addTexture(m_frameBufferTexMulti, GL_COLOR_ATTACHMENT0, GL_FRAMEBUFFER, GL_TEXTURE_2D_MULTISAMPLE);
		m_frameBufferMulti->addRenderBuffer(m_renderBufferMulti, GL_DEPTH_STENCIL_ATTACHMENT, GL_FRAMEBUFFER);
		m_frameBuffer->checkStatus();
		m_frameBufferMulti->checkStatus();
		m_frameBufferMesh = Texture::createTexturePlane(2.0,2.0);

		m_renderManager->loadDefaultShaders(m_resourceManager);
        
        // FPS Manager
		m_timer = new Timer();

		Transform3D::setProjection(Matrix4f::perspective(70.0f, m_nativeResolution.x / m_nativeResolution.y, 1000.0f, 0.1f));

		if ((m_initFlags & InitFlags::INIT_3D) != 0)
			init3D();
		if ((m_initFlags & InitFlags::INIT_2D) != 0)
			init2D();
		if ((m_initFlags & InitFlags::JOYSTICK) != 0)
			activateJoystick();
		if ((m_initFlags & InitFlags::PHYSICS_2D) != 0)
			m_physics2D = new Physics2D(this, Vector2f(0.0f, -10.0f), getNativeRes());

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
                    
					if(m_lighting3D)
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

					m_framework->swapWindow(m_window);

					m_timer->endTimeMeasure();
#ifdef DEBUG_OUTPUTS
                std::cout << "End of mainLoop" << std::endl;
#endif
        }
    }

    bool MainClass::pollEvents()
    {
        m_inputManager->setMouseWheel(0,0);
        while(m_framework->pollEvent())
        {
#ifdef DEBUG_OUTPUTS
        	std::cout << "Polling an event" << std::endl;
#endif
            switch(m_framework->event.type)
            {
			case EventType::Quit:
                    return false;
                case EventType::KeyDown:
                    m_inputManager->pressKey(m_framework->event.key.key);
                    break;
                case EventType::KeyUp:
                    m_inputManager->releaseKey(m_framework->event.key.key);
                    break;
                case EventType::MouseButtonDown:
                    m_inputManager->pressKey(m_framework->event.button.button);
                    break;
                case EventType::MouseButtonUp:
                    m_inputManager->releaseKey(m_framework->event.button.button);
                    break;
                case EventType::MouseMotion:
                    m_inputManager->setMouseCoords(m_framework->event.motion.x,m_framework->event.motion.y);
					m_inputManager->setMouseRel(m_framework->event.motion.xrel, m_framework->event.motion.yrel);
                    break;
                case EventType::MouseWheel:
                    m_inputManager->setMouseWheel(m_framework->event.wheel.x,m_framework->event.wheel.y);
                    break;
				case EventType::WindowEvent:
					switch (m_framework->event.window.event)
					{
					case WindowEventType::SizeChanged:
						onResize(m_framework->event.window.data1, m_framework->event.window.data2);
                        break;
                    default:
                        break;
					}
                default:
                    break;
            }

#ifdef DEBUG_OUTPUTS
            std::cout << "Polling Joystickevents" << std::endl;
#endif
            if(m_joystickManager)
                m_joystickManager->pollEvents(m_framework->event);
#ifdef DEBUG_OUTPUTS
            std::cout << "Polled Joystickevents" << std::endl;
#endif

            if(!pollEvent(m_framework->event))
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


    bool MainClass::pollEvent(const Event& e)
    {
        return true;
    }

    bool MainClass::render()
    {
        return true;
    }

    bool MainClass::m_update()
    {
		if (m_physics2D)
			m_physics2D->update();
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
    
    const Colorb& MainClass::getAmbientLight3D() const
    {
        return m_lighting3D->ambientLight;
    }
    
    void MainClass::onResize(unsigned int w,unsigned int h)
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
        Vector2i newRes = m_window->getResolution();
        
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

			if (newRes.y > (int)m_windowHeight)
				m_viewportOffsetY = (GLint)(((float)newRes.y - (float)m_windowHeight) / 2.0f);
			else
			{
				m_windowWidth = (int)((double)newRes.y * normScale);
				m_windowHeight = newRes.y;
				m_viewportOffsetX = (GLint)(((float)newRes.x - (float)m_windowWidth) / 2.0f);
			}
		}
    }
    
    void MainClass::setAmbientLight3D(const Colorb& col)
    {
		Lighting3D::ambientLight = col;
    }
    
    void MainClass::setNativeRes(const Vector2f& v)
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
		m_frameBufferTex = new Texture(nullptr, (GLsizei)m_nativeResolution.x, (GLsizei)m_nativeResolution.y, Settings::geti(SettingName::BACK_BUFFER_FILTERING), GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, GL_TEXTURE_2D);
		m_frameBufferTexMulti = new Texture(nullptr, (GLsizei)m_nativeResolution.x, (GLsizei)m_nativeResolution.y, Settings::geti(SettingName::BACK_BUFFER_FILTERING), GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, GL_TEXTURE_2D_MULTISAMPLE);
		m_renderBuffer = new RenderBuffer((GLsizei)m_nativeResolution.x, (GLsizei)m_nativeResolution.y, GL_DEPTH24_STENCIL8, GL_RENDERBUFFER, false);
		m_renderBufferMulti = new RenderBuffer((GLsizei)m_nativeResolution.x, (GLsizei)m_nativeResolution.y, GL_DEPTH24_STENCIL8, GL_RENDERBUFFER, true);

		m_frameBuffer->addTexture(m_frameBufferTex, GL_COLOR_ATTACHMENT0, GL_FRAMEBUFFER, GL_TEXTURE_2D);
		m_frameBuffer->addRenderBuffer(m_renderBuffer, GL_DEPTH_STENCIL_ATTACHMENT, GL_FRAMEBUFFER);
		m_frameBufferMulti->addTexture(m_frameBufferTexMulti, GL_COLOR_ATTACHMENT0, GL_FRAMEBUFFER, GL_TEXTURE_2D_MULTISAMPLE);
		m_frameBufferMulti->addRenderBuffer(m_renderBufferMulti, GL_DEPTH_STENCIL_ATTACHMENT, GL_FRAMEBUFFER);

		m_frameBuffer->checkStatus();
		m_frameBufferMulti->checkStatus();

		Transform3D::setProjection(Matrix4f::perspective(70.0f, getNativeRes().x / getNativeRes().y, 1000.0f, 0.1f));

		TransformableObject2D::setViewportSize(m_nativeResolution);
		TransformableObject2D::setCenter(Vector2f(-0.5f,-0.5f));

		onResize(m_window->getResolution().x,m_window->getResolution().y);
    }

    void MainClass::setBackgroundColor(const Colorb& col)
    {
    	m_backgroundColor = col;
        Colorf color = m_backgroundColor;
        
        glClearColor(color.r,color.g,color.b,color.a);
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
