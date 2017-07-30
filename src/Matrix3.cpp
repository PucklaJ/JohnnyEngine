#ifndef MATRIX3_CPP
#define MATRIX3_CPP
#include "../include/Matrix3.h"
#include "../include/Matrix4.h"
#include <string>
#include "../include/mathematics_functions.h"
#include <GL/glew.h>

namespace Johnny
{
	template<class T>
	Matrix3<T> Matrix3<T>::identity()
	{
		return Matrix3(1);
	}

	template<class T>
	Matrix3<T> Matrix3<T>::translate(const T& x, const T& y)
	{
		Matrix3<T> mat(1);

		mat.values[MAT3_GET(0, 2)] = x;
		mat.values[MAT3_GET(1, 2)] = y;

		return mat;
	}

	template<class T>
	Matrix3<T> Matrix3<T>::translate(const Vector2<T>& v)
	{
		return translate(v.x, v.y);
	}

	template<class T>
	Matrix3<T> Matrix3<T>::rotate(const T& angle)
	{
		Matrix3<T> mat(1);
		T sina = (T)sin((double)toRadians(angle));
		T cosa = (T)cos((double)toRadians(angle));

		mat.values[MAT3_GET(0, 0)] = cosa;
		mat.values[MAT3_GET(1, 1)] = cosa;
		mat.values[MAT3_GET(1, 0)] = sina;
		mat.values[MAT3_GET(0, 1)] = -sina;

		return mat;
	}

	template<class T>
	Matrix3<T> Matrix3<T>::scale(const T& x, const T& y)
	{
		Matrix3<T> mat(1);

		mat.values[MAT3_GET(0, 0)] = x;
		mat.values[MAT3_GET(1, 1)] = y;

		return mat;
	}

	template<class T>
	Matrix3<T> Matrix3<T>::scale(const Vector2<T>& v)
	{
		return scale(v.x, v.y);
	}

	template<class T>
	Matrix3<T> Matrix3<T>::camera(const Vector2<T>& position, const T& zoom, const T& rotation)
	{		
		return   rotate(rotation) * scale(zoom, zoom) * translate(position*(T)-1);
	}

	template<class T>
	Matrix3<T> Matrix3<T>::lookAt(const Vector3<T>& position, const Vector3<T>& middle, const Vector3<T>& up)
	{
		// Src: https://github.com/TheCherno/Sparky/blob/master/Sparky-core/src/sp/maths/mat4.cpp

		Matrix3<T> result(1);
		Vector3<T> f = (middle - position);
		f.normalise();
		Vector3<T> up1 = up;
		up1.normalise();
		Vector3<T> s = f.cross(up);
		Vector3<T> u = s.cross(f);

		result.values[0 + 0 * 3] = s.x;
		result.values[0 + 1 * 3] = s.y;
		result.values[0 + 2 * 3] = s.z;

		result.values[1 + 0 * 3] = u.x;
		result.values[1 + 1 * 3] = u.y;
		result.values[1 + 2 * 3] = u.z;

		result.values[2 + 0 * 3] = -f.x;
		result.values[2 + 1 * 3] = -f.y;
		result.values[2 + 2 * 3] = -f.z;

		return result * translate(-position.x, -position.y);
	}

	template<class T>
	Matrix3<T>::Matrix3(const T& v)
	{
		for (unsigned int i = 0; i < 9; i++)
		{
			values[i] = 0;
		}

		values[MAT3_GET(0, 0)] = v;
		values[MAT3_GET(1, 1)] = v;
		values[MAT3_GET(2, 2)] = v;
	}

	template<class T>
	Matrix3<T>::Matrix3(const Matrix3<T>& mat)
	{
		for (unsigned int i = 0; i < 9; i++)
			values[i] = mat.values[i];
	}

	template<class T>
	Matrix3<T>& Matrix3<T>::multiply(const Matrix3<T>& mat)
	{
		T sum[3];

		for (unsigned int r = 0; r < 3; r++)
		{
			for (unsigned int c = 0; c < 3; c++)
			{
				sum[c] = 0;
				for (unsigned int i = 0; i < 3; i++)
				{
					sum[c] += values[MAT3_GET(r, i)] * mat.values[MAT3_GET(i, c)];
				}
			}

			for (unsigned int i = 0; i < 3; i++)
			{
				values[MAT3_GET(r, i)] = sum[i];
			}
		}

		return *this;
	}

	template<class T>
	Matrix3<T> & Matrix3<T>::multiply(const T& v)
	{
		for (unsigned int i = 0; i < 9; i++)
		{
			values[i] *= v;
		}
	}

	template<class T>
	Vector3<T> Matrix3<T>::multiply(const Vector3<T>& v) const
	{
		Vector3<T> v1(v);

		v1.x = values[MAT3_GET(0, 0)] * v.x + values[MAT3_GET(0, 1)] * v.y + values[MAT3_GET(0, 2)] * v.z;
		v1.y = values[MAT3_GET(1, 0)] * v.x + values[MAT3_GET(1, 1)] * v.y + values[MAT3_GET(1, 2)] * v.z;
		v1.z = values[MAT3_GET(2, 0)] * v.x + values[MAT3_GET(2, 1)] * v.y + values[MAT3_GET(2, 2)] * v.z;

		return v1;
	}

	template<class T>
	inline void Matrix3<T>::print()
	{
		std::cout << *this;
	}

	template<class T>
	Matrix3<T>& Matrix3<T>::operator*=(const Matrix3<T>& mat2)
	{
		return multiply(mat2);
	}

	template<class T>
	Matrix3<T>& Matrix3<T>::operator*=(const T& v)
	{
		return multiply(v);
	}

	template<class T>
	Vector3<T>& Matrix3<T>::operator[](unsigned int i)
	{
		return columns[i];
	}

	template<class T>
	Matrix3<T> operator*(const Matrix3<T>& mat1, const Matrix3<T>& mat2)
	{
		return Matrix3<T>(mat1).multiply(mat2);
	}

	template<class T>
	Matrix3<T> operator*(const Matrix3<T>& mat, const T& v)
	{
		return Matrix3<T>(mat).multiply(v);
	}

	template <class T>
	Vector2<T> operator*(const Matrix3<T>& mat, const Vector2<T>& v)
	{
		Vector3<T> v1(mat*Vector3<T>(v.x,v.y,1));

		return Vector2<T>(v1.x / v1.z, v1.y / v1.z);
	}

	template<class T>
	Vector3<T> operator*(const Matrix3<T>& mat, const Vector3<T>& v)
	{
		return mat.multiply(v);
	}

	template<class T>
	std::ostream& operator<<(std::ostream& os, const Matrix3<T>& mat)
	{
		for (unsigned int r = 0; r < 3; r++)
		{
			os << "[ ";
			for (unsigned int c = 0; c < 3; c++)
			{
				os << mat.values[MAT3_GET(r, c)] << " ";
			}
			os << "]" << std::endl;
		}

		return os;
	}
}

#endif
