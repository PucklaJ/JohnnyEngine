#pragma once
#include "Vector2.h"
#include <ostream>

namespace Johnny
{
	template<class T> class Rectangle;
	template<class T> std::ostream& operator<<(std::ostream&, const Rectangle<T>&);

	template<class T>
	class Rectangle
	{
	public:
		Rectangle();
		Rectangle(const T&, const T&, const T&, const T&);
		Rectangle(const Vector2<T>&,const Vector2<T>&);
		~Rectangle();

		T area();

		T x = 0;
		T y = 0;
        union
        {
            T width = 0;
            T w;
        };
		
        union
        {
            T height = 0;
            T h;
        };		


		friend std::ostream& operator<< <>(std::ostream&, const Rectangle<T>&);
	};

	typedef Rectangle<GLint> TextureRegion;
}

#include "../src/Geometry.cpp"