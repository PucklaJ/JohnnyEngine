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

	/*! \brief A class which represents a 4x4 matrix
	 *  \param T The type of the elements of the matrix
	 */
	template<class T>
	class Matrix4
	{
	public:
		/*! \brief Creates a 4x4 identity matrix
		 *  \return The newly created 4x4 identity matrix
		 */
		static Matrix4 identity();
		/*! \brief Creates a 4x4 perspective projection matrix
		 *  \param fov The field of view of the projection in degrees
		 *  \param aspect The aspect ratio
		 *  \param far The far plane where geometry clips
		 *  \param near The near plane where geometry clips
		 *  \return The newly created 4x4 perspective projection matrix
		 */
		static Matrix4 perspective(const T& fov,const T& aspect,const T& far,const T& near);
		/*! \brief Creates a 4x4 orthographic projection matrix
		 *  \param top The top plane
		 *  \param bottom The bottom plane
		 *  \param right The right plane
		 *  \param left The left plane
		 *  \param far The far plane
		 *  \param near The near plane
		 *  \return The newly created 4x4 orthographic projection matrix
		 */
		static Matrix4 orthographic(const T& top, const T& bottom, const T& right, const T& left, const T& far, const T& near);
		/*! \brief Creates a 4x4 worldview matrix
		 *  \param position The position of the viewer
		 *  \param middle The point on which the viewer looks
		 *  \param up The direction vector which defines the up direction
		 *  \return The newly created 4x4 worldview matrix
		 */
		static Matrix4 lookAt(const Vector3<T>& position, const Vector3<T>& middle, const Vector3<T>& up);
		/*! \brief Creates a 4x4 translation matrix
		 *  \param x How mauch to translate on the x-Axis
		 *  \param y How much to translate on the y-Axis
		 *  \param z How much to translate on the z-Axis
		 *  \return The newly created 4x4 translation matrix
		 */
		static Matrix4 translate(const T& x, const T& y, const T& z);
		/*! \brief Creates a 4x4 translation matrix
		 *  \param v The translation vector
		 *  \return The newly created 4x4 translation matrix
		 */
		static Matrix4 translate(const Vector3<T>& v);
		/*! \brief Creates a 4x4 rotation matrix
		 *  \param angle How much degrees to rotate
		 *  \param axis The axis on which to rotate
		 *  \return The newly created 4x4 rotation matrix
		 */
		static Matrix4 rotate(const T& angle, const Vector3<T>& axis);
		/*! \brief Creates a 4x4 scale matrix
		 *  \param x How much to scale on the x-Axis
		 *  \param y How much to scale on the y-Axis
		 *  \param z How much to scale on the z-Axis
		 *  \return The newly created 4x4 scale matrix
		 */
		static Matrix4 scale(const T& x, const T& y, const T& z);
		/*! \brief Creates a 4x4 scale matrix
		 *  \param v The scale vector
		 *  \return The newly created 4x4 scale matrix
		 */
		static Matrix4 scale(const Vector3<T>& v);

		Matrix4() = default;
		/*! \brief Creates a new 4x4 matrix
		 *  \param d The value of all diagonal values
		 */
		Matrix4(const T& d);
		/*! \brief The copy constructor
		 *  \param mat The matrix from which to copy
		 */
		Matrix4(const Matrix4& mat);

		union
		{
			T values[4 * 4] INIT_IDENTITY; //!< The elements of the matrix as an array
			Vector4<T> columns[4];		   //!< The elements of the matrix as an array of columns 
		};

        /*! \brief Multiplies this matrix with another one
         *  \param mat The matrix to multiply with
         *  \return A reference to this matrix
         */
		Matrix4& multiply(const Matrix4& mat);
		/*! \brief Multiplies this matrix with a scalar
		 *  \param s The scalar to multiply with
		 *  \return A reference to this matrix
		 */
		Matrix4& multiply(const T& s);
		/*! \brief Multiplies this matrix with a Vector4<T>
		 *  \param v The vector to multiply with
		 *  \return The resulting Vector4<T>
		 */
		Vector4<T> multiply(const Vector4<T>& v) const;

		/*! \brief Prints this matrix to the console
		 *
		 */
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
