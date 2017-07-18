#include "../include/JoystickManager.h"
#include "../include/JoystickListener.h"
#include <SDL2/SDL_joystick.h>
#include <iostream>
#include "../include/LogManager.h"
#include "../include/operators.h"
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


    void JoystickManager::pollEvents(const SDL_Event& e)
    {
#ifdef DEBUG_OUTPUTS
    	std::cout << "JoystickManager pollEvents" << std::endl;
#endif
        switch(e.type)
        {
        case SDL_CONTROLLERAXISMOTION:
            m_listener->onAxisMotion(e.caxis);
            break;
        case SDL_CONTROLLERBUTTONDOWN:
            m_listener->onButtonDown(e.cbutton);
            break;
        case SDL_CONTROLLERBUTTONUP:
            m_listener->onButtonUp(e.cbutton);
            break;
        case SDL_CONTROLLERDEVICEADDED:
            m_listener->onConnect(e.cdevice);
            break;
        case SDL_CONTROLLERDEVICEREMOVED:
            m_listener->onDisconnect(e.cdevice);
            break;
        }
#ifdef DEBUG_OUTPUTS
        std::cout << "JoystickManager pollEvents end" << std::endl;
#endif
    }

    bool equal(Uint8 u1[], Uint8 u2[])
    {
        int size = sizeof((Uint8*)u1)/sizeof(*u1);
        for(int i = 0;i<size;i++)
        {
            if(u1[i] != u2[i])
            {
                return false;
            }
        }
        return true;
    }

    void JoystickManager::addController(SDL_GameController* j)
    {
        for(size_t i = 0;i<m_controllers.size();i++)
        {
            if(m_controllers[i] == nullptr)
                continue;
            if(equal(SDL_JoystickGetGUID(SDL_GameControllerGetJoystick(j)).data,SDL_JoystickGetGUID(SDL_GameControllerGetJoystick(m_controllers[i])).data))
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

    void JoystickManager::removeController(SDL_GameController* j)
    {
        for(size_t i = 0;i<m_controllers.size();i++)
        {
            if(equal(SDL_JoystickGetGUID(SDL_GameControllerGetJoystick(j)).data,SDL_JoystickGetGUID(SDL_GameControllerGetJoystick(m_controllers[i])).data))
            {
                SDL_GameControllerClose(m_controllers[i]);
                m_controllers[i] = nullptr;
                break;
            }

        }
    }
    void JoystickManager::removeController(int which)
    {
        for(size_t i = 0;i<m_controllers.size();i++)
        {
            if(SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(m_controllers[i])) == which)
            {
                SDL_GameControllerClose(m_controllers[i]);
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

            if(SDL_GameControllerGetAttached(m_controllers[i]) == SDL_FALSE)
            {
                SDL_GameControllerClose(m_controllers[i]);
                m_controllers[i] = nullptr;
            }
        }

    }

}
