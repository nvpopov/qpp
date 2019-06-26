#ifndef QPP_INTERSECTIONS_H
#define QPP_INTERSECTIONS_H
#include <geom/lace3d.hpp>
#include <geom/aabb.hpp>
#include <geom/ray.hpp>
#include <mathf/math.hpp>
#include <cmath>

namespace qpp {

  ///
  /// \brief ray_sphere_test
  /// \param _ray
  /// \param vCenter
  /// \param fRadius
  /// \return
  ///
  template <typename REAL>
  REAL ray_sphere_test(ray_t<REAL> *_ray,
                       const vector3<REAL> sph_center,
                       const REAL sph_r){
    REAL a = _ray->dir.dot(_ray->dir);
    vector3<REAL> s0_r0 = _ray->start - sph_center;
    REAL b = 2.0f * _ray->dir.dot(s0_r0);
    REAL c = s0_r0.dot(s0_r0) - (sph_r * sph_r);
    if (b*b - 4.0*a*c < 0.0) return -1.0;
    return (-b - sqrt((b*b) - 4.0*a*c))/(2.0*a);
  }


  ///
  /// \brief ray_aabb_test
  /// \param _ray
  /// \param _aabb
  /// \return
  ///
  template <typename REAL>
  bool ray_aabb_test(ray_t<REAL> &_ray, aabb_3d_t<REAL> &_aabb){
    //if (!_ray || !_aabb) return false;
    REAL t1 = (_aabb.min[0] - _ray.start[0]) /
        (cmp_eps(_ray.dir[0], 0.0f) ? 0.00001f : _ray.dir[0]);

    REAL t2 = (_aabb.max[0] - _ray.start[0]) /
        (cmp_eps(_ray.dir[0], 0.0f) ? 0.00001f : _ray.dir[0]);

    REAL t3 = (_aabb.min[1] - _ray.start[1]) /
        (cmp_eps(_ray.dir[1], 0.0f) ? 0.00001f : _ray.dir[1]);

    REAL t4 = (_aabb.max[1] - _ray.start[1]) /
        (cmp_eps(_ray.dir[1], 0.0f) ? 0.00001f : _ray.dir[1]);

    REAL t5 = (_aabb.min[2] - _ray.start[2]) /
        (cmp_eps(_ray.dir[2], 0.0f) ? 0.00001f : _ray.dir[2]);

    REAL t6 = (_aabb.max[2] - _ray.start[2]) /
        (cmp_eps(_ray.dir[2], 0.0f) ? 0.00001f : _ray.dir[2]);

    REAL tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)),
                         std::min(t5, t6));
    REAL tmax = std::min(std::min( std::max(t1, t2),  std::max(t3, t4)),
                         std::max(t5, t6));

    if (tmax < 0) return false;

    if (tmin > tmax) return false;

    return true;

  }


  ///
  /// \brief aabb_aabb_test
  /// \param a
  /// \param b
  /// \return
  ///
  template <typename REAL>
  bool aabb_aabb_test(aabb_3d_t<REAL> *a, aabb_3d_t<REAL> *b){
    return
        (a->min[0] <= b->max[0] && a->max[0] >= b->min[0]) &&
        (a->min[1] <= b->max[1] && a->max[1] >= b->min[1]) &&
        (a->min[2] <= b->max[2] && a->max[2] >= b->min[2]);
  }

  template <typename REAL>
  bool point_aabb_test(const vector3<REAL> p, aabb_3d_t<REAL> &a){
    for (uint8_t i = 0; i < 3; i++)
      if (!((p[i] >= a.min[i]) && (p[i] <= a.max[i])))
        return false;
    return true;
  }
}
#endif
