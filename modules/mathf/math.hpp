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
  int round(REAL x){
    return floor(x+0.5);
  }

  template <class REAL>
  REAL deg2rad(REAL deg){
    return (deg * M_PI) / 180;
  }

  template <class REAL>
  REAL rad2deg(REAL rad){
    return (rad * 180) / M_PI;
  }

}

#endif
