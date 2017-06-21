#ifndef JOYSTCKMANAGER_H
#define JOYSTCKMANAGER_H
#include <vector>
#include <SDL2/SDL_events.h>

namespace SDL
{
    class JoystickListener;

    class JoystickManager
    {
        public:
            JoystickManager();
            virtual ~JoystickManager();

            void pollEvents(const SDL_Event& e);
            void update();

            void setListener(JoystickListener*);
            void addController(SDL_GameController*);
            void removeController(SDL_GameController*);
            void removeController(int);

            std::vector<SDL_GameController*>& getControllers(){return m_controllers;}

        protected:

        private:
            JoystickListener* m_listener = nullptr;
            std::vector<SDL_GameController*> m_controllers;
    };
}


#endif // JOYSTCKMANAGER_H
