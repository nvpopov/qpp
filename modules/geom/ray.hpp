#ifndef QPP_RAY_H
#define QPP_RAY_H
#include <geom/lace3d.hpp>
#include <cmath>

namespace qpp{
  template <typename REAL>
  struct ray_t {
      vector3<REAL> start;
      vector3<REAL> dir;

      ///
      /// \brief ray
      ///
      ray_t(){
        start = vector3<REAL>(0.0, 0.0, 0.0);
        dir = vector3<REAL>(0.0, 1.0, 0.0);
      }

      ///
      /// \brief ray
      /// \param _start
      /// \param _dir
      ///
      ray_t(const vector3<REAL> _start, const vector3<REAL> _dir){
        start = _start; dir = _dir.normalized();
      }

  };
}
#endif
