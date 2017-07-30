#ifndef VECTOR3_CPP
#define VECTOR3_CPP
#include "../include/Vector3.h"
#include <cmath>
#include "../include/Vector3.h"

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
	Vector3<T>::Vector3(const Vector4<T>& v)
	{
		x = v.x/v.w;
		y = v.y/v.w;
		z = v.z/v.w;
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

		v1.x = y * v.z - z * v.y;
		v1.y = z * v.x - x * v.z;
		v1.z = x * v.y - y * v.x;

		return v1;
	}
	template<class T>
	T Vector3<T>::dot(const Vector3<T>& v)
	{
		return x*v.x+y*v.y+z*v.z;
	}

	template<class T>
	T Vector3<T>::distance(const Vector3<T>& v, bool squared) const
	{
		Vector3<T> v1(v);

		v1.subtract(*this);

		return v1.length(squared);
	}
	template<class T>
	Vector3<T>& Vector3<T>::operator+=(const Vector3<T>& v2)
	{
		return add(v2);
	}
	template<class T>
	Vector3<T>& Vector3<T>::operator-=(const Vector3<T>& v2)
	{
		return subtract(v2);
	}
	template<class T>
	Vector3<T>& Vector3<T>::operator*=(const Vector3<T>& v2)
	{
		return multiply(v2);
	}
	template<class T>
	Vector3<T>& Vector3<T>::operator*=(const T& s)
	{
		return multiply(s);
	}
	template<class T>
	Vector3<T>& Vector3<T>::operator/=(const Vector3<T>& v2)
	{
		return divide(v2);
	}
	template<class T>
	Vector3<T> operator+(const Vector3<T>& v1, const Vector3<T>& v2)
	{
		return Vector3<T>(v1).add(v2);
	}
	template<class T>
	Vector3<T> operator-(const Vector3<T>& v1, const Vector3<T>& v2)
	{
		return Vector3<T>(v1).subtract(v2);
	}
	template<class T>
	Vector3<T> operator*(const Vector3<T>& v1, const Vector3<T>& v2)
	{
		return Vector3<T>(v1).multiply(v2);
	}
	template<class T>
	Vector3<T> operator*(const Vector3<T>& v, const T& s)
	{
		return Vector3<T>(v).multiply(s);
	}

	template<class T>
	Vector3<T> operator/(const Vector3<T>& v1, const Vector3<T>& v2)
	{
		return Vector3<T>(v1).divide(v2);
	}
	template<class T>
	Vector3<T> operator-(const Vector3<T>& v)
	{
		Vector3<T> v1(v);
		return v1.multiply((T)-1);
	}
	template<class T>
	std::ostream& operator<<(std::ostream& os, const Vector3<T>& v)
	{
		os << "(" << v.x << ";" << v.y << ";" << v.z << ")";
		return os;
	}
	template<class T>
	Vector3<T>& Vector3<T>::operator=(const Vector4<T>& v2)
	{
		*this = Vector3<T>(v2);
		return *this;
	}
	template<class T>
	T& Vector3<T>::operator[](unsigned int i)
	{
		switch(i)
		{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		default:
			throw "operator[] unsigned int must be 0,1,2";
			break;
		}
	}
}

#endif
