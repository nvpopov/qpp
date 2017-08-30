#ifndef _QPP_MATH_H
#define _QPP_MATH_H

#include <cmath>

namespace qpp{

  template <class REAL>
  int floor(REAL x)
  { return std::floor(x); }

  template <class REAL>
  int ceil(REAL x)
  { return std::ceil(x); }

  template <class REAL>
  int round(REAL x)
  {
    return floor(x+0.5);
  }

};

#endif
