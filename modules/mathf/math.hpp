#ifndef QPP_MATH_H
#define QPP_MATH_H

#include <algorithm>
#include <cmath>
#include <consts.hpp>

namespace qpp {

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
    return (deg * REAL(pi)) / 180;
  }

  template <class REAL>
  REAL rad2deg(REAL rad){
    return (rad * 180) / REAL(pi);
  }

  template <class REAL>
  inline REAL clamp(REAL val, REAL lo, REAL hi) {
      return std::max(lo, std::min(hi, val));
  }

  template <class REAL>
  inline bool cmp_eps(const REAL a, const REAL b){
    return std::fabs(a-b) <= std::numeric_limits<REAL>::epsilon() *
        std::max(1.0f, std::max(std::fabs(a), std::fabs(b)));
  }
}

#endif
