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
	/*! \brief Converts degrees into radians
	 *  \param degrees The value in degrees
	 *  \return The value in radians
	 */
	template<class T>
	inline T toRadians(const T& degrees)
	{
		return degrees / (T)180 * (T)M_PI;
	}

	/*! \brief Converts radians into degrees
	 *  \param radians The value in radians
	 *  \return The value in degrees
	 */
	template<class T>
	inline T toDegrees(const T& radians)
	{
		return radians * (T)180 / (T)M_PI;
	}

	/*! \brief Gets the absolute value of a number
	 *  \param d The value to get the absolute from
	 *  \param The absolute value of d
	 */
	template<class T>
	inline double abs(const T& d)
	{
		return d < (T)0 ? -d : d;
	}


	/*! \brief Gets a random value in a given range
	 *  \param min The minimum value
	 *  \param max The maximum value
	 *  \return A random value between min and max
	 */
	inline int getRand(int min, int max)
	{
		return rand() % (max - min + 1) + (min);
	}

	/*! \param percent The amount of percent in which the return value should be true
	 *  \return true if a random value between 1 and 100 <= percent
	 */
	inline bool luck(int percent)
	{
		return getRand(1, 100) <= percent;
	}

	/*! \brief Gets an elements of an array for a given coordinate
	 *  \param vars The array to fetch the element from
	 *  \param x The x coordinate of the element
	 *  \param y The y coordinate of the element
	 *  \param w The width of the 2D array
	 *  \return The element at the given coordinate
	 */
	template<class T>
	inline T get(const std::vector<T>& vars, int x, int y, int w)
	{
		return vars[y * w + x];
	}

	/*! \brief Checks if a given value is inside a given array
	 *  \param vars The array to check
	 *  \param var The variable to check
	 *  \return true if the variable is inside the array and false if not
	 */
	template<class T, class D>
	inline bool contains(const std::vector<T>& vars, const D& var)
	{
		return std::find(vars.begin(), vars.end(), var) != vars.end();
	}

	/*! \brief Swaps two variables with each other
	 *  \param var1 The one variable for the swap
	 *  \param var2 The other variable for the swap
	 */
	template<class T>
	inline void swap(T var1, T var2)
	{
		T temp = var1;
		var1 = var2;
		var2 = temp;
	}

	/*! \brief Reverses a given array
	 *  \param vars The array to reverse
	 */
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

	/*! \param var The array from which to get the size
	 *  \return The number of elements of an array
	 */
	template<class T>
	inline int sizeOfArray(T var[])
	{
		return sizeof(var) / sizeof(*var);
	}

	/*! \brief clamps a value between to given boundaries
	 *  \param var The variable to clamp
	 *  \param min The minimum boundary
	 *  \param max The maximum boundary
	 *  \return if var>max then max if var<min then min else var
	 */
	template<class T>
	inline T clamp(const T& var,const T& min,const T& max)
	{
		return (var > max ? max : (var < min ? min : var));
	}
    
    /*! \brief Prints a 3x3 matrix to the console DEPRECATED
     *  \param mat The matrix to print
     */
    extern void print(const glm::mat3& mat);
    /*! \brief Prints a 4x4 matrix to the console DEPRECATED
     *  \param mat The matrix to print
     */
    extern void print(const glm::mat4& mat);
}
