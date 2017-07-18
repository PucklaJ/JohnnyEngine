#ifndef MATHEMATICS_H_INCLUDED
#define MATHEMATICS_H_INCLUDED
#include <ostream>
#ifndef _USE_MATH_DEFINES 
	#define _USE_MATH_DEFINES 1
#endif
#include <cmath>
#include <math.h>
#include <vector>
#include <algorithm>
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include "mathematics_functions.h"

namespace Johnny
{   
    struct A_Square
    {
		A_Square(int x_,int y_,unsigned int g_, bool solid_)
		{
			x = x_;
			y = y_;
			g = g_;
			solid = solid_;
		}
        
		int x;
		int y;
		unsigned int g;
		bool solid;
		A_Square* m_previous = nullptr;
    };
    
    extern std::vector<A_Square> a_stern(std::vector<A_Square>&,A_Square&,A_Square&,int);
}





#endif // MATHEMATICS_H_INCLUDED
