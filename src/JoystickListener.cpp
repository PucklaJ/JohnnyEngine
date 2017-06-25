#include <JoystickListener.h>
#include <JoystickManager.h>
#include <LogManager.h>
#include <operators.h>
#include <iostream>
//#define DEBUG_OUTPUTS

namespace SDL
{
    JoystickListener::JoystickListener()
    {
        //ctor
    }

    JoystickListener::~JoystickListener()
    {
        //dtor
    }

    void JoystickListener::setManager(JoystickManager* jm)
    {
        m_manager = jm;
    }

    void JoystickListener::onAxisMotion(const SDL_ControllerAxisEvent& e)
    {
#ifdef DEBUG_OUTPUTS
    	std::cout << "onAxisMotion start" << std::endl;
#endif
        int index = -1;

        for(size_t i = 0;i<m_manager->getControllers().size();i++)
        {
#ifdef DEBUG_OUTPUTS
        	std::cout << "Checking Controller: " << i << std::endl;
#endif
            if(m_manager->getControllers()[i] == nullptr)
            {
#ifdef DEBUG_OUTPUTS
            std::cout << "Controller: " << i << " is nullptr" << std::endl;
#endif
            	continue;
            }

#ifdef DEBUG_OUTPUTS
            std::cout << "Getting JoystickID" << std::endl;
#endif
            if(SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(m_manager->getControllers()[i])) == e.which)
            {
                index = (int)i;
                break;
            }
#ifdef DEBUG_OUTPUTS
            std::cout << "Controller " << i << " is not the one" << std::endl;
#endif
        }

        if(index == -1)
        {
#ifdef DEBUG_OUTPUTS
        	std::cout << "Index of controller is -1" << std::endl;
#endif
            return;
        }
#ifdef DEBUG_OUTPUTS
        std::cout << "Controller found: " << index << std::endl;
#endif

        for(AbIterator it = m_abLis.begin();it!=m_abLis.end();it++)
        {
            if(it->first == index)
            {
#ifdef DEBUG_OUTPUTS
            	std::cout << "There is a listener with index: " << index << std::endl;
#endif
                for(size_t i = 0;i<it->second.size();i++)
                {
#ifdef DEBUG_OUTPUTS
                	std::cout << "Running on Axis motion of listener: " << i << std::endl;
#endif
                    it->second[i]->onAxisMotion(e);
                }
            }
        }
#ifdef DEBUG_OUTPUTS
        std::cout << "onAxisMotion End" << std::endl;
#endif
    }

    int Uint8ToInt(Uint8 u)
    {
        int n = 0;
        for(int i = 0;i<8;i++)
        {
            if(u&(1<<i))
            {
                n |= (1<<i);
            }
        }

        return n;
    }

    void JoystickListener::onButtonDown(const SDL_ControllerButtonEvent& e)
    {
#ifdef DEBUG_OUTPUTS
    	std::cout << "onButtonDown start" << std::endl;
#endif
        int index = -1;

        for(size_t i = 0;i<m_manager->getControllers().size();i++)
        {
            if(m_manager->getControllers()[i] == nullptr)
               continue;

            if(SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(m_manager->getControllers()[i])) == e.which)
            {
                index = (int)i;
                break;
            }
        }

        if(index == -1)
        {
            return;
        }


        for(AbIterator it = m_abLis.begin();it!=m_abLis.end();it++)
        {
            if(it->first == index)
            {
                for(size_t i = 0;i<it->second.size();i++)
                {
                    it->second[i]->onButtonDown(e);
                }
            }
        }

#ifdef DEBUG_OUTPUTS
        std::cout << "onButtonDown end" << std::endl;
#endif
    }


    void JoystickListener::onButtonUp(const SDL_ControllerButtonEvent& e)
    {
#ifdef DEBUG_OUTPUTS
    	std::cout << "onButtonUp start" << std::endl;
#endif
        int index = -1;

        for(size_t i = 0;i<m_manager->getControllers().size();i++)
        {
            if(m_manager->getControllers()[i] == nullptr)
                continue;

            if(SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(m_manager->getControllers()[i])) == e.which)
            {
                index = (int)i;
                break;
            }
        }

        if(index == -1)
        {
            return;
        }

        for(AbIterator it = m_abLis.begin();it!=m_abLis.end();it++)
        {
            if(it->first == index)
            {
                for(size_t i = 0;i<it->second.size();i++)
                {
                    it->second[i]->onButtonUp(e);
                }
            }
        }
#ifdef DEBUG_OUTPUTS
        std::cout << "onButtonUp end" << std::endl;
#endif
    }

    void JoystickListener::onConnect(const SDL_ControllerDeviceEvent& e)
    {
#ifdef DEBUG_OUTPUTS
    	std::cout << "onConnect start" << std::endl;
#endif
        LogManager::log("Controller connected");
        m_manager->addController(SDL_GameControllerOpen(e.which));

        for(size_t i = 0;i<m_conLis.size();i++)
        {
            m_conLis[i]->onConnect(e);
        }
#ifdef DEBUG_OUTPUTS
        std::cout << "onConnect end" << std::endl;
#endif
    }

    void JoystickListener::onDisconnect(const SDL_ControllerDeviceEvent& e)
    {
#ifdef DEBUG_OUTPUTS
    	std::cout << "onDisconnect start" << std::endl;
#endif
        LogManager::log("Controller disconnected");

        for(size_t i = 0;i<m_conLis.size();i++)
        {
            m_conLis[i]->onDisconnect(e);
        }
#ifdef DEBUG_OUTPUTS
        std::cout << "onDisconnect end" << std::endl;
#endif
    }

    void JoystickListener::addListener(AxisButtonListener* a, int i)
    {
        for(AbIterator it = m_abLis.begin();it!=m_abLis.end();it++)
        {
            if(it->first == i)
            {
                it->second.push_back(a);
                return;
            }
        }

        std::vector<AxisButtonListener*> vec;
        vec.push_back(a);

        m_abLis.insert(std::pair<int,std::vector<AxisButtonListener*>>(i,vec));

        a->setListener(this);
    }

    void JoystickListener::addListener(ConnectionListener* a, int)
    {
       m_conLis.push_back(a);
       a->setListener(this);
    }

    void JoystickListener::removeListener(AxisButtonListener* abl)
    {
    	for(AbIterator it = m_abLis.begin();it!=m_abLis.end();it++)
    	{
    		for(size_t i = 0;i<it->second.size();i++)
    		{
    			if(it->second[i] == abl)
    			{
    				it->second[i] = it->second.back();
    				it->second.pop_back();

    				if(it->second.empty())
    				{
    					m_abLis.erase(it);
    				}
    				break;
    			}
    		}
    	}
    }

    void JoystickListener::removeListener(ConnectionListener* cl)
    {
    	for(size_t i = 0;i<m_conLis.size();i++)
    	{
    		if(m_conLis[i] == cl)
    		{
    			m_conLis[i] = m_conLis.back();
    			m_conLis.pop_back();
    			break;
    		}
    	}
    }

    /*AxisButtonListener::~AxisButtonListener()
    {
    	m_listener->removeListener(this);
    }*/

    ConnectionListener::~ConnectionListener()
    {
    	m_listener->removeListener(this);
    }

    void AxisButtonListener::setListener(JoystickListener* l)
    {
        m_listener = l;
    }

    void ConnectionListener::setListener(JoystickListener* l)
    {
        m_listener = l;
    }


}
