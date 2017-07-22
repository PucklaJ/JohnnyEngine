#pragma once
#include "../include/Vector3.h"
#include "../include/Vector2.h"
#include <iostream>

#define MAT3_GET(r,c) (r + c * 3)

namespace Johnny
{
	template<class T> class Matrix3;
	template<class T> Matrix3<T> operator*(const Matrix3<T>&, const Matrix3<T>&);
	template<class T> Matrix3<T> operator*(const Matrix3<T>&, const T&);
	template<class T> std::ostream& operator<<(std::ostream&, const Matrix3<T>&);
	template<class T> Vector3<T> operator*<>(const Matrix3<T>&, const Vector3<T>&);

	template<class T>
	class Matrix3
	{
	public:
		static Matrix3 identity();
		static Matrix3 translate(const T&,const T&);
		static Matrix3 translate(const Vector2<T>&);
		static Matrix3 rotate(const T&);
		static Matrix3 scale(const T&,const T&);
		static Matrix3 scale(const Vector2<T>&);
		static Matrix3 camera(const Vector2<T>&,const T&,const T&);


		Matrix3() = default;
		Matrix3(const T&);
		Matrix3(const Matrix3&);

		union
		{
			T values[3 * 3];
			Vector3<T> columns[3];
		};

		Matrix3& multiply(const Matrix3&);
		Matrix3& multiply(const T&);
		Vector3<T> multiply(const Vector3<T>&) const;

		void print();

		Matrix3& operator*=(const Matrix3&);
		Matrix3& operator*=(const T&);

		friend Matrix3<T> operator*<>(const Matrix3<T>&, const Matrix3<T>&);
		friend Matrix3<T> operator*<>(const Matrix3<T>&, const T&);
		friend Vector3<T> operator*<>(const Matrix3<T>&,const Vector3<T>&);

		friend std::ostream& operator<< <>(std::ostream&, const Matrix3<T>&);
	};

	typedef Matrix3<GLfloat> Matrix3f;
	typedef Matrix3<GLdouble> Matrix3d;
	typedef Matrix3<GLint> Matrix3i;
}

#include "../src/Matrix3.cpp"
