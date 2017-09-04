#include "../include/Tween.h"
#include <iostream>
#include "../include/MainClass.h"
#include "../include/Sprite2D.h"
#include "../include/LogManager.h"
#include "../include/Texture.h"
#include "../include/ResourceManager.h"
#include "../include/Transform2D.h"

namespace Johnny
{
	std::vector<int> Tween2D::m_ids;

	Tween2D::Tween2D(float time) :
        m_time(time),
		m_parent(nullptr)
    {
    	do
    	{
    		m_id = rand();
    	}while(std::count(m_ids.begin(),m_ids.end(),m_id) != 0);

    	m_ids.push_back(m_id);
    }

	Tween2D::~Tween2D()
    {
        
    }

    void Tween2D::quit()
    {
    	for(size_t i = 0;i<m_ids.size();i++)
		{
			if(m_ids[i] == m_id)
			{
				m_ids[i] = m_ids.back();
				m_ids.pop_back();
				return;
			}
		}
    }

    void Tween2D::init()
    {

    }

    void Tween2D::setParent(TweenableObject2D* a)
    {
        m_parent = a;
    }
    
    void Tween2D::addTime(float time)
    {
        m_passedTime += time;
    }

    PositionTween2D::PositionTween2D(const Vector2f& v,float time) : Tween2D(time),
        m_dstPos(v)
    {

    }

    bool floatEqual(float d1,float d2)
    {
    	if(d1 == d2 || ((d2 + 0.0001f > d1) && (d2 - 0.0001f < d1)))
    		return true;
    	else
    		return false;
    }

    bool floatGreaterOrEqual(float d1,float d2)
    {
    	if(d1 > d2 || floatEqual(d1,d2))
    		return true;
    	return false;
    }

    bool floatSmallerOrEqual(float d1,float d2)
	{
		if(d1 < d2 || floatEqual(d1,d2))
			return true;
		return false;
	}

#define fgoe(d1,d2) floatGreaterOrEqual(d1,d2)
#define fsoe(d1,d2) floatSmallerOrEqual(d1,d2)

    bool PositionTween2D::update(float dt)
    {
       m_parent->addPosition(m_vel*dt);

        if(((m_vel.x < 0 && fsoe(m_parent->getPosition().x,m_dstPos.x)) ||
            (m_vel.x >= 0 && fgoe(m_parent->getPosition().x,m_dstPos.x)))&&
           ((m_vel.y < 0 && fsoe(m_parent->getPosition().y,m_dstPos.y))||
            (m_vel.y >= 0 && fgoe(m_parent->getPosition().y,m_dstPos.y))))
        {
            m_parent->setPosition(m_dstPos);
            return true;
        }

        return false;
    }

    void PositionTween2D::init()
    {
        m_vel.x = ((m_dstPos.x - m_parent->getPosition().x == 0.0f ? 0.0f : ((m_dstPos.x - m_parent->getPosition().x)/m_time)));
        m_vel.y = ((m_dstPos.y - m_parent->getPosition().y == 0.0f ? 0.0f : ((m_dstPos.y - m_parent->getPosition().y)/m_time)));

        if(abs(m_vel.x) < 0.0001f)
        {
        	m_vel.x = (0.0f);
        }
        if(abs(m_vel.y) < 0.0001f)
        {
        	m_vel.y = (0.0f);
        }

        if(m_vel.x == 0.0f)
        {
        	m_parent->setPosition(m_dstPos.x,m_parent->getPosition().y);
        }
        if(m_vel.y == 0.0f)
        {
        	m_parent->setPosition(m_parent->getPosition().x,m_dstPos.y);
        }
    }
    
    AnimationTween2D::AnimationTween2D(Texture* atlas,int x, int y,float time,bool loop,bool customTime) : Tween2D(time),
    	m_sprParent(nullptr),
		m_atlas(atlas),
        m_x(x),
        m_y(y),
        m_loop(loop),
        m_customTime(customTime)

    {
        
    }
    
    AnimationTween2D::AnimationTween2D(const std::vector<Texture*>& texs,float time,bool loop,bool customTime) : Tween2D(time),
    	m_sprParent(nullptr),
		m_x(0),
		m_y(0),
		m_loop(loop),
		m_customTime(customTime)
    {
        m_textures = new std::vector<Texture*>();
        
        for(size_t i = 0;i<texs.size();i++)
        {
            m_textures->push_back(texs[i]);
        }
        
    }
    
    AnimationTween2D::AnimationTween2D(const std::vector<TextureRegion>& regions,float time,bool loop,bool customTime) : Tween2D(time),
		m_sprParent(nullptr),
		m_x(0),
		m_y(0),
		m_loop(loop),
		m_customTime(customTime)
	{
		m_regions = new std::vector<TextureRegion>();

		for(size_t i = 0;i<regions.size();i++)
		{
			m_regions->push_back(regions[i]);
		}

	}

    AnimationTween2D::~AnimationTween2D()
    {
    	quit();

        if(m_textures)
        {
            for(size_t i = 0;i<m_textures->size();i++)
            {
                if(!MainClass::getInstance()->getResourceManager()->isLoaded((*m_textures)[i]))
                {
                    delete (*m_textures)[i];
                }
            }
            m_textures->clear();
            delete m_textures;
        }
        else if(m_regions)
        {
			m_regions->clear();
			delete m_regions;
        }

    }
    
    void AnimationTween2D::init()
    {
        m_sprParent = dynamic_cast<Sprite2D*>(m_parent);
        
        if(!m_sprParent)
        {
            LogManager::error("AnimationTween2D can only be given to a Sprite2D!");
            return;
        }
        
        if(m_atlas)
        {
            m_sprParent->setTexture(m_atlas);
            
            m_srcRegion.x = 0;
            m_srcRegion.y = 0;
            m_srcRegion.width = m_atlas->getWidth() / m_x;
            m_srcRegion.height = m_atlas->getHeight() / m_y;
            
            m_sprParent->setSrcRegion(m_srcRegion);
            m_sprParent->setDrawSize((GLfloat)m_srcRegion.width,(GLfloat)m_srcRegion.height);
        }
        else if(m_textures)
        {
            m_srcRegion.x = 0;
            if(m_textures->empty())
            {
                LogManager::error("Texture Array of AnimationTween2D is empty!");
            }
            else
                m_sprParent->setTexture((*m_textures)[0]);
        }
        else
        {
        	m_srcRegion.x = 0;
        	if(m_regions->empty())
        	{
        		LogManager::error("TextureRegion Array of AnimationTween2D is empty");
        	}
        	else
        	{
        		m_sprParent->setSrcRegion((*m_regions)[0]);
        		m_sprParent->setDrawSize((GLfloat)(*m_regions)[0].width,(GLfloat)(*m_regions)[0].height);
        	}

        }
    }
    
    bool AnimationTween2D::update(float dt)
    {
            if(!m_customTime)
                m_passedTime += dt;
            if(m_passedTime >= m_time)
            {
                if(m_atlas)
                {
                    m_srcRegion.x+=m_srcRegion.width;
                    
                    if(m_srcRegion.x == (m_srcRegion.width*m_x))
                    {
                        m_srcRegion.x = 0;
                        m_srcRegion.y+=m_srcRegion.height;
                        
                        if(m_srcRegion.y == (m_srcRegion.height*m_y))
                        {
                            if(!m_loop)
                                return true;
                            m_srcRegion.y = 0;
                        }
                    }
                    
                    m_sprParent->setSrcRegion(m_srcRegion);
                
                }
                else if(m_textures)
                {
                    if(++m_srcRegion.x == (int)m_textures->size())
                    {
                    	m_srcRegion.x = 0;

                        if(!m_loop)
                        {
                        	return true;
                        }
                    }
                    
                    m_sprParent->setTexture((*m_textures)[m_srcRegion.x]);
                }
                else
                {
                	if(++m_srcRegion.x == (int)m_regions->size())
                	{
                		m_srcRegion.x = 0;

                		if(!m_loop)
                		{
                			return true;
                		}
                	}

                	m_sprParent->setSrcRegion((*m_regions)[m_srcRegion.x]);
                	m_sprParent->setDrawSize((GLfloat)(*m_regions)[m_srcRegion.x].width,(GLfloat)(*m_regions)[m_srcRegion.x].height);
                }
                
                m_passedTime = 0.0;
                
            }
            
            return false;
    }
    
    PulsateTween2D::PulsateTween2D(float length,float speed,bool loop) : Tween2D(0.0),
        m_loop(loop),
        m_length(length),
        m_speed(speed)
    {
        
    }
    
    void PulsateTween2D::init()
    {
        m_startPos = m_parent->getPosition();
        m_startScale = m_parent->getScale();
    }
    
    bool PulsateTween2D::update(float dt)
    {
        m_time += dt * m_speed;
        if(m_time >= 2.0f*(float)M_PI)
        {
            if(!m_loop)
            {
                m_parent->setPosition(m_startPos);
                m_parent->setScale(m_startScale);
                return true;
            }
            m_time = 0.0;
        }
        
        Vector2f normScale = m_startScale;
        normScale.normalise();
        Vector2f normPos = m_parent->getPosition();
        normPos.normalise();
        
        m_parent->setScale(m_startScale + (normScale*sin(m_time)*m_length));
        m_parent->setPosition(m_startPos - (normPos*sin(m_time)*m_length));
        
        return false;
    }
    
    BlinkTween2D::BlinkTween2D(float time) : Tween2D(time)
    {
        
    }
    
    BlinkTween2D::~BlinkTween2D()
    {
        
    }
    
    void BlinkTween2D::init()
    {
        Tween2D::init();
        m_sprParent = static_cast<Sprite2D*>(m_parent);
    }
    
    bool BlinkTween2D::update(float dt)
    {
        m_passedTime += dt;
        
        if(m_passedTime >= m_time)
        {
            m_sprParent->setVisible(!m_sprParent->isVisible());
            m_passedTime = 0.0f;
        }
        
        return false;
    }
    
    void BlinkTween2D::quit()
    {
        m_sprParent->setVisible(true);
        Tween2D::quit();
    }
    
    RotationTween2D::RotationTween2D(float speed) : Tween2D(0.0f),
        m_speed(speed)
    {
        
    }
    
    RotationTween2D::~RotationTween2D()
    {
        
    }
    
    void RotationTween2D::init()
    {
        
    }
    
    bool RotationTween2D::update(float dt)
    {
        m_parent->addRotation(m_speed * dt);
        return false;
    }

	TweenableObject2D::TweenableObject2D()
	{
	}

	TweenableObject2D::~TweenableObject2D()
	{
	}

	Tween2D* TweenableObject2D::getTween(int id)
	{
		for (size_t i = 0; i<m_tweens.size(); i++)
		{
			if (m_tweens[i]->getID() == id)
				return m_tweens[i];
		}

		return nullptr;
	}

	int TweenableObject2D::addTween(Tween2D* t)
	{
		m_tweens.push_back(t);
		t->setParent(this);
		t->init();

		return t->getID();
	}

	void TweenableObject2D::clearTweens()
	{
		for (size_t i = 0; i<m_tweens.size(); i++)
		{
			delete m_tweens[i];
		}

		m_tweens.clear();
	}

	void TweenableObject2D::pauseTween(int id)
	{
		for (size_t i = 0; i<m_tweens.size(); i++)
		{
			if (m_tweens[i]->getID() == id)
			{
				m_tweens[i]->setPaused(true);
				break;
			}
		}
	}

	void TweenableObject2D::resumeTween(int id)
	{
		for (size_t i = 0; i<m_tweens.size(); i++)
		{
			if (m_tweens[i]->getID() == id)
			{
				m_tweens[i]->setPaused(false);
				break;
			}
		}
	}

	void TweenableObject2D::stopTween(int id)
	{
		for (size_t i = 0; i<m_tweens.size(); i++)
		{
			if (m_tweens[i]->getID() == id)
			{
                m_tweens[i]->quit();
				delete m_tweens[i];
				m_tweens[i] = m_tweens.back();
				m_tweens.pop_back();
				break;
			}
		}
	}

	void TweenableObject2D::updateTweens(float dt)
	{
		for (size_t i = 0; i<m_tweens.size(); i++)
		{
			if (m_tweens[i]->isPaused())
				continue;

			if (m_tweens[i]->update(dt))
			{
                m_tweens[i]->quit();
				delete m_tweens[i];
				m_tweens[i] = m_tweens.back();
				m_tweens.pop_back();
				i--;
			}
		}
	}
    
    bool TweenableObject2D::isRunning(int id)
    {
        for(size_t i = 0;i<m_tweens.size();i++)
        {
            if(m_tweens[i]->getID() == id)
                return true;
        }
        
        return false;
    }

}

