#include "../include/JoystickManager.h"
#include "../include/JoystickListener.h"
#include <SDL2/SDL_joystick.h>
#include <iostream>
#include "../include/LogManager.h"
#include "../include/operators.h"
#include <SDL2/SDL_events.h>
#include "../include/MainClass.h"
//#define DEBUG_OUTPUTS

namespace Johnny
{
    JoystickManager::JoystickManager()
    {
        //ctor
    }

    JoystickManager::~JoystickManager()
    {
        if(m_listener)
        delete m_listener;
    }
    void JoystickManager::setListener(JoystickListener* jl)
    {
        m_listener = jl;
        m_listener->setManager(this);
    }


    void JoystickManager::pollEvents(const Event& e)
    {
#ifdef DEBUG_OUTPUTS
    	std::cout << "JoystickManager pollEvents" << std::endl;
#endif
        switch(e.type)
        {
        case EventType::ControllerAxisMotion:
            m_listener->onAxisMotion(e.caxis);
            break;
        case EventType::ControllerButtonDown:
            m_listener->onButtonDown(e.cbutton);
            break;
        case EventType::ControllerButtonUp:
            m_listener->onButtonUp(e.cbutton);
            break;
        case EventType::ControllerDeviceAdded:
            m_listener->onConnect(e.cdevice);
            break;
        case EventType::ControllerDeviceRemoved:
            m_listener->onDisconnect(e.cdevice);
            break;
        default:
            break;
        }
#ifdef DEBUG_OUTPUTS
        std::cout << "JoystickManager pollEvents end" << std::endl;
#endif
    }

    void JoystickManager::addController(void* j)
    {
        for(size_t i = 0;i<m_controllers.size();i++)
        {
            if(m_controllers[i] == nullptr)
                continue;
            if(MainClass::getInstance()->getFramework()->isSameController(j,m_controllers[i]))
                return;
        }

        for(size_t i = 0;i<m_controllers.size();i++)
        {
            if(m_controllers[i] == nullptr)
            {
                LogManager::log("Added Controller as nullptr");
                m_controllers[i] = j;
                return;
            }
        }

        m_controllers.push_back(j);
    }

    void JoystickManager::removeController(void* j)
    {
        for(size_t i = 0;i<m_controllers.size();i++)
        {
            if(MainClass::getInstance()->getFramework()->isSameController(j,m_controllers[i]))
            {
                MainClass::getInstance()->getFramework()->closeController(m_controllers[i]);
                m_controllers[i] = nullptr;
                break;
            }

        }
    }
    void JoystickManager::removeController(int which)
    {
        for(size_t i = 0;i<m_controllers.size();i++)
        {
            if(MainClass::getInstance()->getFramework()->getControllerID(m_controllers[i]) == which)
            {
                MainClass::getInstance()->getFramework()->closeController(m_controllers[i]);
                m_controllers[i] = nullptr;
                break;
            }
        }
    }

    void JoystickManager::update()
    {
        if(m_listener == nullptr)
        {
            LogManager::error("Listener of JoystickManager is nullptr!");
            return;
        }

        for(size_t i = 0;i<m_controllers.size();i++)
        {
            if(m_controllers[i] == nullptr)
                continue;

            if(MainClass::getInstance()->getFramework()->isAttachedController(m_controllers[i]) == false)
            {
                MainClass::getInstance()->getFramework()->closeController(m_controllers[i]);
                m_controllers[i] = nullptr;
            }
        }

    }

}
