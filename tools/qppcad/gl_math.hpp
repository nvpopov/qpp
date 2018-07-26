#ifndef _QPP_GLMATH_H
#define _QPP_GLMATR_H
#include <Eigen/Eigen>
#include <geom/lace3d.hpp>
#include <mathf/math.hpp>

namespace qpp{
  Eigen::Matrix4f gl_m_frustrum();

  template<typename REAL>
  matrix4<REAL> perspective( REAL fovy,
                             REAL aspect,
                             REAL zNear,
                             REAL zFar){
    assert(aspect > 0);
    assert(zFar > zNear);

    REAL radf = deg2rad(fovy);

    REAL tanHalfFovy = tan(radf / 2.0);
    matrix4<REAL> res = matrix4<REAL>::Zero();
    res(0,0) = 1.0 / (aspect * tanHalfFovy);
    res(1,1) = 1.0 / (tanHalfFovy);
    res(2,2) = - (zFar + zNear) / (zFar - zNear);
    res(3,2) = - 1.0;
    res(2,3) = - (2.0 * zFar * zNear) / (zFar - zNear);
    return res;
  }

  template<typename REAL>
  matrix4<REAL> lookAt(
      matrix4<REAL> const & camPos,
      matrix4<REAL> const & center,
      matrix4<REAL> const & up
      ){

    vector3<REAL> f = (center - camPos).normalized();
    vector3<REAL> u = up.normalized();
    vector3<REAL> s = f.cross(u).normalized();
    u = s.cross(f);

    matrix4<REAL> res;
    res <<  s.x(),s.y(),s.z(),-s.dot(camPos),
        u.x(),u.y(),u.z(),-u.dot(camPos),
        -f.x(),-f.y(),-f.z(),f.dot(camPos),
        0,0,0,1;

    return res;
  }

}

#endif
