#ifndef GEOMETRY_CPP
#define GEOMETRY_CPP
#include "../include/Geometry.h"

namespace Johnny
{
	template<class T>
	Rectangle<T>::Rectangle() : Rectangle<T>(0,0,0,0)
	{

	}

	template<class T>
	Rectangle<T>::Rectangle(const T& _x, const T& _y, const T& _width, const T& _height) : 
		x(_x),
		y(_y),
		width(_width),
		height(_height)
	{
		
	}

	template<class T>
	Rectangle<T>::Rectangle(const Vector2<T>& pos, const Vector2<T>& _size) :
		x(pos.x),
        y(pos.y),
		width(_size.x),
        height(_size.y)
	{
	}

	template<class T>
	Rectangle<T>::~Rectangle()
	{

	}

	template<class T>
	T Rectangle<T>::area()
	{
		return width*height;
	}
    
    template<class T>
    bool Rectangle<T>::intersects(const Rectangle<T>& rect) const
    {
        return rect.x < x + width &&
               rect.x + rect.width > x &&
               rect.y < y + height &&
               rect.y + rect.height > y;
    }

	template<class T>
	std::ostream& operator<<(std::ostream& os, const Rectangle<T>& r)
	{
		os << "(" << r.x << ";" << r.y << ";" << r.width << ";" << r.height << ")";
		return os;
	}
}

#endif