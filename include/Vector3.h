#pragma once
#include <GL/glew.h>
#include <iostream>
#include "Vector4.h"
#include <glm/glm.hpp>

namespace Johnny
{
	template<class T> class Vector3;
	template<class T> Vector3<T> operator+(const Vector3<T>&, const Vector3<T>&);
	template<class T> Vector3<T> operator-(const Vector3<T>&, const Vector3<T>&);
	template<class T> Vector3<T> operator*(const Vector3<T>&, const Vector3<T>&);
	template<class T> Vector3<T> operator*(const Vector3<T>&, const T&);
	template<class T> Vector3<T> operator/(const Vector3<T>&, const Vector3<T>&);
	template<class T> Vector3<T> operator-(const Vector3<T>&);

	template<class T> std::ostream& operator<<(std::ostream&, const Vector3<T>&);

	template<class T>
	class Vector3
	{
	public:
		Vector3() = default;
		Vector3(const T&, const T&, const T&);
		Vector3(const Vector3&);
		Vector3(const Vector4<T>&);



		union
		{
			T x = 0;
			T r;
			T width;
		};

		union
		{
			T y = 0;
			T g;
			T height;
		};

		union
		{
			T z = 0;
			T b;
			T depth;
		};
        
        glm::vec3 toGLM() const;

		T length(bool squared = false) const;
		Vector3& normalise();
        Vector3 normaliseConst() const;

		Vector3& add(const Vector3&);
		Vector3& subtract(const Vector3&);
		Vector3& multiply(const Vector3&);
		Vector3& multiply(const T&);
		Vector3& divide(const Vector3&);
		Vector3& divide(const T&);

		Vector3 cross(const Vector3&);
		T dot(const Vector3&);
		T distance(const Vector3&, bool squared = false) const;

		Vector3& operator+=(const Vector3&);
		Vector3& operator-=(const Vector3&);
		Vector3& operator*=(const Vector3&);
		Vector3& operator*=(const T&);
		Vector3& operator/=(const Vector3&);

		Vector3& operator=(const Vector4<T>&);

		T& operator[](unsigned int);

		friend Vector3<T> operator+<>(const Vector3<T>&, const Vector3<T>&);
		friend Vector3<T> operator-<>(const Vector3<T>&, const Vector3<T>&);
		friend Vector3<T> operator*<>(const Vector3<T>&, const Vector3<T>&);
		friend Vector3<T> operator*<>(const Vector3<T>&, const T&);
		friend Vector3<T> operator/<>(const Vector3<T>&, const Vector3<T>&);
		friend Vector3<T> operator-<>(const Vector3<T>&);

		friend std::ostream& operator<< <>(std::ostream&, const Vector3<T>&);
	};
    
    template<class T>
    extern Vector3<T> toMy(const glm::vec3&);

	typedef Vector3<GLfloat> Vector3f;
	typedef Vector3<GLdouble> Vector3d;
	typedef Vector3<GLint> Vector3i;
}

#include "../src/Vector3.cpp"
