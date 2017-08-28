#ifndef JOYSTICKLISTENER_H
#define JOYSTICKLISTENER_H
#include <SDL2/SDL_events.h>
#include <vector>
#include <map>

namespace Johnny
{
    /* \brief Converts a Uint8 to a int
     * \param u The Uint8 to convert
     * \return The resulting integer
     */
    extern int Uint8ToInt(Uint8 u);
    namespace Buttons
    {
        const int UP = 11,
                  DOWN = 12,
                  LEFT = 13,
                  RIGHT = 14,
                  START = 6,
                  SELECT = 4,
                  L3 = 7,
                  R3 = 8,
                  L1 = 9,
                  R1 = 10,
                  CROSS = 0,
                  CIRCLE = 1,
                  SQUARE = 2,
                  TRIANGLE = 3,
                  BACK=SELECT,
                  LS=L3,
                  RS=R3,
                  LB=L1,
                  RB=R1,
                  A=CROSS,
                  B=CIRCLE,
                  X=SQUARE,
                  Y=TRIANGLE;
    };
	
	namespace Axis
    {
        const int LEFT_STICK_X=0,
                  LEFT_STICK_Y=1,
                  RIGHT_STICK_X=2,
                  RIGHT_STICK_Y=3,
                  L2=4,
                  R2=5,
                  LT=L2,
                  RT=R2;


    };

    class JoystickListener;

    /* \brief A Listener class which catches button input and axis movement of a controller
     *
     */
    class AxisButtonListener
    {
    public:
    	virtual ~AxisButtonListener(){}
      /* \brief Gets called when a stick or a trigger gets moved
       * \param e A struct which holds information about the event
       */
      virtual void onAxisMotion(const SDL_ControllerAxisEvent& e)=0;
      /* \brief Gets called when a button is pressed
       * \param e A struct which holds information about the event
       */
      virtual void onButtonDown(const SDL_ControllerButtonEvent& e)=0;
      /* \brief Gets called when a button is released
       * \param e A struct which holds information about the event
       */
      virtual void onButtonUp(const SDL_ControllerButtonEvent& e)=0;

      /* \brief Sets the JoystickListener of the object
       * \param jl The JoystickListener to set
       */
      void setListener(JoystickListener* jl);
    protected:
        JoystickListener* m_listener; //!< The JoystickListener of the object
    private:

    };

    /* \brief A Listener class which listens to controllers connecting and disconnecting
     *
     */
    class ConnectionListener
    {
    public:
    	virtual ~ConnectionListener();

      /* \brief Gets called when a controller connects
       * \param e A struct which holds infotmation about the event
       */
      virtual void onConnect(const SDL_ControllerDeviceEvent& e)=0;
      /* \brief Gets called when a controller disconnects
       * \param e A struct which holds information about the event
       */
      virtual void onDisconnect(const SDL_ControllerDeviceEvent& e)=0;

      /* \brief Sets the JoystickListener of the object
       * \param jl The JoystickListener to set
       */
      void setListener(JoystickListener* jl);
    protected:
      JoystickListener* m_listener; //!< The JoystickListener of the object
    private:

    };

    class JoystickManager;

    /* \brief The main JoystickListener class which fetches all ControllerInputs
     *
     */
    class JoystickListener
    {
        public:
            JoystickListener();
            virtual ~JoystickListener();

            /* \brief Sets the JoystickManager
             * \param jm The JoystickManager to set
             */
            void setManager(JoystickManager* jm);
            /* \return The JoystickManager of the object
             *
             */
            JoystickManager* getManager(){return m_manager;}

            /* \brief Gets called when a axsis or trigger of a controller is moved
             * \param e A struct which holds information about the event
             */
            void onAxisMotion(const SDL_ControllerAxisEvent& e);
            /* \brief Gets called when a button of a controller is pressed
             * \param e A struct which holds information about the event
             */
            void onButtonDown(const SDL_ControllerButtonEvent& e);
            /* \brief Gets called when a button of a controller is released
             * \param e A struct which holds information about the event
             */
            void onButtonUp(const SDL_ControllerButtonEvent& e);
            /* \brief Gets called when a controller connects
             * \param e A struct which holds information about the event
             */
            void onConnect(const SDL_ControllerDeviceEvent& e);
            /* \brief Gets called when a controller disconnects
             * \param e A struct which holds information about the event
             */
            void onDisconnect(const SDL_ControllerDeviceEvent& e);

            /* \brief Attaches a AxisButtonListener to a specific controller id
             * \param abl The listener to attach
             * \param id The id to which the listener gets attached
             */
            void addListener(AxisButtonListener* abl,int id);
            /* \brief Attaches a ConnectionListener
             * \param cl The listener to attach
             */
            void addListener(ConnectionListener* cl);
            /* \brief Remove a AxisButtonListener from this listener
             * \param abl The listener to remove
             */
            void removeListener(AxisButtonListener* abl);
            /* \brief Removes a ConnectionListener from this listener
             * \param cl The listener to remove
             */
            void removeListener(ConnectionListener* cl);

        protected:
            JoystickManager* m_manager = nullptr; //!< The JoystickManager of the object
        private:
            std::map<int,std::vector<AxisButtonListener*>> m_abLis; //!< The map which holds all AxisButtonListeners with the specific ids
            std::vector<ConnectionListener*> m_conLis;              //!< The vector which holds all ConnectionListeners


    };

    /* \brief A Iterator which iterates over the m_abLis map
     *
     */
    typedef std::map<int,std::vector<AxisButtonListener*>>::iterator AbIterator ;
}


#endif // JOYSTICKLISTENER_H
