#ifndef MATHEMATICS_H_INCLUDED
#define MATHEMATICS_H_INCLUDED
#include <ostream>
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES 1
#endif
#include "Matrix3.h"
#include "Matrix4.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "mathematics_functions.h"
#include <algorithm>
#include <cmath>
#include <math.h>
#include <vector>

namespace Johnny {
/*! \brief A struct which represents a square of the AStar algorithm
 *
 */
struct A_Square {
  /*! \brief Creates a new A_Square
   *  \param x_ The x position of the new A_Square
   *  \param y_ The y position of the new A_Square
   *  \param g_ The g value of the new A_Square
   *  \param solid_ Wether the A_Square is solid
   */
  A_Square(int x_, int y_, unsigned int g_, bool solid_) {
    x = x_;
    y = y_;
    g = g_;
    solid = solid_;
  }

  int x;                          //!< The x position of the square
  int y;                          //!< The y position of the square
  unsigned int g;                 //!< The g value of the square
  bool solid;                     //!< Determines if the square is solid
  A_Square *m_previous = nullptr; //!< The square from which the pathfinder came
};

/*! \brief The AStar algorithm
 *  \param field A vector containing a field of A_Squares
 *  \param start The start square for the algorithm
 *  \param end The end square for the algorithm
 *  \param w The width of the field in A_Squares
 */
extern std::vector<A_Square> a_stern(std::vector<A_Square> &field,
                                     A_Square &start, A_Square &end, int w);
} // namespace Johnny

#endif // MATHEMATICS_H_INCLUDED
