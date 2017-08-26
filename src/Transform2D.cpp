#include "../include/Transform2D.h"
#include "../include/Camera2D.h"
#include "../include/MainClass.h"
#include "../include/Sprite2D.h"
#include <iostream>

namespace Johnny
{
	Transform2D::Transform2D() :
		m_translation(0.0f, 0.0f),
		m_rotation(0.0f),
		m_scale(1.0f, 1.0f)
	{

	}

	Transform2D::Transform2D(const Vector2f& translation, const GLfloat& rotation, const Vector2f& scale) :
		m_translation(translation),
		m_rotation(rotation),
		m_scale(scale)
	{
		
	}

	Transform2D::~Transform2D()
	{

	}

	Matrix3f Transform2D::getTransformation() const
	{
		return Matrix3f::translate(m_translation) * Matrix3f::rotate(m_rotation) * Matrix3f::scale(m_scale);
	}

	Matrix3f Transform2D::getProjectedTransformation(const Camera2D* cam) const
	{
		return cam->getViewMatrix() * getTransformation();
	}

	Vector2f TransformableObject2D::center;
	bool TransformableObject2D::yAxisFlipped = true;
	bool TransformableObject2D::xAxisFlipped = false;
	Vector2f TransformableObject2D::viewportSize;
	std::vector<TransformableObject2D*> TransformableObject2D::objects;
    bool TransformableObject2D::centerSet = false;

	const Vector2f& TransformableObject2D::getCenter()
	{
		return center;
	}

	bool TransformableObject2D::getYAxisFlipped()
	{
		return yAxisFlipped;
	}

	bool TransformableObject2D::getXAxisFlipped()
	{
		return xAxisFlipped;
	}

	const Vector2f& TransformableObject2D::getViewportSize()
	{
		return viewportSize;
	}

	void TransformableObject2D::setCenter(const Vector2f& v)
	{
        Vector2f prevCenter;
        if(centerSet)
        {
            prevCenter = getCenter() * getViewportSize();
        }
            
		center = v;
        if(centerSet)
        {
            
            
            for (size_t i = 0; i < objects.size(); i++)
            {
                if (!objects[i]->m_affectedByCenter)
                    continue;

                objects[i]->m_transform.setTranslation(fromCoords(objects[i]->m_transform.getTranslation() - objects[i]->m_size / 2.0f * objects[i]->m_transform.getScale() - prevCenter));
                objects[i]->setPosition(objects[i]->m_transform.getTranslation());
            }
        }
        
        centerSet = true;
	}

	void TransformableObject2D::setYAxisFlipped(bool b)
	{
		bool prevY = yAxisFlipped;
		yAxisFlipped = b;
        
        Vector2f _center = getCenter() * getViewportSize();
        
		for (size_t i = 0; i < objects.size(); i++)
		{
			if (!objects[i]->m_affectedByCenter)
				continue;

			objects[i]->m_transform.setTranslation(fromCoords(objects[i]->m_transform.getTranslation() - objects[i]->m_size / 2.0f * objects[i]->m_transform.getScale() - _center,xAxisFlipped,prevY));
			objects[i]->setPosition(objects[i]->m_transform.getTranslation());
		}
	}

	void TransformableObject2D::setXAxisFlipped(bool b)
	{
		bool prevX = xAxisFlipped;
		xAxisFlipped = b;
        
        Vector2f _center = getCenter() * getViewportSize();
        
		for (size_t i = 0; i < objects.size(); i++)
		{
			if (!objects[i]->m_affectedByCenter)
				continue;

			objects[i]->m_transform.setTranslation(fromCoords(objects[i]->m_transform.getTranslation() - objects[i]->m_size / 2.0f * objects[i]->m_transform.getScale() - _center, prevX, yAxisFlipped));
			objects[i]->setPosition(objects[i]->m_transform.getTranslation());
		}
	}

	void TransformableObject2D::setViewportSize(const Vector2f& v)
	{
		Vector2f prevViewport = viewportSize;
		viewportSize = v;
        
        Vector2f _center = getCenter() * prevViewport;
        
		for (size_t i = 0; i < objects.size(); i++)
		{
			if (!objects[i]->m_affectedByCenter)
				continue;

			objects[i]->m_transform.setTranslation(fromCoords(objects[i]->m_transform.getTranslation() - Vector2f(objects[i]->m_size.x / 2.0f,-objects[i]->m_size.y / 2.0f) * objects[i]->m_transform.getScale() - _center,prevViewport));
			objects[i]->setPosition(objects[i]->m_transform.getTranslation());
		}
	}

	TransformableObject2D::TransformableObject2D()
	{
		objects.push_back(this);
	}

	TransformableObject2D::~TransformableObject2D()
	{

		if (objects.size() == 1)
			objects.clear();
		else
		{

			for (size_t i = 0; i < objects.size(); i++)
			{

				if (objects[i] == this)
				{
					objects[i] = objects.back();
					objects.pop_back();
					break;
				}
			}
		}
	}

	void TransformableObject2D::setPosition(const Vector2f& pos)
	{
		if (m_size.x == 0.0f && m_size.y == 0.0f)
		{
			m_transform.setTranslation(pos);
		}
		else
		{
            Vector2f _size = Vector2f(m_size.x / 2.0f,-m_size.y/2.0f);
            Vector2f _center;
            
            if(m_affectedByCenter)
            {
                _center = getCenter() * getViewportSize();
            }
            
			m_transform.setTranslation(fromCoords(pos) + _size * m_transform.getScale() + _center);
		}
			
	}

	void TransformableObject2D::setPosition(const GLfloat& x, const GLfloat& y)
	{
		setPosition(Vector2f(x, y));
	}

	void TransformableObject2D::setRotation(const GLfloat& rotation)
	{
		m_transform.setRotation(rotation);
	}

	void TransformableObject2D::setScale(const Vector2f& v)
	{
		if (m_size.x == 0.0f && m_size.y == 0.0f)
			m_transform.setScale(v);
		else
		{
            Vector2f _center = getCenter() * getViewportSize();
            
			m_transform.setTranslation(toCoords(m_transform.getTranslation() - Vector2f(m_size.x / 2.0f,-m_size.y/2.0f) * m_transform.getScale() - (m_affectedByCenter ? _center : Vector2f(0.0f, 0.0f))));
			m_transform.setScale(v);
			setPosition(m_transform.getTranslation());
		}
		
	}

	void TransformableObject2D::setScale(const GLfloat& x, const GLfloat& y)
	{
		setScale(Vector2f(x, y));
	}

	void TransformableObject2D::setSize(const Vector2f& v)
	{
		if (m_size.x == 0.0f && m_size.y == 0.0f)
		{
			m_size = v;
		}
		else
		{
            Vector2f _center = getCenter() * getViewportSize();
            
			m_transform.setTranslation(toCoords(m_transform.getTranslation() - Vector2f(m_size.x / 2.0f, -m_size.y / 2.0f) * m_transform.getScale() - (m_affectedByCenter ? _center : Vector2f(0.0f, 0.0f))));
			m_size = v;
		}
		
		setPosition(m_transform.getTranslation());
	}

	void TransformableObject2D::addPosition(const Vector2f& pos)
	{
		m_transform.setTranslation(m_transform.getTranslation() + pos);
	}

	void TransformableObject2D::addPosition(const GLfloat& x, const GLfloat& y)
	{
		m_transform.setTranslation(m_transform.getTranslation() + Vector2f(x, y));
	}

	void TransformableObject2D::addScale(const Vector2f& v)
	{
		m_transform.setScale(m_transform.getScale() + v);
	}

	void TransformableObject2D::addScale(const GLfloat& x, const GLfloat& y)
	{
		m_transform.setScale(m_transform.getScale() + Vector2f(x, y));
	}

	Vector2f TransformableObject2D::getPosition() const
	{
        Vector2f _center = getCenter() * getViewportSize();
        
		return toCoords(m_transform.getTranslation() - Vector2f(m_size.x / 2.0f, -m_size.y / 2.0f) * m_transform.getScale() - (m_affectedByCenter ? _center : Vector2f(0.0f, 0.0f)));
	}

#define IS_VIEW (viewport.x != -1.0f && viewport.y != -1.0f)
#define GET_VIEW (IS_VIEW ? viewport : viewportSize)

	Vector2f TransformableObject2D::toCoords(const Vector2f& v,const Vector2f& viewport)
	{
		return Vector2f(xAxisFlipped ? (GET_VIEW.x - v.x) : v.x, yAxisFlipped ? (GET_VIEW.y - v.y) : v.y);
	}
	Vector2f TransformableObject2D::toCoords(const Vector2f& v, bool x, bool y)
	{
		return Vector2f(x ? (viewportSize.x - v.x) : v.x, y ? (viewportSize.y - v.y) : v.y);
	}
	Vector2f TransformableObject2D::fromCoords(const Vector2f& v,const Vector2f& viewport)
	{
		return Vector2f(xAxisFlipped ? (GET_VIEW.x - v.x) : v.x, yAxisFlipped ? (GET_VIEW.y - v.y) : v.y);
	}
	Vector2f TransformableObject2D::fromCoords(const Vector2f& v, bool x, bool y)
	{
		return Vector2f(x ? (viewportSize.x - v.x) : v.x, y ? (viewportSize.y - v.y) : v.y);
	}
}
