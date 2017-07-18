#pragma once
#include "../include/Vector3.h"
#include <iostream>

#define MAT3_GET(r,c) (r + c * 3)

namespace Johnny
{
	template<class T>
	class Matrix3
	{
	public:
		static Matrix3 identity();

		Matrix3() = default;
		Matrix3(const T&);

		union
		{
			T values[3 * 3];
			Vector3<T> columns[3];
		};

		Matrix3& multiply(const Matrix3&);
		Matrix3& multiply(const T&);

		void print();

		Matrix3& operator*=(const Matrix3&);
		friend Matrix3& operator*=(Matrix3&, const T&);

		friend Matrix3 operator*(const Matrix3&, const Matrix3&);
		friend Matrix3 operator*(const Matrix3&, const T&);

		friend std::ostream& operator<<(std::ostream&, const Matrix3&);
	};

	typedef Matrix3<GLfloat> Matrix3f;
	typedef Matrix3<GLdouble> Matrix3d;
	typedef Matrix3<GLint> Matrix3i;
}

#include <string>
#include "../include/operators.h"

namespace Johnny
{
	template<class T>
	Matrix3<T> Matrix3<T>::identity()
	{
		return Matrix3(1);
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
		for (unsigned int r = 0; r < 3; r++)
		{
			std::cout << "[ ";
			for (unsigned int c = 0; c < 3; c++)
			{
				std::cout << values[MAT3_GET(r, c)] << " ";
			}
			std::cout << "]" << std::endl;
		}
	}

	template<class T>
	Matrix3<T>& Matrix3<T>::operator*=(const Matrix3<T>& mat2)
	{
		return multiply(mat2);
	}

	template<class T>
	Matrix3<T>& operator*=(Matrix3<T>& mat, const T& v)
	{
		return mat.multiply(v);
	}

	template<class T>
	Matrix3<T> operator*(const Matrix3<T>& mat1, const Matrix3<T>& mat2)
	{
		return mat1.multiply(mat2);
	}
	template<class T>
	Matrix3<T> operator*(const Matrix3<T>& mat, const T& v)
	{
		return mat.multiply(v);
	}

	template<class T>
	std::ostream& operator<<(std::ostream& os, const Matrix3<T>& mat)
	{
		for (unsigned int c = 0; c < 3; c++)
		{
			os << "[ ";
			for (unsigned int r = 0; r < 3; r++)
			{
				os << std::string("") + mat.values[MAT3_GET(r, c)] + " ";
			}
			os << "]"
		}

		return os;
	}
}
