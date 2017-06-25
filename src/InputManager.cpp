#include <InputManager.h>
#include <iostream>

using namespace std;

typedef map<unsigned int,bool>::iterator mapIt;

    InputManager::InputManager()
    {
		m_castsShadows = false;
    }

    InputManager::~InputManager()
    {

    }
    bool InputManager::justPressed(unsigned int kc)
    {
        bool re = isPressed(kc) && !wasPressed(kc);
        return re;
    }

    bool InputManager::isPressed(unsigned int kc)
    {
        mapIt it = m_keyMap.find(kc);

        if(it != m_keyMap.end())
        {
            return m_keyMap[kc];
        }

        return false;
    }

    bool InputManager::wasPressed(unsigned int kc)
    {
        mapIt it = m_previousKeyMap.find(kc);
        if(it != m_previousKeyMap.end())
        {
            return m_previousKeyMap[kc];
        }

        return false;
    }

    bool InputManager::update()
    {
        for(mapIt it = m_keyMap.begin();it != m_keyMap.end();it++)
        {
            m_previousKeyMap[it->first] = it->second;
        }

		m_mouse.xrel = m_mouse.yrel = m_mouse.wheel_x = m_mouse.wheel_y = 0;

        return true;
    }

    void InputManager::releaseKey(unsigned int kc)
    {
        m_keyMap[kc] = false;
    }

    void InputManager::pressKey(unsigned int kc)
    {
        m_keyMap[kc] = true;
    }

    void InputManager::setMouseCoords(unsigned int x, unsigned int y)
    {
        m_mouse.x = x;
        m_mouse.y = y;
    }
    
    void InputManager::setMouseWheel(int wheel_x,int wheel_y)
    {
        m_mouse.wheel_x = wheel_x;
        m_mouse.wheel_y = wheel_y;
    }

	void InputManager::setMouseRel(int x, int y)
	{
		m_mouse.xrel = x;
		m_mouse.yrel = y;
	}









