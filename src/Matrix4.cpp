#ifndef MATRIX4_CPP
#define MATRIX4_CPP
#include "../include/Matrix4.h"
#include <string>
#include "../include/operators.h"
#ifndef _USE_MATH_DEFINES
	#define _USE_MATH_DEFINES 1
#endif
#include "../include/mathematics_functions.h"

namespace Johnny
{
	template<class T>
	Matrix4<T> Matrix4<T>::identity()
	{
		return Matrix4(1);
	}

	template<class T>
	Matrix4<T> Matrix4<T>::perspective(const T& fov, const T& aspect, const T& far, const T& near)
	{
		Matrix4<T> mat(1);
		T tanFovHalf = (T)tan((double)(toRadians(fov) / (T)2));

		mat.values[MAT4_GET(0, 0)] = (T)1 / (aspect * tanFovHalf);
		mat.values[MAT4_GET(1, 1)] = (T)1 / tanFovHalf;
		mat.values[MAT4_GET(2, 2)] = - ((far+near)/(far-near));
		mat.values[MAT4_GET(2, 3)] = - ((2*far*near)/(far-near));
		mat.values[MAT4_GET(3, 2)] = -1;
		mat.values[MAT4_GET(3, 3)] = 0;

		return mat;
	}

	template<class T>
	Matrix4<T> Matrix4<T>::orthographic(const T& top, const T& bottom, const T& right, const T& left, const T& far, const T& near)
	{
		Matrix4<T> mat(1);

		mat.values(MAT4_GET(0, 0)) = (T)2 / (right-left);
		mat.values(MAT4_GET(1, 1)) = (T)2 / (top-bottom);
		mat.values(MAT4_GET(2, 2)) = (T)-2 / (far-near);
		mat.values(MAT4_GET(0, 3)) = - ((right+left)/(right-left));
		mat.values(MAT4_GET(1, 3)) = - ((top+bottom)/(top-bottom));
		mat.values(MAT4_GET(2, 3)) = - ((far+near)/(far-near));

		return mat;
	}

	template<class T>
	Matrix4<T> Matrix4<T>::lookAt(const Vector3<T>& position, const Vector3<T>& middle, const Vector3<T>& up)
	{
		// Src: https://github.com/TheCherno/Sparky/blob/master/Sparky-core/src/sp/maths/mat4.cpp

		Matrix4<T> result(1);
		Vector3<T> f = (middle - position).normalise();
		Vector3<T> s = f.cross(up.normalise());
		Vector3<T> u = s.cross(f);

		result.values[0 + 0 * 4] = s.x;
		result.values[0 + 1 * 4] = s.y;
		result.values[0 + 2 * 4] = s.z;
			   
		result.values[1 + 0 * 4] = u.x;
		result.values[1 + 1 * 4] = u.y;
		result.values[1 + 2 * 4] = u.z;
			   
		result.values[2 + 0 * 4] = -f.x;
		result.values[2 + 1 * 4] = -f.y;
		result.values[2 + 2 * 4] = -f.z;

		return result * translate(-position.x, -position.y, -position.z);
	}

	template<class T>
	Matrix4<T> Matrix4<T>::translate(const T& x, const T& y, const T& z)
	{
		Matrix4<T> mat(1);

		mat.values[MAT4_GET(0, 3)] = x;
		mat.values[MAT4_GET(1, 3)] = y;
		mat.values[MAT4_GET(2, 3)] = z;

		return mat;
	}

	template<class T>
	Matrix4<T> Matrix4<T>::translate(const Vector3<T>& v)
	{
		return translate(v.x,v.y,v.z);
	}

	template<class T>
	Matrix4<T> Matrix4<T>::rotate(const T& angle, const Vector3<T>& axis)
	{
		// Src: https://github.com/TheCherno/Sparky/blob/master/Sparky-core/src/sp/maths/mat4.cpp

		Matrix4<T> result(1);

		T r = toRadians(angle);
		T c = (T)cos((double)r);
		T s = (T)sin((double)r);
		T omc = (T)1 - c;

		T x = axis.x;
		T y = axis.y;
		T z = axis.z;

		result.values[0 + 0 * 4] = x * x * omc + c;
		result.values[0 + 1 * 4] = y * x * omc + z * s;
		result.values[0 + 2 * 4] = x * z * omc - y * s;

		result.values[1 + 0 * 4] = x * y * omc - z * s;
		result.values[1 + 1 * 4] = y * y * omc + c;
		result.values[1 + 2 * 4] = y * z * omc + x * s;

		result.values[2 + 0 * 4] = x * z * omc + y * s;
		result.values[2 + 1 * 4] = y * z * omc - x * s;
		result.values[2 + 2 * 4] = z * z * omc + c;

		return result;
	}

	template<class T>
	Matrix4<T> Matrix4<T>::scale(const T& x, const T& y, const T& z)
	{
		Matrix4<T> mat(1);

		mat.values[MAT4_GET(0, 0)] = x;
		mat.values[MAT4_GET(1, 1)] = y;
		mat.values[MAT4_GET(2, 2)] = z;

		return mat;
	}

	template<class T>
	Matrix4<T> Matrix4<T>::scale(const Vector3<T>& v)
	{
		scale(v.x,v.y,v.z);
	}

	template<class T>
	Matrix4<T>::Matrix4(const T& v)
	{
		for (unsigned int i = 0; i < 16; i++)
		{
			values[i] = 0;
		}

		values[MAT4_GET(0, 0)] = v;
		values[MAT4_GET(1, 1)] = v;
		values[MAT4_GET(2, 2)] = v;
		values[MAT4_GET(3, 3)] = v;
	}

	template<class T>
	Matrix4<T>::Matrix4(const Matrix4<T>& mat)
	{
		for (unsigned int i = 0; i < 16; i++)
			values[i] = mat.values[i];
	}

	template<class T>
	Matrix4<T>& Matrix4<T>::multiply(const Matrix4<T>& mat)
	{
		T sum[4];

		for (unsigned int r = 0; r < 4; r++)
		{
			for (unsigned int c = 0; c < 4; c++)
			{
				sum[c] = 0;
				for (unsigned int i = 0; i < 4; i++)
				{
					sum[c] += values[MAT4_GET(r, i)] * mat.values[MAT4_GET(i, c)];
				}
			}

			for (unsigned int i = 0; i < 4; i++)
			{
				values[MAT4_GET(r, i)] = sum[i];
			}
		}

		return *this;
	}

	template<class T>
	Matrix4<T> & Matrix4<T>::multiply(const T& v)
	{
		for (unsigned int i = 0; i < 16; i++)
		{
			values[i] *= v;
		}
	}

	template<class T>
	inline void Matrix4<T>::print()
	{
		std::cout << *this;
	}

	template<class T>
	Matrix4<T>& Matrix4<T>::operator*=(const Matrix4<T>& mat2)
	{
		return multiply(mat2);
	}

	template<class T>
	Matrix4<T>& Matrix4<T>::operator*=(const T& v)
	{
		return multiply(v);
	}

	template<class T>
	Matrix4<T> operator*(const Matrix4<T>& mat1, const Matrix4<T>& mat2)
	{
		return Matrix4<T>(mat1).multiply(mat2);
	}

	template<class T>
	Matrix4<T> operator*(const Matrix4<T>& mat, const T& v)
	{
		return Matrix4<T>(mat).multiply(v);
	}

	template<class T>
	std::ostream& operator<<(std::ostream& os, const Matrix4<T>& mat)
	{
		for (unsigned int r = 0; r < 4; r++)
		{
			os << "[ ";
			for (unsigned int c = 0; c < 4; c++)
			{
				os << mat.values[MAT4_GET(r, c)] << " ";
			}
			os << "]" << std::endl;
		}

		return os;
	}
}

#endif
