#pragma once
#include "Vector2.h"
#include <ostream>

namespace Johnny
{
	template<class T> class Rectangle;
	template<class T> std::ostream& operator<<(std::ostream&, const Rectangle<T>&);

	/* \brief A class which represents a rectangle
	 * \param T The type of the x,y,width,height values
	 */
	template<class T>
	class Rectangle
	{
	public:
		/* \brief Creates a new rectangle
		 *        with x=0,y=0,width=0,height=0
		 *
		 */
		Rectangle();
		/* \brief Creates a new rectangle
		 * \param x The x value of the new rectangle
		 * \param y The y value of the new rectangle
		 * \param width The width value of the new rectangle
		 * \param height The height value of the new rectangle
		 */
		Rectangle(const T& x, const T& y, const T& width, const T& height);
		/* \brief Creates a new rectangle
		 * \param pos The position of the new rectangle x=pos.x,y=pos.y
		 * \param size The size of the new rectangle width=size.width,height=size.height
		 */
		Rectangle(const Vector2<T>& pos,const Vector2<T>& size);
		~Rectangle();

		/* \return The area of the rectangle
		 *
		 */
		T area();

		T x = 0; //!< The x coordinate of the position of the rectangle
		T y = 0; //!< The y coordinate of the position of the rectangle
        union
        {
            T width = 0; //!< The width of the rectangle
            T w;
        };
		
        union
        {
            T height = 0; //!< The height of the rectangle
            T h;
        };		


		friend std::ostream& operator<< <>(std::ostream&, const Rectangle<T>&);
	};

	/* \brief Defines a rectangle on a texture
	 *
	 */
	typedef Rectangle<GLint> TextureRegion;
}

#include "../src/Geometry.cpp"