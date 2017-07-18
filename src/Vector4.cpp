#include "../include/Vector4.h"
/*#include <cmath>

namespace Johnny
{
	template<class T>
	Vector4<T>::Vector4(const T& x, const T& y, const T& z, const T& w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	template<class T>
	Vector4<T>::Vector4(const Vector4<T>& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
	}

	template<class T>
	T Vector4<T>::length(bool squared) const
	{
		if (squared)
			return x*x + y*y + z*z + w*w;
		else
			return sqrt(x*x + y*y + z*z + w*w);
	}

	template<class T>
	Vector4<T>& Vector4<T>::normalise()
	{
		T Length = length();

		x /= Length;
		y /= Length;
		z /= Length;
		w /= Length;

		return *this;
	}

	template<class T>
	Vector4<T>& Vector4<T>::add(const Vector4<T>& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;

		return *this;
	}

	template<class T>
	Vector4<T>& Vector4<T>::subtract(const Vector4<T>& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;

		return *this;
	}

	template<class T>
	Vector4<T>& Vector4<T>::multiply(const Vector4<T>& v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		w *= v.w;

		return *this;
	}

	template<class T>
	Vector4<T>& Vector4<T>::multiply(const T& s)
	{
		x *= s;
		y *= s;
		z *= s;
		w *= s;

		return *this;
	}

	template<class T>
	Vector4<T>& Vector4<T>::divide(const Vector4& v)
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;
		w /= v.w;

		return *this;
	}

	template<class T>
	Vector4<T>& Vector4<T>::divide(const T& s)
	{
		x /= s;
		y /= s;
		z /= s;
		w /= s;

		return *this;
	}

	template<class T>
	T Vector4<T>::distance(const Vector4<T>& v, bool squared) const
	{
		Vector4 v1(v);

		v1.subtract(*this);

		return v1.length(squared);
	}

	template<class T>
	Vector4<T>& operator+=(Vector4<T>& v1, const Vector4<T>& v2)
	{
		return v1.add(v2);
	}

	template<class T>
	Vector4<T>& operator-=(Vector4<T>& v1, const Vector4<T>& v2)
	{
		return v1.subtract(v2);
	}

	template<class T>
	Vector4<T>& operator*=(Vector4<T>& v1, const Vector4<T>& v2)
	{
		return v1.multiply(v2);
	}

	template<class T>
	Vector4<T>& operator/=(Vector4<T>& v1, const Vector4<T>& v2)
	{
		return v1.divide(v2);
	}

	template<class T>
	const Vector4<T> operator+(const Vector4<T>& v1, const Vector4<T>& v2)
	{
		return Vector4(v1).add(v2);
	}

	template<class T>
	const Vector4<T> operator-(const Vector4<T>& v1, const Vector4<T>& v2)
	{
		return Vector4(v1).subtract(v2);
	}

	template<class T>
	const Vector4<T> operator*(const Vector4<T>& v1, const Vector4<T>& v2)
	{
		return Vector4(v1).multiply(v2);
	}

	template<class T>
	const Vector4<T> operator/(const Vector4<T>& v1, const Vector4<T>& v2)
	{
		return Vector4(v1).divide(v2);
	}
}*/