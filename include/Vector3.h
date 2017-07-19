#pragma once
#include <GL/glew.h>
#include <iostream>

namespace Johnny
{
	template<class T> class Vector3;
	template<class T> const Vector3<T> operator+(const Vector3<T>&, const Vector3<T>&);
	template<class T> const Vector3<T> operator-(const Vector3<T>&, const Vector3<T>&);
	template<class T> const Vector3<T> operator*(const Vector3<T>&, const Vector3<T>&);
	template<class T> const Vector3<T> operator/(const Vector3<T>&, const Vector3<T>&);

	template<class T> std::ostream& operator<<(std::ostream&, const Vector3<T>&);

	template<class T>
	class Vector3
	{
	public:
		Vector3() = default;
		Vector3(const T&, const T&, const T&);
		Vector3(const Vector3&);

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

		T length(bool squared = false) const;
		Vector3& normalise();

		Vector3& add(const Vector3&);
		Vector3& subtract(const Vector3&);
		Vector3& multiply(const Vector3&);
		Vector3& multiply(const T&);
		Vector3& divide(const Vector3&);
		Vector3& divide(const T&);

		Vector3 cross(const Vector3&);
		T distance(const Vector3&, bool squared = false) const;

		Vector3& operator+=(const Vector3&);
		Vector3& operator-=(const Vector3&);
		Vector3& operator*=(const Vector3&);
		Vector3& operator/=(const Vector3&);

		friend const Vector3<T> operator+<>(const Vector3<T>&, const Vector3<T>&);
		friend const Vector3<T> operator-<>(const Vector3<T>&, const Vector3<T>&);
		friend const Vector3<T> operator*<>(const Vector3<T>&, const Vector3<T>&);
		friend const Vector3<T> operator/<>(const Vector3<T>&, const Vector3<T>&);

		friend std::ostream& operator<< <>(std::ostream&, const Vector3<T>&);
	};

	typedef Vector3<GLfloat> Vector3f;
	typedef Vector3<GLdouble> Vector3d;
	typedef Vector3<GLint> Vector3i;
}

#include "../src/Vector3.cpp"