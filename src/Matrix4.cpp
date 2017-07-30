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

		mat.values[MAT4_GET(0, 0)] = (T)2 / (right-left);
		mat.values[MAT4_GET(1, 1)] = (T)2 / (top-bottom);
		mat.values[MAT4_GET(2, 2)] = (T)-2 / (far-near);
		mat.values[MAT4_GET(0, 3)] = - ((right+left)/(right-left));
		mat.values[MAT4_GET(1, 3)] = - ((top+bottom)/(top-bottom));
		mat.values[MAT4_GET(2, 3)] = - ((far+near)/(far-near));

		return mat;
	}

	template<class T>
	Matrix4<T> Matrix4<T>::lookAt(const Vector3<T>& position, const Vector3<T>& middle, const Vector3<T>& up)
	{
		// Src: https://github.com/TheCherno/Sparky/blob/master/Sparky-core/src/sp/maths/mat4.cpp

		/*Matrix4<T> Result(1);
		Vector3<T> f = Vector3<T>(middle - position).normalise();
		Vector3<T> s = f.cross(up);
		Vector3<T> u = s.cross(f);

		Result.values[0 + 0 * 4] = s.x;
		Result.values[1 + 0 * 4] = s.y;
		Result.values[2 + 0 * 4] = s.z;
			   
		Result.values[0 + 1 * 4] = u.x;
		Result.values[1 + 1 * 4] = u.y;
		Result.values[2 + 1 * 4] = u.z;
			   
		Result.values[0 + 2 * 4] = f.x;
		Result.values[1 + 2 * 4] = f.y;
		Result.values[2 + 2 * 4] = f.z;

		Result.values[0 + 3 * 4] = -position.x;
		Result.values[1 + 3 * 4] = -position.y;
		Result.values[2 + 3 * 4] = -position.z;


		 * tvec3<T, P> const f(normalize(center - eye));
		tvec3<T, P> const s(normalize(cross(f, up)));
		tvec3<T, P> const u(cross(s, f));

		tmat4x4<T, P> Result(1);
		Result[0][0] = s.x;
		Result[1][0] = s.y;
		Result[2][0] = s.z;
		Result[0][1] = u.x;
		Result[1][1] = u.y;
		Result[2][1] = u.z;
		Result[0][2] =-f.x;
		Result[1][2] =-f.y;
		Result[2][2] =-f.z;
		Result[3][0] =-dot(s, eye);
		Result[3][1] =-dot(u, eye);
		Result[3][2] = dot(f, eye);
		return Result;*/


		Vector3<T> f = Vector3<T>(middle - position).normalise();
		Vector3<T> s = f.cross(up).normalise();
		Vector3<T> u = s.cross(f);

		Matrix4<T> Result(1);
		Result.values[MAT4_GET(0,0)] = s.x;
		Result.values[MAT4_GET(0,1)] = s.y;
		Result.values[MAT4_GET(0,2)] = s.z;
		Result.values[MAT4_GET(1,0)] = u.x;
		Result.values[MAT4_GET(1,1)] = u.y;
		Result.values[MAT4_GET(1,2)] = u.z;
		Result.values[MAT4_GET(2,0)] =-f.x;
		Result.values[MAT4_GET(2,1)] =-f.y;
		Result.values[MAT4_GET(2,2)] =-f.z;
		Result.values[MAT4_GET(0,3)] =-s.dot(position);
		Result.values[MAT4_GET(1,3)] =-u.dot(position);
		Result.values[MAT4_GET(2,3)] = f.dot(position);
		return Result;

		return Result;
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
	Matrix4<T> Matrix4<T>::rotate(const T& angle, const Vector3<T>& v)
	{
		// Src: https://github.com/TheCherno/Sparky/blob/master/Sparky-core/src/sp/maths/mat4.cpp

		/*Matrix4<T> result(1);

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

		return result;*/

		const T a = toRadians(angle);
		const T c = cos(a);
		const T s = sin(a);

		Vector3<T> axis(v);axis.normalise();
		Vector3<T> temp(axis*(T(1) - c));

		Matrix4<T> Rotate(1);
		Rotate.values[MAT4_GET(0,0)] = c + temp.x * axis.x;
		Rotate.values[MAT4_GET(1,0)] = temp.x * axis.y + s * axis.z;
		Rotate.values[MAT4_GET(2,0)] = temp.x * axis.z - s * axis.y;

		Rotate.values[MAT4_GET(0,1)] = temp.y * axis.x - s * axis.z;
		Rotate.values[MAT4_GET(1,1)] = c + temp.y * axis.y;
		Rotate.values[MAT4_GET(2,1)] = temp.y * axis.z + s * axis.x;

		Rotate.values[MAT4_GET(0,2)] = temp.z * axis.x + s * axis.y;
		Rotate.values[MAT4_GET(1,2)] = temp.z * axis.y - s * axis.x;
		Rotate.values[MAT4_GET(2,2)] = c + temp.z * axis.z;

		/*Matrix4<T> Result(0);
		Result[0] = m[0] * Rotate[0][0] + m[1] * Rotate[0][1] + m[2] * Rotate[0][2];
		Result[1] = m[0] * Rotate[1][0] + m[1] * Rotate[1][1] + m[2] * Rotate[1][2];
		Result[2] = m[0] * Rotate[2][0] + m[1] * Rotate[2][1] + m[2] * Rotate[2][2];
		Result[3] = m[3];*/
		return Rotate;
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
		return scale(v.x,v.y,v.z);
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
	Vector4<T> Matrix4<T>::multiply(const Vector4<T>& v) const
	{
		Vector4<T> v1(v);

		v1.x = values[MAT4_GET(0,0)] * v.x + values[MAT4_GET(0,1)] * v.y + values[MAT4_GET(0,2)] * v.z + values[MAT4_GET(0,3)] * v.w;
		v1.y = values[MAT4_GET(1,0)] * v.x + values[MAT4_GET(1,1)] * v.y + values[MAT4_GET(1,2)] * v.z + values[MAT4_GET(1,3)] * v.w;
		v1.z = values[MAT4_GET(2,0)] * v.x + values[MAT4_GET(2,1)] * v.y + values[MAT4_GET(2,2)] * v.z + values[MAT4_GET(2,3)] * v.w;
		v1.w = values[MAT4_GET(3,0)] * v.x + values[MAT4_GET(3,1)] * v.y + values[MAT4_GET(3,2)] * v.z + values[MAT4_GET(3,3)] * v.w;

		return v1;
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
	Vector4<T>& Matrix4<T>::operator[](unsigned int i)
	{
		return columns[i];
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
	Vector4<T> operator*(const Matrix4<T>& mat,const Vector4<T>& v)
	{
		return mat.multiply(v);
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
