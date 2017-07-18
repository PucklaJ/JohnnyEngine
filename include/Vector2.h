#pragma once
#include <GL/glew.h>
#include <iostream>

namespace Johnny
{
	template<class T> class Vector2;
	template<class T> const Vector2<T> operator+(const Vector2<T>&, const Vector2<T>&);
	template<class T> const Vector2<T> operator-(const Vector2<T>&, const Vector2<T>&);
	template<class T> const Vector2<T> operator*(const Vector2<T>&, const Vector2<T>&);
	template<class T> const Vector2<T> operator/(const Vector2<T>&, const Vector2<T>&);
	template<class T> std::ostream& operator<<(std::ostream&, const Vector2<T>&);

	template<class T>
	class Vector2
	{
	public:
		Vector2() = default;
		Vector2(const T&,const T&);
		Vector2(const Vector2&);

		union
		{
			T x = 0;
			T r;
			T width;
		};

		union
		{
			T y = 0;
			T g;
			T height;
		};

		T length(bool squared = false) const;
		Vector2& normalise();

		Vector2& add(const Vector2&);
		Vector2& subtract(const Vector2&);
		Vector2& multiply(const Vector2&);
		Vector2& multiply(const T&);
		Vector2& divide(const Vector2&);
		Vector2& divide(const T&);

		T dot(const Vector2&) const;
		T distance(const Vector2&,bool squared = false) const;

		Vector2& operator+=(const Vector2&);
		Vector2& operator-=(const Vector2&);
		Vector2& operator*=(const Vector2&);
		Vector2& operator/=(const Vector2&);

		friend const Vector2<T> operator+<>(const Vector2<T>&, const Vector2<T>&);
		friend const Vector2<T> operator-<>(const Vector2<T>&, const Vector2<T>&);
		friend const Vector2<T> operator*<>(const Vector2<T>&, const Vector2<T>&);
		friend const Vector2<T> operator/<>(const Vector2<T>&, const Vector2<T>&);

		friend std::ostream& operator<< <>(std::ostream&, const Vector2<T>&);
	};

	typedef Vector2<GLfloat> Vector2f;
	typedef Vector2<GLdouble> Vector2d;
	typedef Vector2<GLint> Vector2i;
}

#include "../src/Vector2.cpp"