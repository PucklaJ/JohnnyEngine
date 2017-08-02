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

	enum InitFlags
	{
		INIT_3D = 1 >> 0,
		INIT_2D = 1 << 1,
		JOYSTICK = 1 << 2,
		PHYSICS_3D = 1 << 3,
		PHYSICS_2D = 1 << 4,
		AUDIO = 1 << 5,
		EVERYTHING = ~0
	};

    class MainClass : public Actor
    {
        public:
            MainClass(Uint32 initFlags = 0,const char* title = "New Window",int width = NORM_W,int height = NORM_H,Uint32 windowFlags = 0);
            virtual ~MainClass();

            void run();

            void setAmbientLight3D(const SDL_Color&);
            void setNativeRes(const Vector2f& v);
            void setBackgroundColor(const SDL_Color&);

			void renderSceneForShadowMap(Shader*);

            static MainClass* getInstance() {return instance;}

            InputManager* getInputManager() {return m_inputManager;}
            ResourceManager* getResourceManager() {return m_resourceManager;}
            Window* getWindow() {return m_window;}
            JoystickManager* getJoystickManager() {return m_joystickManager;}
			Lighting3D* getLighting3D() { return m_lighting3D; }
			RenderManager* getRenderManager() { return m_renderManager; }
			FrameBuffer* getBackBuffer() { return m_frameBufferMulti; }
			Mesh3D* getBackBufferMesh() { return m_frameBufferMesh; }
			Skybox* getSkybox() { return m_skybox; }
			Timer* getTimer() { return m_timer; }

            Camera3D* getCamera3D();
			Camera2D* getCamera2D();
            float getScaleW() const {return m_scaleW;}
            float getScaleH() const {return m_scaleH;}
            const Vector2f& getNativeRes() const {return m_nativeResolution;}
            const SDL_Color& getBackgroundColor() const {return m_backgroundColor;}
            
            virtual bool render() override;
            virtual bool update() override;
            virtual bool m_update() override;

            virtual void onResize(int,int);
            virtual void onFullscreen(bool);

        protected:
            virtual void quit() = 0;
            virtual bool init() = 0;
            virtual bool pollEvents();
            virtual bool pollEvent(const SDL_Event& e);

            InputManager* m_inputManager = nullptr;
            ResourceManager* m_resourceManager = nullptr;
            Window* m_window = nullptr;
            Camera3D* m_camera3D = nullptr;
			Camera2D* m_camera2D = nullptr;
            JoystickManager* m_joystickManager = nullptr;
			Lighting3D* m_lighting3D = nullptr;
			RenderManager* m_renderManager = nullptr;
			Skybox* m_skybox = nullptr;
			Timer* m_timer = nullptr;

        private:
            static MainClass* instance;

			void init3D();
			void init2D();
			void activateJoystick();

			void afterInit();
            void m_quit();

            void mainLoop();

            void m_init();

			Mesh3D* m_frameBufferMesh = nullptr;
			FrameBuffer* m_frameBufferMulti = nullptr;
			FrameBuffer* m_frameBuffer = nullptr;
			RenderBuffer* m_renderBufferMulti = nullptr;
			RenderBuffer* m_renderBuffer = nullptr;
			Texture* m_frameBufferTexMulti = nullptr;
			Texture* m_frameBufferTex = nullptr;

            const char* m_windowTitle;
            int m_windowWidth;
            int m_windowHeight;

            float m_scaleW;
            float m_scaleH;

			GLint m_viewportOffsetX = 0;
			GLint m_viewportOffsetY = 0;
            
            SDL_Color m_backgroundColor;
        
            Vector2f m_nativeResolution;
			Uint32 m_initWindowFlags = 0;
			Uint32 m_initFlags = 0;
    };
}



#endif // MAINCLASS_H
