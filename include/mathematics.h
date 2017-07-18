#ifndef MATHEMATICS_H_INCLUDED
#define MATHEMATICS_H_INCLUDED
#include <ostream>
#define _USE_MATH_DEFINES 1
#include <cmath>
#include <math.h>
#include <vector>
#include <algorithm>
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix3.h"

namespace Johnny
{
    extern double abs(const double& d);
    extern int getRand(int min,int max);
    extern bool luck(int percent);
    
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

    template<class T>
    inline T get(const std::vector<T>& vars,int x, int y,int w)
    {
        return vars[y * w + x];
    }
    
    template<class T,class D>
    inline bool contains(const std::vector<T>& vars,const D& var)
    {
        return std::find(vars.begin(),vars.end(),var) != vars.end();
    }
    
    template<class T>
    inline void swap(T var1,T var2)
    {
        T temp = var1;
        var1 = var2;
        var2 = temp;
    }
    
    template<class T>
    inline void reverse(const std::vector<T>& vars)
    {
        int j = 0;
        for(int i = (int)vars.size()-1;i>j;i--)
        {
            swap(vars[i],vars[j]);
            j++;
        }
    }
    
    template<class T>
    inline int sizeOfArray(T var[])
    {
        return sizeof(var)/sizeof(*var);
    }
    
    extern std::vector<A_Square> a_stern(std::vector<A_Square>&,A_Square&,A_Square&,int);

}





#endif // MATHEMATICS_H_INCLUDED
