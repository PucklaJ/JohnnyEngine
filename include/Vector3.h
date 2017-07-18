#pragma once

#include <GL/glew.h>

namespace Johnny
{
	template<class T>
	class Vector3
	{
	public:
		Vector3() = default;
		Vector3(const T&, const T&, const T&);
		Vector3(const Vector3&);

		union
		{
			T x = 0.0f;
			T r;
			T width;
		};

		union
		{
			T y = 0.0f;
			T g;
			T height;
		};

		union
		{
			T z = 0.0f;
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

		friend Vector3& operator+=(Vector3&, const Vector3&);
		friend Vector3& operator-=(Vector3&, const Vector3&);
		friend Vector3& operator*=(Vector3&, const Vector3&);
		friend Vector3& operator/=(Vector3&, const Vector3&);

		friend const Vector3 operator+(const Vector3&, const Vector3&);
		friend const Vector3 operator-(const Vector3&, const Vector3&);
		friend const Vector3 operator*(const Vector3&, const Vector3&);
		friend const Vector3 operator/(const Vector3&, const Vector3&);
	};

	typedef Vector3<GLfloat> Vector3f;
	typedef Vector3<GLdouble> Vector3d;
	typedef Vector3<GLint> Vector3i;
}

#include <cmath>

namespace Johnny
{
	template<class T>
	Vector3<T>::Vector3(const T& x, const T& y, const T& z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	template<class T>
	Vector3<T>::Vector3(const Vector3& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}
	template<class T>
	T Vector3<T>::length(bool squared) const
	{
		if (squared)
			return x*x + y*y + z*z;
		else
			return sqrt(x*x + y*y + z*z);
	}
	template<class T>
	Vector3<T>& Vector3<T>::normalise()
	{
		T Length = length();

		x /= Length;
		y /= Length;
		z /= Length;

		return *this;
	}
	template<class T>
	Vector3<T>& Vector3<T>::add(const Vector3<T>& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;

		return *this;
	}
	template<class T>
	Vector3<T>& Vector3<T>::subtract(const Vector3<T>& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;

		return *this;
	}
	template<class T>
	Vector3<T>& Vector3<T>::multiply(const Vector3<T>& v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;

		return *this;
	}
	template<class T>
	Vector3<T>& Vector3<T>::multiply(const T& s)
	{
		x *= s;
		y *= s;
		z *= s;

		return *this;
	}
	template<class T>
	Vector3<T>& Vector3<T>::divide(const Vector3<T>& v)
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;

		return *this;
	}
	template<class T>
	Vector3<T>& Vector3<T>::divide(const T& s)
	{
		x /= s;
		y /= s;
		z /= s;

		return *this;
	}
	template<class T>
	Vector3<T> Vector3<T>::cross(const Vector3<T>& v)
	{
		Vector3<T> v1(*this);

		v1.x = v1.y * v.z - v1.z * v.y;
		v1.y = v1.z * v.x - v1.x * v.z;
		v1.z = v1.x * v.y - v1.y * v.x;

		return v1;
	}
	template<class T>
	T Vector3<T>::distance(const Vector3<T>& v, bool squared) const
	{
		Vector3<T> v1(v);

		v1.subtract(*this);

		return v1.length(squared);
	}
	template<class T>
	Vector3<T>& operator+=(Vector3<T>& v1, const Vector3<T>& v2)
	{
		return v1.add(v2);
	}
	template<class T>
	Vector3<T>& operator-=(Vector3<T>& v1, const Vector3<T>& v2)
	{
		return v1.subtract(v2);
	}
	template<class T>
	Vector3<T>& operator*=(Vector3<T>& v1, const Vector3<T>& v2)
	{
		return v1.multiply(v2);
	}
	template<class T>
	Vector3<T>& operator/=(Vector3<T>& v1, const Vector3<T>& v2)
	{
		return v1.divide(v2);
	}
	template<class T>
	const Vector3<T> operator+(const Vector3<T>& v1, const Vector3<T>& v2)
	{
		return Vector3<T>(v1).add(v2);
	}
	template<class T>
	const Vector3<T> operator-(const Vector3<T>& v1, const Vector3<T>& v2)
	{
		return Vector3<T>(v1).subtract(v2);
	}
	template<class T>
	const Vector3<T> operator*(const Vector3<T>& v1, const Vector3<T>& v2)
	{
		return Vector3<T>(v1).multiply(v2);
	}
	template<class T>
	const Vector3<T> operator/(const Vector3<T>& v1, const Vector3<T>& v2)
	{
		return Vector3<T>(v1).divide(v2);
	}
}