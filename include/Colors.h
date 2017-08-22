#ifndef COLORS_H
#define COLORS_H
#include <SDL2/SDL_pixels.h>
#include "mathematics_functions.h"
#include <GL/glew.h>
#include <ostream>
#include "Vector4.h"

namespace Johnny
{
	template<class T,size_t maxValue>
	class Color : public Vector4<T>
	{
	public:
		Color();
		Color(const T&, const T&, const T&, const T&);
		Color(const T&, const T&, const T&);
		template<class T1,size_t maxValue1>
		Color(const Color<T1, maxValue1>&);

		Color<GLfloat, 1> normalise();

		template<class T1,size_t maxValue1>
		Color<T, maxValue>& operator=(const Color<T1, maxValue1>&);
	};

	template<class T, size_t maxValue>
	inline Color<T, maxValue>::Color() : Vector4<T>((T)0,(T)0,(T)0,(T)0)
	{
	}

	template<class T, size_t maxValue>
	inline Color<T, maxValue>::Color(const T& _r, const T& _g, const T& _b, const T& _a) : Vector4<T>(
		clamp(_r, (T)0, (T)maxValue),
		clamp(_g, (T)0, (T)maxValue),
        clamp(_b, (T)0, (T)maxValue),
		clamp(_a, (T)0, (T)maxValue))
	{
	}

	template<class T, size_t maxValue>
	inline Color<T, maxValue>::Color(const T& _r, const T& _g, const T& _b) : Color<T,maxValue>(_r,_g,_b,(T)maxValue)
	{
	}

	template<class T, size_t maxValue>
	inline Color<GLfloat, 1> Color<T, maxValue>::normalise()
	{
		return Color<GLfloat, 1>(*this);
	}

	template<class T, size_t maxValue>
	template<class T1, size_t maxValue1>
	inline Color<T, maxValue>::Color(const Color<T1, maxValue1>& color)
	{
		*this = color;
	}

	template<class T, size_t maxValue>
	template<class T1, size_t maxValue1>
	inline Color<T, maxValue>& Color<T, maxValue>::operator=(const Color<T1, maxValue1>& color)
	{
		this->r = (T)(((GLfloat)color.r / (GLfloat)maxValue1) * (GLfloat)maxValue);
		this->g = (T)(((GLfloat)color.g / (GLfloat)maxValue1) * (GLfloat)maxValue);
		this->b = (T)(((GLfloat)color.b / (GLfloat)maxValue1) * (GLfloat)maxValue);
		this->a = (T)(((GLfloat)color.a / (GLfloat)maxValue1) * (GLfloat)maxValue);

		return *this;
	}

	inline std::ostream& operator<<(std::ostream& os, const Color<GLubyte, 255>& color)
	{
		os << "(" << (GLuint)color.r << ";" << (GLuint)color.g << ";" << (GLuint)color.b << ";" << (GLuint)color.a << ")";
		return os;
	}

	typedef Color<GLfloat, 1> Colorf;
	typedef Color<GLubyte, 255> Colorb;

	namespace Colors
    {
        const Colorb RED = {255,0,0,255};
        const Colorb GREEN = {0,255,0,255};
        const Colorb BLUE = {0,0,255,255};
        const Colorb LIGHT_BLUE = {173,216,230,0};
        const Colorb WHITE = {255,255,255,255};
        const Colorb BLACK = {0,0,0,255};
        const Colorb GRAY = {128,128,128,255};
        const Colorb YELLOW = {255,255,0,255};
        const Colorb BROWN = {51,25,0,255};
        const Colorb PINK = {255,0,255,255};
    }
}

#endif
