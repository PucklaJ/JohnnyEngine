#ifndef JOYSTCKMANAGER_H
#define JOYSTCKMANAGER_H
#include <vector>
#include <SDL2/SDL_events.h>

namespace Johnny
{
    class JoystickListener;

    /* \brief The class which manages all controller specific things
     *
     */
    class JoystickManager
    {
        public:
            JoystickManager();
            virtual ~JoystickManager();

            /* \brief Polls the controller events
             * \param e The event from which to poll
             */
            void pollEvents(const SDL_Event& e);
            /* \brief Updates the JoystickManager
             *
             */
            void update();

            /* \brief Sets the JoystickListener
             * \param jl The JoystickListener to set
             */
            void setListener(JoystickListener* jl);
            /* \brief Adds a controller to the vector
             * \param gc The controller to add
             */
            void addController(SDL_GameController* gc);
            /* \brief Removes a controller from the vector
             * \param gc The controller to remove
             */
            void removeController(SDL_GameController* gc);
            /* \brief Removes a controller with an index from the vector
             * \param index The index of te controller
             */
            void removeController(int index);

            std::vector<SDL_GameController*>& getControllers(){return m_controllers;}
            
        private:
            JoystickListener* m_listener = nullptr;         //!< The JoystickListener of the object
            std::vector<SDL_GameController*> m_controllers; //!< The vector which holds the controllers
    };
}


#endif // JOYSTCKMANAGER_H
