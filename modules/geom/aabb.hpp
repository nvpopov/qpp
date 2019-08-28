#ifndef QPP_AABB_H
#define QPP_AABB_H

#include <ostream>
#include <geom/lace3d.hpp>
#include <cmath>


namespace qpp {

  const uint8_t DIM_RECT = 3;

  /// 3d axis aligned bounding box
  template<typename REAL = float>
  struct aabb_3d_t {

      vector3<REAL> max;
      vector3<REAL> min;

      aabb_3d_t<REAL>& operator=(const aabb_3d_t<REAL>& other) {
        max = other.max;
        min = other.min;
        return *this;
      }

      void shift(const vector3<REAL> &shift) {
        min += shift;
        max += shift;
      }

      const aabb_3d_t<REAL> shifted(const vector3<REAL> &shift) {
        aabb_3d_t<REAL> res_aabb = *this;
        res_aabb.shift(shift);
        return res_aabb;
      }

      /// \brief squared_dist_point_check
      /// \param pn
      /// \param bmin
      /// \param bmax
      /// \return
      REAL squared_dist_point_check(const REAL pn,
                                    const REAL bmin,
                                    const REAL bmax) {

        REAL out = 0; REAL v = pn;
        if ( v < bmin ){ REAL val = (bmin - v); out += val * val; }
        if ( v > bmax ){ REAL val = (v - bmax); out += val * val; }
        return out;

      }

      /// \brief center
      /// \return
      vector3<REAL> center() {
        return (max+min)*0.5;
      }

      /// \brief squared_dist_point
      /// \param point
      /// \return
      REAL squared_dist_point(const vector3<REAL> point) {

        REAL sq = 0.0;
        for(int i = 0; i < DIM_RECT; i++)
          sq += squared_dist_point_check( point[i], min[i], max[i] );
        return sq;

      }

      /// \brief test_aganist_sphere
      /// \param fSphRad
      /// \param vSphCnt
      /// \return
      bool test_sphere(const REAL sph_r,
                       const vector3<REAL> sph_cnt) {
        return squared_dist_point(sph_cnt) <= (sph_r * sph_r);
      }

      bool test_point(const vector3<REAL> test_point) {

        for(int i = 0; i < DIM_RECT; i++)
          if (min[i] > test_point[i]) return false;

        for(int i = 0; i < DIM_RECT; i++)
          if (max[i] < test_point[i]) return false;

        return true;

      }

      /// \brief fill_guess
      /// \param _fGuessVal
      void fill_guess(const REAL _guess_val) {

        for (unsigned int i = 0; i < DIM_RECT; i++) {
            this->min[i] = -_guess_val / 2;
            this->max[i] =  _guess_val / 2;
          }

      }

      /// \brief fill_guess_with_shift
      /// \param _fGuessVal
      /// \param shift
      void fill_guess_with_shift(const REAL guess_value,
                                 const vector3<REAL> shift) {

        for (unsigned int i = 0; i < DIM_RECT; i++) {
            this->min[i] = (-guess_value / 2) + shift[i];
            this->max[i] = ( guess_value / 2) + shift[i];
          }

      }

      /// \brief split
      /// \param nl
      /// \param nh
      /// \param iAxis
      void split(aabb_3d_t<REAL> &nl,
                 aabb_3d_t<REAL> &nh,
                 const int iAxis = 0) {

        for (uint8_t i = 0; i < DIM_RECT; i++) {
            REAL mid_point = (max[i] - min[i]) / 2 ;
            nl.min[i] =  min[i];
            if (i == iAxis) {
                nl.max[i] = nl.min[i] + mid_point;
                nh.min[i] = nl.min[i] + mid_point;
                nh.max[i] = nl.max[i] + mid_point;
              }
            else {
                nl.max[i] = nl.min[i] + mid_point * 2;
                nh.min[i] = nl.min[i] ;
                nh.max[i] = nl.max[i];
              }
          }

      }

      /// \brief volume
      /// \return
      REAL volume() {

        REAL _ret = 1.0;
        for (uint8_t i = 0 ; i < DIM_RECT; i++) _ret *= (max[i] - min[i]);
        return _ret;

      }

      /// \brief rtree_box_nd
      aabb_3d_t() {

        for (unsigned int i = 0; i < DIM_RECT; i++) {
            max[i] = 0.0f;
            min[i] = 0.0f;
          }

      }

      aabb_3d_t(const REAL x1, const REAL y1, const REAL z1,
                const REAL x2, const REAL y2, const REAL z2) {
        min[0] = x1; min[1] = y1; min[2] = z1;
        max[0] = x2; max[1] = y2; max[2] = z2;
      }

      aabb_3d_t(const vector3<REAL> &ctr_min, const vector3<REAL> &ctr_max) {
        min[0] = ctr_min[0]; min[1] = ctr_min[1]; min[2] = ctr_min[2];
        max[0] = ctr_max[0]; max[1] = ctr_max[1]; max[2] = ctr_max[2];
      }

      aabb_3d_t(const vector3<REAL> &shift,
                const REAL x1, const REAL y1, const REAL z1,
                const REAL x2, const REAL y2, const REAL z2) {

        min[0] = x1; min[1] = y1; min[2] = z1;
        max[0] = x2; max[1] = y2; max[2] = z2;
        min += shift;
        max += shift;

      }

      //void split()
  };

  template<typename REAL = float>
  std::ostream& operator << (std::ostream& stream,
                             aabb_3d_t<REAL> &nh) {
    stream << "[ rmin = {";
    for (unsigned int i = 0; i < DIM_RECT; i++)
      stream << nh.min[i] << ",";
    stream << "} rmax ={";
    for (unsigned int i = 0; i < DIM_RECT; i++)
      stream << nh.max[i] << ",";
    stream << "} ]";
    return stream;
  }

} //namespace qpp

#endif
