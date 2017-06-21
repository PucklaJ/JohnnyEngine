#ifndef MAINCLASS_H
#define MAINCLASS_H
#include "InputManager.h"
#include <SDL2/SDL_events.h>
#include "Actor.h"
#include "WindowHandle.h"
#include <chrono>
#include "SDL2_framerate.h"
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_mixer.h>
#include <glm/glm.hpp>
#include <GL/glew.h>

#define NO_FPS_LOCK -1

using namespace std::chrono;

class Lighting;
class ShadowMap;
class RenderManager;
class Mesh;
class FrameBuffer;
class RenderBuffer;
class Texture;
class Skybox;

class Camera;

namespace SDL
{            
    class ResourceManager;
    
    class JoystickManager;

    class MainClass : public Actor
    {
        public:
            MainClass(const char* title = "New Window",int width = NORM_W,int height = NORM_H,Uint32 windowFlags = 0);
            virtual ~MainClass();

            void run();

            void setTimeScale(double d){m_timeScale = d;}
            void setMaxFPS(int);
            void setAmbientLight(const SDL_Color&);
            void setNativeRes(const glm::vec2& v);
            void setBackgroundColor(const SDL_Color&);

			void renderSceneForShadowMap(Shader*);

            static MainClass* getInstance() {return instance;}

            InputManager* getInputManager() {return m_inputManager;}
            ResourceManager* getResourceManager() {return m_resourceManager;}
            WindowHandle* getWindow() {return m_window;}
            JoystickManager* getJoystickManager() {return m_joystickManager;}
			Lighting* getLighting() { return m_lighting; }
			RenderManager* getRenderManager() { return m_renderManager; }
			FrameBuffer* getBackBuffer() { return m_frameBufferMulti; }
			Mesh* getBackBufferMesh() { return m_frameBufferMesh; }
			Skybox* getSkybox() { return m_skybox; }

            Camera* getCamera();
            int getMaxFPS() {return m_maxFPS;}
            float getScaleW() const {return m_scaleW;}
            float getScaleH() const {return m_scaleH;}
            const glm::vec2& getNativeRes() const {return m_nativeResolution;}
            #ifdef _WIN32
            float getDeltaTimeInSeconds() const {return (float)(m_realDeltaTimeInSeconds*m_timeScale);}
            #else
            float getDeltaTimeInSeconds() const {return (float)(m_smoothDeltaTimeInSeconds*m_timeScale);}
            #endif
            double getFPS() const {return m_fps;}
            const SDL_Color& getBackgroundColor() const {return m_backgroundColor;}
            void activateJoystick();
            
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

            int m_maxFPS = 60;
            InputManager* m_inputManager = nullptr;
            ResourceManager* m_resourceManager = nullptr;
            WindowHandle* m_window = nullptr;
            Camera* m_camera = nullptr;
            JoystickManager* m_joystickManager = nullptr;
			Lighting* m_lighting = nullptr;
			RenderManager* m_renderManager = nullptr;
			Skybox* m_skybox = nullptr;

            double m_timeScale = 1.0;

        private:
            static MainClass* instance;

			void afterInit();
            void m_quit();

            void startTimeMeasure();
            void mainLoop();
            int endTimeMeasure();

            void m_init();

			Mesh* m_frameBufferMesh = nullptr;
			FrameBuffer* m_frameBufferMulti = nullptr;
			FrameBuffer* m_frameBuffer = nullptr;
			RenderBuffer* m_renderBufferMulti = nullptr;
			RenderBuffer* m_renderBuffer = nullptr;
			Texture* m_frameBufferTexMulti = nullptr;
			Texture* m_frameBufferTex = nullptr;

            const char* m_windowTitle;
            int m_windowWidth;
            int m_windowHeight;


            double calculateMeanDeltaTime();
            void takeAwayHighestAndLowestDts();
            void moveDeltaTimesOneIndexDown();
            int getDeltaTimesSize();
            void copyRealTimesToSmoothTimes();
            int m_realDeltaTimeSize = 0;
            void setNum(double&,int&);
            double m_realDeltaTimeInSeconds = 0.0;
            double m_smoothDeltaTimeInSeconds = 0.0;
            double m_realDeltaTimes[11] = {-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0};
            double m_smoothDeltaTimes[11] = {-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0};
            double m_FPSes[3];
            double m_fps = 0.0;
            int m_lastFrame = 0;

            float m_scaleW;
            float m_scaleH;

			GLint m_viewportOffsetX = 0;
			GLint m_viewportOffsetY = 0;

            double m_time = 0.0;
            high_resolution_clock::time_point m_startTime;
            high_resolution_clock::time_point m_endTime;
            #ifdef MAX_FPS_LOCK
            double m_timeForMaxFPS = 0.0;
            high_resolution_clock::time_point m_startTimeForMaxFPS;
            high_resolution_clock::time_point m_endTimeForMaxFPS;
            duration<double,micro> m_deltaClockTimeForMaxFPS;
            #endif
            duration<double,micro> m_deltaClockTime;
            
            FPSmanager m_fpsManager;
            
            SDL_Color m_backgroundColor;
        
            glm::vec2 m_nativeResolution;
			Uint32 m_initWindowFlags = 0;
    };
}



#endif // MAINCLASS_H
