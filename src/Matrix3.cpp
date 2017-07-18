#include "../include/Matrix3.h"
/*#include <string>
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

		for (unsigned int r = 0; r < 3;r++)
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
				values[MAT3_GET(r,i)] = sum[i];
			}
		}
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
	Matrix3<T>& operator*=(Matrix3<T>& mat1, const Matrix3<T>& mat2)
	{
		return mat1.multiply(mat2);
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
				os << std::string("") + mat.values[MAT3_GET(r,c)] + " ";
			}
			os << "]"
		}

		return os;
	}
}*/
