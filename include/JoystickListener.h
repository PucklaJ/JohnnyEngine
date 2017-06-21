#ifndef JOYSTICKLISTENER_H
#define JOYSTICKLISTENER_H
#include <SDL2/SDL_events.h>
#include <vector>
#include <map>

namespace SDL
{
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

    class AxisButtonListener
    {
    public:
    	virtual ~AxisButtonListener(){}
        virtual void onAxisMotion(const SDL_ControllerAxisEvent&)=0;
        virtual void onButtonDown(const SDL_ControllerButtonEvent&)=0;
        virtual void onButtonUp(const SDL_ControllerButtonEvent&)=0;

        void setListener(JoystickListener*);
    protected:
        JoystickListener* m_listener;
    private:

    };

    class ConnectionListener
    {
    public:
    	virtual ~ConnectionListener();

        virtual void onConnect(const SDL_ControllerDeviceEvent&)=0;
        virtual void onDisconnect(const SDL_ControllerDeviceEvent&)=0;

        void setListener(JoystickListener*);
    protected:
        JoystickListener* m_listener;
    private:

    };

    class JoystickManager;

    class JoystickListener
    {
        public:
            JoystickListener();
            virtual ~JoystickListener();

            void setManager(JoystickManager*);
            JoystickManager* getManager(){return m_manager;}

            void onAxisMotion(const SDL_ControllerAxisEvent&);
            void onButtonDown(const SDL_ControllerButtonEvent&);
            void onButtonUp(const SDL_ControllerButtonEvent&);
            void onConnect(const SDL_ControllerDeviceEvent&);
            void onDisconnect(const SDL_ControllerDeviceEvent&);

            void addListener(AxisButtonListener*,int);
            void addListener(ConnectionListener*,int);
            void removeListener(AxisButtonListener*);
            void removeListener(ConnectionListener*);

        protected:
            JoystickManager* m_manager = nullptr;
        private:
            std::map<int,std::vector<AxisButtonListener*>> m_abLis;
            std::vector<ConnectionListener*> m_conLis;


    };

    typedef std::map<int,std::vector<AxisButtonListener*>>::iterator AbIterator ;
}


#endif // JOYSTICKLISTENER_H
