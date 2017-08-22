#include "../include/Actor.h"
#include <cstdlib>
#include <algorithm>
#include "../include/Camera3D.h"
#include "../include/MainClass.h"
#include "../include/LogManager.h"
#include <sstream>
#include <string>
#include <iostream>
#include <cstdio>
#include "../include/RenderManager.h"
//#define DEBUG_OUTPUTS


namespace Johnny
{
    template<class t>
    const char* toString(t number)
    {
        std::string str;
        std::stringstream stream;

        stream << number;
        stream >> str;
        stream.clear();

        return str.c_str();
    }

    std::vector<int> Actor::m_ids;
	std::vector<Actor*> Actor::m_allActors;

    Actor::Actor(const char* name) :
        m_name(name),
        m_parent(nullptr)
    {
        do
        {
            m_id = rand();
        }while(std::find(m_ids.begin(),m_ids.end(),m_id) != m_ids.end());

		m_allActors.push_back(this);
    }

    Actor::~Actor()
    {
		for (size_t i = 0; i < m_allActors.size(); i++)
		{
			if (m_allActors[i] == this)
			{
				m_allActors[i] = m_allActors.back();
				m_allActors.pop_back();
			}
		}
    }

    bool Actor::m_update()
    {
#ifdef DEBUG_OUTPUTS
    	std::cout << "m_update: " << m_name << std::endl;
    	std::cout << "Children: " << m_children.size() << std::endl;
#endif
        for(std::size_t i = 0;i<m_children.size();i++)
        {
#ifdef DEBUG_OUTPUTS
        	std::cout << "Children[" << i << "]: " << m_children[i]->getName() << std::endl;
#endif

            if(!m_children[i]->m_all_update())
                return false;
        }
#ifdef DEBUG_OUTPUTS
        std::cout << "Updated Children" << std::endl;
        std::cout << "Updateing Tweens" << std::endl;
#endif
#ifdef DEBUG_OUTPUTS
        std::cout << "End of m_update: " << m_name << std::endl;
#endif

        return true;
    }

    bool Actor::render()
    {
        return true;
    }

    void Actor::quit()
    {

    }

    void Actor::m_quit()
    {
        removeChildrenAfterLoops();

        m_parent = nullptr;
        for(std::size_t i = 0;i<m_children.size();i++)
        {
            m_children[i]->m_all_quit();
            delete m_children[i];
        }
        m_children.clear();
    }

    bool Actor::addChild(Actor* a,bool instantAdd)
    {
#ifdef DEBUG_OUTPUTS
    	std::cout << "AddChild: " << a->getName() << std::endl;
#endif

        if(a->getID() == getID() || isChild(a))
            return true;

        if(!instantAdd)
        {
            m_childrenToAdd.push_back(a);
        }
        else
        {
            Actor* p = a->getParent();
            if(p)
            {
                p->removeChild(a,false);
            }

            a->setParent(this);
            a->setMainClass(m_mainClass);

            m_children.push_back(a);

            if(!a->m_initialised)
            {
                a->m_initialised = true;
                return a->init();
            }
        }

        return true;
    }

    bool Actor::addChildrenBeforeLoops()
    {
#ifdef DEBUG_OUTPUTS
    	std::cout << "Add Children Before Loops: " << m_name << std::endl;
#endif

        if(m_childrenToAdd.empty())
        {
#ifdef DEBUG_OUTPUTS
        	std::cout << "Returned From Empty" << std::endl;
#endif
        	return true;
        }


        for(size_t i = 0;i<m_childrenToAdd.size();i++)
        {
#ifdef DEBUG_OUTPUTS
        	std::cout << "ChildrenToAdd[" << i << "]: " << m_name << std::endl;
#endif

            Actor* p = m_childrenToAdd[i]->getParent();
            if(p)
            {
#ifdef DEBUG_OUTPUTS
            	std::cout << "Removing parent" << std::endl;
#endif
                p->removeChild(m_childrenToAdd[i],false);
            }

#ifdef DEBUG_OUTPUTS
            std::cout << "setting variables" << std::endl;
#endif

            m_childrenToAdd[i]->setParent(this);
            m_childrenToAdd[i]->setMainClass(m_mainClass);

#ifdef DEBUG_OUTPUTS
            std::cout << "Adding to array" << std::endl;
#endif
            m_children.push_back(m_childrenToAdd[i]);

            if(!m_childrenToAdd[i]->m_initialised)
            {
#ifdef DEBUG_OUTPUTS
            	std::cout << "initializing child" << std::endl;
#endif
                if(!m_childrenToAdd[i]->init())
                    return false;
                m_childrenToAdd[i]->m_initialised = true;
#ifdef DEBUG_OUTPUTS
                std::cout << "initialized" << std::endl;
#endif
            }


        }

        m_childrenToAdd.clear();
#ifdef DEBUG_OUTPUTS
        std::cout << "ChildrenBeforeLoops End" << std::endl;
#endif

        return true;
    }

    bool Actor::isChild(Actor* a)
    {
        for(std::size_t i = 0;i<m_children.size();i++)
        {
            if(m_children[i]->getID() == a->getID())
            {
                return true;
            }
        }

        return false;
    }

    void Actor::setParent(Actor* a)
    {
        m_parent = a;
    }

    void Actor::removeChild(Actor* a,bool del,bool instant)
    {
        if(!instant)
        {
            m_idsToRemove.push_back(a->getID());
            m_ifDeleteToRemove.push_back(del);
        }
        else
        {
            for(std::size_t i = 0;i<m_children.size();i++)
            {
                if(m_children[i]->getID() == a->getID())
                {
                    if(del)
                    {
                        m_children[i]->m_all_quit();
                        delete m_children[i];
                    }
                    m_children[i] = m_children.back();
                    m_children.pop_back();

                    return;
                }
            }
        }

    }
    
    void Actor::setAllChildrenWithNullShaderToDefaultShader()
    {
        for(size_t i = 0;i<m_children.size();i++)
        {
            if(m_children[i]->getShader() == nullptr)
                m_children[i]->setShader(RenderManager::DEFAULT_SHADER);
            
            m_children[i]->setAllChildrenWithNullShaderToDefaultShader();
        }
    }

    void Actor::removeChildrenAfterLoops()
    {
#ifdef DEBUG_OUTPUTS
    	std::cout << "Remove Children After Loops: " << m_name << std::endl;
#endif
        if(m_idsToRemove.empty())
        {
#ifdef DEBUG_OUTPUTS
        	std::cout << "Returned From Empty" << std::endl;
#endif
        	return;
        }


        int id;
        bool del;
        for(size_t u = 0;u < m_idsToRemove.size();u++)
        {
            id = m_idsToRemove[u];
            del = m_ifDeleteToRemove[u];
#ifdef DEBUG_OUTPUTS
            std::cout << "Reovable[" << u << "]: " << m_name << std::endl;
#endif

            for(std::size_t i = 0;i<m_children.size();i++)
            {
                if(m_children[i]->getID() == id)
                {
                    if(del)
                    {
#ifdef DEBUG_OUTPUTS
                    	std::cout << "Found and Delete" << std::endl;
#endif
                        m_children[i]->m_all_quit();
                        delete m_children[i];
                    }
                    m_children[i] = m_children.back();
                    m_children.pop_back();
                    break;
                }
            }
        }

        m_idsToRemove.clear();
        m_ifDeleteToRemove.clear();
    }

    void Actor::m_all_quit()
    {
        quit();
        m_quit();
    }

    bool Actor::m_all_update()
    {
#ifdef DEBUG_OUTPUTS
    	std::cout << "m_all_update: " << m_name << std::endl;
#endif
        if(!addChildrenBeforeLoops())
            return false;

        if(!(update() && m_update()))
            return false;
#ifdef DEBUG_OUTPUTS
        std::cout << "m_all_update end: " << m_name << std::endl;
#endif
        return true;
    }

    void Actor::setMainClass(MainClass* mc)
    {
        m_mainClass = mc;
    }

    MainClass* Actor::getMainClass()
    {
        return m_mainClass;
    }

    bool Actor::init()
    {
        return true;
    }

    void Actor::setAffectedByCamera(const bool b)
    {
        m_isAffectedByCamera = b;
    }

    void Actor::setVisible(const bool b)
    {
        m_visible = b;
    }

	void Actor::setShader(Shader * s, bool changeInRenderManager)
	{
		if (m_mainClass && changeInRenderManager)
		{
			m_mainClass->getRenderManager()->removeActor(this);
		}
		m_shader = s;

		if (m_mainClass && changeInRenderManager)
		{
			m_mainClass->getRenderManager()->addActor(this);
		}
	}

    bool Actor::isOnScreen()
    {
        return true;
    }

	std::vector<Actor*> Actor::getChildrenWithCastsShadow()
	{
		std::vector<Actor*> actors;
		std::vector<Actor*> childActors;
		for (size_t i = 0; i < m_children.size(); i++)
		{
			if (m_children[i]->castsShadows())
			{
				actors.push_back(m_children[i]);
				childActors = m_children[i]->getChildrenWithCastsShadow();
				for (size_t j = 0; j < childActors.size(); j++)
					actors.push_back(childActors[i]);
			}
		}

		return actors;
	}

    bool Actor::m_render_render()
    {
        if(!m_visible)
        {
#ifdef DEBUG_OUTPUTS
        std::cout << "Children Before: " << m_children.size() << std::endl;
#endif

        removeChildrenAfterLoops();
#ifdef DEBUG_OUTPUTS
        std::cout << "Children After: " << m_children.size() << std::endl;
#endif
        return true;
        }


        if(!isOnScreen())
        {
#ifdef DEBUG_OUTPUTS
        std::cout << "Children Before: " << m_children.size() << std::endl;
#endif

        removeChildrenAfterLoops();
#ifdef DEBUG_OUTPUTS
        std::cout << "Children After: " << m_children.size() << std::endl;
#endif
            return true;
        }

        if(!render())
        {
#ifdef DEBUG_OUTPUTS
			std::cout << "Children Before: " << m_children.size() << std::endl;
#endif
			removeChildrenAfterLoops();
#ifdef DEBUG_OUTPUTS
			std::cout << "Children After: " << m_children.size() << std::endl;
#endif
            return false;
        }
#ifdef DEBUG_OUTPUTS
        std::cout << "Children Before: " << m_children.size() << std::endl;
#endif

        removeChildrenAfterLoops();
#ifdef DEBUG_OUTPUTS
        std::cout << "Children After: " << m_children.size() << std::endl;
#endif

        return true;
    }
}
