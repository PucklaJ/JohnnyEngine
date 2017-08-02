#pragma once
#ifndef _USE_MATH_DEFINES 
	#define _USE_MATH_DEFINES 1
#endif
#include <cmath>
#include <math.h>
#include <cstdlib>
#include <vector>
#include <glm/glm.hpp>
#include <algorithm>

namespace Johnny
{
	template<class T>
	inline T toRadians(const T& degrees)
	{
		return degrees / (T)180 * (T)M_PI;
	}

	template<class T>
	inline T toDegrees(const T& radians)
	{
		return radians * (T)180 / (T)M_PI;
	}

	template<class T>
	inline double abs(const T& d)
	{
		return d < (T)0 ? -d : d;
	}


	inline int getRand(int min, int max)
	{
		return rand() % (max - min + 1) + (min);
	}

	inline bool luck(int percent)
	{
		return getRand(1, 100) <= percent;
	}

	template<class T>
	inline T get(const std::vector<T>& vars, int x, int y, int w)
	{
		return vars[y * w + x];
	}

	template<class T, class D>
	inline bool contains(const std::vector<T>& vars, const D& var)
	{
		return std::find(vars.begin(), vars.end(), var) != vars.end();
	}

	template<class T>
	inline void swap(T var1, T var2)
	{
		T temp = var1;
		var1 = var2;
		var2 = temp;
	}

	template<class T>
	inline void reverse(const std::vector<T>& vars)
	{
		int j = 0;
		for (int i = (int)vars.size() - 1; i>j; i--)
		{
			swap(vars[i], vars[j]);
			j++;
		}
	}

	template<class T>
	inline int sizeOfArray(T var[])
	{
		return sizeof(var) / sizeof(*var);
	}

	template<class T>
	inline T clamp(const T& var,const T& min,const T& max)
	{
		return (var > max ? max : (var < min ? min : var));
	}
    
    extern void print(const glm::mat3&);
    extern void print(const glm::mat4&);
}
