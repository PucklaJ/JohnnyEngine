#pragma once
#include "../include/Vector4.h"
#include "../include/Vector3.h"
#include <iostream>

#define MAT4_GET(r,c) (r + c * 4)
#define INIT_IDENTITY = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1}

namespace Johnny
{
	template<class T> class Matrix4;
	template<class T> Matrix4<T> operator*(const Matrix4<T>&, const Matrix4<T>&);
	template<class T> Matrix4<T> operator*(const Matrix4<T>&, const T&);
	template<class T> Vector4<T> operator*(const Matrix4<T>&,const Vector4<T>&);
	template<class T> std::ostream& operator<<(std::ostream&, const Matrix4<T>&);

	template<class T>
	class Matrix4
	{
	public:
		static Matrix4 identity();
		static Matrix4 perspective(const T&,const T&,const T&,const T&);
		static Matrix4 orthographic(const T&,const T&,const T&,const T&,const T&,const T&);
		static Matrix4 lookAt(const Vector3<T>&,const Vector3<T>&, const Vector3<T>&);
		static Matrix4 translate(const T&, const T&, const T&);
		static Matrix4 translate(const Vector3<T>&);
		static Matrix4 rotate(const T&, const Vector3<T>&);
		static Matrix4 scale(const T&, const T&, const T&);
		static Matrix4 scale(const Vector3<T>&);

		Matrix4() = default;
		Matrix4(const T&);
		Matrix4(const Matrix4&);

		union
		{
			T values[4 * 4] INIT_IDENTITY;
			Vector4<T> columns[4];
		};

		Matrix4& multiply(const Matrix4&);
		Matrix4& multiply(const T&);
		Vector4<T> multiply(const Vector4<T>&) const;

		void print();

		Matrix4& operator*=(const Matrix4&);
		Matrix4& operator*=(const T&);

		Vector4<T>& operator[](unsigned int);

		friend Matrix4<T> operator*<>(const Matrix4<T>&, const Matrix4<T>&);
		friend Matrix4<T> operator*<>(const Matrix4<T>&, const T&);
		friend Vector4<T> operator*<>(const Matrix4<T>&,const Vector4<T>&);

		friend std::ostream& operator<< <>(std::ostream&, const Matrix4<T>&);
	};

	typedef Matrix4<GLfloat> Matrix4f;
	typedef Matrix4<GLdouble> Matrix4d;
	typedef Matrix4<GLint> Matrix4i;
}

#include "../src/Matrix4.cpp"
