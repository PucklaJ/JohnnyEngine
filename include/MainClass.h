#ifndef MAINCLASS_H
#define MAINCLASS_H
#include "InputManager.h"
#include <SDL2/SDL_events.h>
#include "Actor.h"
#include "Window.h"
#include <chrono>
#include "SDL2_framerate.h"
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_mixer.h>
#include <GL/glew.h>
#include "Timer.h"
#include "Vector2.h"
#include "Colors.h"

#define NO_FPS_LOCK -1

using namespace std::chrono;

namespace Johnny
{   
	class Lighting3D;
	class RenderManager;
	class Mesh3D;
	class FrameBuffer;
	class RenderBuffer;
	class Texture;
	class Skybox;
	class Timer;

	class Camera3D;
	class Camera2D;

    class ResourceManager;
    
    class JoystickManager;
	
	class Physics2D;

	/*! \brief A enum with all flags to determine what should be initialised
	 *
	 */
	enum InitFlags
	{
		INIT_3D = 1 >> 0,   //!< Initialises everything for 3D rendering
		INIT_2D = 1 << 1,   //!< Initialises everything for 2D rendering
		JOYSTICK = 1 << 2,  //!< Initialises the JoystickManager to capture controller inputs
		PHYSICS_3D = 1 << 3,//!< Initialises the Physics3D (will be ignored)
		PHYSICS_2D = 1 << 4,//!< Initialises the Physics2D
		AUDIO = 1 << 5,     //!< Initialises audio output (will be ignored)
		EVERYTHING = ~0     //!< Initialises everything
	};

	/*! \brief The main or root class where the application starts
	 *
	 *
	 * This class handles all base things such as the initialisation.
	 */
    class MainClass : public Actor
    {
        public:
        	/*! \brief Creates a new MainClass
        	 *  \param initFlags Ore'd together InitFlags to determine what will be initialised
        	 *  \param title The title of the Window which will be created
        	 *  \param width The width of the Window in pixels
        	 *  \param height The height of the Window in pixels
        	 *  \param windowFlags The flags which will be used for the Window initialisation (this value will be ore'd together with SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL)
        	 */
            MainClass(Uint32 initFlags = 0,const char* title = "New Window",int width = NORM_W,int height = NORM_H,Uint32 windowFlags = 0);
            virtual ~MainClass();

            /*! \brief Starts the engine.
             *         Should be called in the main function
             *
             */
            void run();
 
            /*! \brief Sets the ambient light for all 3D lighting equations
             *  \param color The color of the ambient light
             */
            void setAmbientLight3D(const Colorb& color);
            /*! \brief Sets the resolution of the application (NOT the window resolutions)
             *  \param v The resolution to set
             */
            void setNativeRes(const Vector2f& v);
            /*! \brief Sets the background color which will be used to clear the screen
             *  \param color The background color to set
             */
            void setBackgroundColor(const Colorb& color);

            /*! \brief Renders every Actor with the given Shader DEPRECATED
             *  \param s The Shader with which everything should be rendered
             */
			void renderSceneForShadowMap(Shader* s);

			/*! \return The instance of the MainClass
			 *
			 */
            static MainClass* getInstance() {return instance;}

            /*! \return The InputManager of the object
             *
             */
            InputManager* getInputManager() {return m_inputManager;}
            /*! \return The ResourceManager of the object
             *
             */
            ResourceManager* getResourceManager() {return m_resourceManager;}
            /*! \return The Window of the object
             *
             */
            Window* getWindow() {return m_window;}
            /*! \return The JoystickManager of the object
             *
             */
            JoystickManager* getJoystickManager() {return m_joystickManager;}
            /*! \return The Lighting3D of the object
             *
             */
			Lighting3D* getLighting3D() { return m_lighting3D; }
			/*! \return The RenderManager of the object
             *
             */
			RenderManager* getRenderManager() { return m_renderManager; }
			/*! \return The back buffer of the object which is the texture to which everything will be drawn and which will then be drawn to the screen
             *
             */
			FrameBuffer* getBackBuffer() { return m_frameBufferMulti; }
			/*! \return The back buffer mesh of the object which is the mesh which will be drawn to the screen with the back buffer on it
             *
             */
			Mesh3D* getBackBufferMesh() { return m_frameBufferMesh; }
			/*! \return The Skybox of the object
             *
             */
			Skybox* getSkybox() { return m_skybox; }
			/*! \return The Timer of the object which measures the frame time
             *
             */
			Timer* getTimer() { return m_timer; }
			/*! \return The Physics2D of the object which handles all 2D physics related things
             *
             */
			Physics2D* getPhysics2D() { return m_physics2D; }

			/*! \return The Camera3D of the object
			 *
			 */
            Camera3D* getCamera3D();
            /*! \return The Camera2D of the object
             *
             */
			Camera2D* getCamera2D();
			/*! \return Native_Resolution.x / Window_Resolution.x
			 *
			 */
            float getScaleW() const {return m_scaleW;}
            /*! \return Native_Resolution.y / Window_Resolution.y
			 *
			 */
            float getScaleH() const {return m_scaleH;}
            /*! \return The resolution of the back buffer
             *
             */
            const Vector2f& getNativeRes() const {return m_nativeResolution;}
            /*! \return The background color of the object which will be used to clear the screen
             *
             */
            const Colorb& getBackgroundColor() const {return m_backgroundColor;}
            
            /*! \brief The render function
             *
			 *
			 * It is overriding the method from Actor
             */
            virtual bool render() override;
            /*! \brief The update function
             *
			 *
			 * It is overriding the method from Actor
             */
            virtual bool update() override;
            /*! \brief The m_update function
             *
			 *
			 * It is overriding the method from Actor
             */
            virtual bool m_update() override;

            /*! \brief Gets called when the Window resizes
             *  \param width The new width of the Window
             *  \param height The new height of the Window
             */
            virtual void onResize(int width,int height);
            /*! \brief Gets called when the Window switches to fullscreen or switches to windowed mode
             *  \param full true if the window switches to fullscreen otherwise false
             */
            virtual void onFullscreen(bool full);

        protected:
        	/*! \brief The quit method
        	 *
        	 *
        	 * It is overriding the method from Actor
        	 */
            virtual void quit() = 0 override;
            /*! \brief The init method
             * 
             *
             * It is overriding the method from Actor
             */
            virtual bool init() = 0 override;
            /*! \brief Gets called every frame to poll the events
             *
             */
            virtual bool pollEvents();
            /*! \brief Gets called always when an event occoured
             *  \param e The event that happened
             */
            virtual bool pollEvent(const SDL_Event& e);

            InputManager* m_inputManager = nullptr;       //!< The InputManager of the object
            ResourceManager* m_resourceManager = nullptr; //!< The ResourceManager of the object
            Window* m_window = nullptr;					  //!< The Window of the object
            Camera3D* m_camera3D = nullptr;				  //!< The Camera3D of the object
			Camera2D* m_camera2D = nullptr;				  //!< The Camera2D of the object
            JoystickManager* m_joystickManager = nullptr; //!< The JoystickManager of the object
			Lighting3D* m_lighting3D = nullptr;	          //!< The Lighting3D of the object
			RenderManager* m_renderManager = nullptr;	  //!< The RenderManager of the object
			Skybox* m_skybox = nullptr;					  //!< The Skybox of the object
			Timer* m_timer = nullptr;					  //!< The Timer of the object
			Physics2D* m_physics2D = nullptr;			  //!< The Physics2D of the object

        private:
            static MainClass* instance;					  //!< The instance of the MainClass

            /*! \brief Gets called when m_initFlags contains InitFlags::INIT_3D and initialises all 3D rendering related things
             *
             */
			void init3D();
			/*! \brief Gets called when m_initFlags contains InitFlags::INIT_2D and initialises all 2D rendering related things
			 *
			 */
			void init2D();
			/*! \brief Gets called when m_initFlags contains InitFlags::JOYSTICK and initialises the JoystickManager
			 *
			 */
			void activateJoystick();
            
            /*! \brief Gets called after the engine has initialised
             *
             */
			void afterInit();
			/*! \brief Handles quitting for internal porpuses
			 *
			 */
            void m_quit();

            /*! \brief Contains the main loop of the engine
             *
             */
            void mainLoop();

            /*! \brief Handles initialising for internal porpuses
             *
             */
            void m_init();

			Mesh3D* m_frameBufferMesh = nullptr;	     //!< The Mesh which will be drawn on the screen with the back buffer on it
			FrameBuffer* m_frameBufferMulti = nullptr;   //!< The FrameBuffer which is used to draw to the back buffer
			FrameBuffer* m_frameBuffer = nullptr;		 //!< The FrameBuffer which will be used to draw to the screen
			RenderBuffer* m_renderBufferMulti = nullptr; //!< The RenderBuffer which will be attached to m_frameBufferMulti for depth rendering
			RenderBuffer* m_renderBuffer = nullptr;      //!< The RenderBuffer which will be attached to m_frameBuffer for depth rendering
			Texture* m_frameBufferTexMulti = nullptr;    //!< The Texture which will be attached to m_frameBufferMulti for color rendering
			Texture* m_frameBufferTex = nullptr;		 //!< The Texture which will be attached to m_frameBuffer for color rendering

            const char* m_windowTitle;					 //!< The title of the Window which was passed through the constructor
            int m_windowWidth;							 //!< The width of the Window which was passed through the constructor in pixels
            int m_windowHeight;							 //!< The height of the Window which was passed through the constructor in pixels

            float m_scaleW;								 //!< Native_Resolution.x / Window_Resolution.x
            float m_scaleH;								 //!< Native_Resolution.y / Window_Resolution.y

			GLint m_viewportOffsetX = 0;				 //!< The x offset of the back buffer on the screen
			GLint m_viewportOffsetY = 0;			     //!< The y offset of the back buffer on the screen
            
            Colorb m_backgroundColor;					 //!< The bakground color which will be used to clear the screen
        
            Vector2f m_nativeResolution;				 //!< The resolution of the back buffer
			Uint32 m_initWindowFlags = 0;				 //!< The windowFlags which were passed through the constructor
			Uint32 m_initFlags = 0;						 //!< The initFlags which were passed through the constructor
    };
}



#endif // MAINCLASS_H
