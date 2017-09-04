#include "../include/PhysicsSprite2D.h"
#include "../include/LogManager.h"
#include "../include/MainClass.h"
#include "../include/Physics2D.h"
#include <iostream>

namespace Johnny
{
    PhysicsSprite2D::PhysicsSprite2D(b2Body* body) : Sprite2D(),
        m_body(body)
    {
        setName("PhysicsSprite2D");
    }
    PhysicsSprite2D::PhysicsSprite2D(const std::string& file,b2Body* body) : Sprite2D(file),
        m_body(body)
    {
        setName("PhysicsSprite2D");
    }
    PhysicsSprite2D::PhysicsSprite2D(Texture* tex,b2Body* body) : Sprite2D(tex),
        m_body(body)
    {
        setName("PhysicsSprite2D");
    }
    PhysicsSprite2D::~PhysicsSprite2D()
    {
        
    }
    
    bool PhysicsSprite2D::init()
    {
		if (!m_mainClass->getPhysics2D())
			LogManager::error("Couldn't initialise PhysicsSprite2D! You need to add PHYSICS_2D to the InitFlags!");

        if(!Sprite2D::init())
            return false;

        if(m_body)
        {
        	m_body->SetUserData(this);
            attachBodyToSprite();
        }
            
        return true;
    }
    bool PhysicsSprite2D::m_update()
    {
        if(!Sprite2D::m_update())
            return false;
        
        if(m_mainClass->getPhysics2D())
        {
			attachBodyToSprite();
        }
        
        if(m_automaticDestroy)
        {
            Vector2f worldSize = m_mainClass->getPhysics2D()->getWorldSize();			Rectangle<GLfloat> box = getBoundingBox();            if(box.x + box.width*2.0f < 0.0f || box.y + box.height*2.0f < 0.0f ||
               box.x-box.width > worldSize.x || box.y-box.height > worldSize.y)
            {
                getParent()->removeChild(this);
            }
        }
        
        
        return true;
    }
    void PhysicsSprite2D::m_quit()
    {
        Sprite2D::m_quit();
        if(m_mainClass->getPhysics2D())
			m_mainClass->getPhysics2D()->getWorld()->DestroyBody(m_body);
    }
    
	void PhysicsSprite2D::attachBodyToSprite()
	{
		setPosition(m_mainClass->getPhysics2D()->coordsWorldToPixel(m_body->GetPosition()) - (getDrawSize() / 2.0f) + m_offset);
		setRotation(toDegrees(m_body->GetAngle()));
	}
}
