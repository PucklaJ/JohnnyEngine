#ifndef MATRIX3_CPP
#define MATRIX3_CPP
#include "../include/Matrix3.h"
#include "../include/Matrix4.h"
#include <string>
#include "../include/mathematics_functions.h"

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

		/*Matrix4<T> mat1 = Matrix4<T>::rotate(angle, Vector3<T>(0, 0, 1));

		for (unsigned int r = 0; r < 3; r++)
		{
			for (unsigned int c = 0; c < 3; c++)
			{
				mat.values[MAT3_GET(r, c)] = mat1.values[MAT4_GET(r, c)];
			}
		}*/


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
		return translate(position*(T)-1) * rotate(rotation) * scale(zoom, zoom);
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
	Matrix3<T> operator*(const Matrix3<T>& mat1, const Matrix3<T>& mat2)
	{
		return Matrix3<T>(mat1).multiply(mat2);
	}

	template<class T>
	Matrix3<T> operator*(const Matrix3<T>& mat, const T& v)
	{
		return Matrix3<T>(mat).multiply(v);
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