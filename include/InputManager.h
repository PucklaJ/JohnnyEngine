#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <map>
#include "Actor.h"

using namespace std;
    struct Mouse
    {
        unsigned int x;
        unsigned int y;
		int xrel;
		int yrel;
        signed int wheel_x;
        signed int wheel_y;
    };

    class InputManager : public SDL::Actor
    {
        public:
            InputManager();
            virtual ~InputManager();

             bool isPressed(unsigned int kc);
             bool justPressed(unsigned int kc);

             void releaseKey(unsigned int kc);
             void pressKey(unsigned int kc);
             void setMouseCoords(unsigned int x,unsigned int y);
             void setMouseWheel(int wheel_x,int wheel_y);
			 void setMouseRel(int x, int y);

             bool update();

            const Mouse& getMouse()
            {
                return m_mouse;
            }

        protected:

        private:
             map<unsigned int,bool> m_keyMap;
             map<unsigned int,bool> m_previousKeyMap;

             bool wasPressed(unsigned int kc);
             Mouse m_mouse;

    };


#endif // INPUTMANAGER_H
