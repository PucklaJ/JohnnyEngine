#pragma once
#include <GL/glew.h>
#include <iostream>

namespace Johnny
{
	template<class T> class Vector4;
	template<class T> const Vector4<T> operator+(const Vector4<T>&, const Vector4<T>&);
	template<class T> const Vector4<T> operator-(const Vector4<T>&, const Vector4<T>&);
	template<class T> const Vector4<T> operator*(const Vector4<T>&, const Vector4<T>&);
	template<class T> const Vector4<T> operator/(const Vector4<T>&, const Vector4<T>&);

	template<class T> std::ostream& operator<<(std::ostream&, const Vector4<T>&);

	template<class T>
	class Vector4
	{
	public:
		Vector4() = default;
		Vector4(const T&, const T&, const T&, const T&);
		Vector4(const Vector4&);

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

		union
		{
			T z = 0;
			T b;
			T depth;
		};

		union
		{
			T w = 0;
			T a;
			T time;
		};

		T length(bool squared = false) const;
		Vector4& normalise();

		Vector4& add(const Vector4&);
		Vector4& subtract(const Vector4&);
		Vector4& multiply(const Vector4&);
		Vector4& multiply(const T&);
		Vector4& divide(const Vector4&);
		Vector4& divide(const T&);

		T distance(const Vector4&, bool squared = false) const;

		Vector4& operator+=(const Vector4&);
		Vector4& operator-=(const Vector4&);
		Vector4& operator*=(const Vector4&);
		Vector4& operator/=(const Vector4&);

		friend const Vector4<T> operator+<>(const Vector4<T>&, const Vector4<T>&);
		friend const Vector4<T> operator-<>(const Vector4<T>&, const Vector4<T>&);
		friend const Vector4<T> operator*<>(const Vector4<T>&, const Vector4<T>&);
		friend const Vector4<T> operator/<>(const Vector4<T>&, const Vector4<T>&);

		friend std::ostream& operator<< <>(std::ostream&, const Vector4<T>&);
	};

	typedef Vector4<GLfloat> Vector4f;
	typedef Vector4<GLdouble> Vector4d;
	typedef Vector4<GLint> Vector4i;
}

#include "../src/Vector4.cpp"