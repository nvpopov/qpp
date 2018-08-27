#ifndef _QPP_AABB_H
#define _QPP_AABB_H

#include <ostream>
#include <geom/lace3d.hpp>
#include <cmath>


namespace qpp{
  const uint DIM_RECT = 3;

  /// 3d axis aligned bounding box
  template<typename REAL = float>
  struct aabb_3d {
      vector3<REAL> max;
      vector3<REAL> min;

      aabb_3d<REAL>& operator=(const aabb_3d<REAL>& other){
        max = other.max;
        min = other.min;
      }

      ///
      /// \brief squared_dist_point_check
      /// \param pn
      /// \param bmin
      /// \param bmax
      /// \return
      ///
      REAL squared_dist_point_check(const REAL pn,
                                    const REAL bmin,
                                    const REAL bmax){
        REAL out = 0; REAL v = pn;
        if ( v < bmin ){ REAL val = (bmin - v); out += val * val; }
        if ( v > bmax ){ REAL val = (v - bmax); out += val * val; }
        return out;
      }

      ///
      /// \brief center
      /// \return
      ///
      vector3<REAL> center(){
        return (max+min)*0.5;
      }

      ///
      /// \brief squared_dist_point
      /// \param point
      /// \return
      ///
      REAL squared_dist_point(const vector3<REAL> point){
        REAL sq = 0.0;
        for(int i = 0; i < DIM_RECT; i++)
          sq += squared_dist_point_check( point[i], min[i], max[i] );
        return sq;
      }

      ///
      /// \brief test_aganist_sphere
      /// \param fSphRad
      /// \param vSphCnt
      /// \return
      ///
      bool test_sphere(const REAL fSphRad,
                               const vector3<REAL> vSphCnt){
        return squared_dist_point(vSphCnt) <= (fSphRad * fSphRad);
      }

      ///
      /// \brief fill_guess
      /// \param _fGuessVal
      ///
      void fill_guess(const REAL _fGuessVal){
        for (unsigned int i = 0; i < DIM_RECT; i++){
            this->min[i] = -_fGuessVal / 2;
            this->max[i] =  _fGuessVal / 2;
          }
      }

      ///
      /// \brief fill_guess_with_shift
      /// \param _fGuessVal
      /// \param shift
      ///
      void fill_guess_with_shift(const REAL _fGuessVal,
                                 const vector3<REAL> vShift){
        for (unsigned int i = 0; i < DIM_RECT; i++){
            this->min[i] = (-_fGuessVal / 2) + vShift[i];
            this->max[i] = ( _fGuessVal / 2) + vShift[i];
          }
      }

      ///
      /// \brief split
      /// \param nl
      /// \param nh
      /// \param iAxis
      ///
      void split(aabb_3d<REAL> &nl,
                 aabb_3d<REAL> &nh,
                 const int iAxis = 0){
        for (uint i = 0; i < DIM_RECT; i++){
            REAL fMidPoint = (max[i] - min[i]) /2 ;
            nl.min[i] =  min[i];
            if (i == iAxis){
                nl.max[i] = nl.min[i] + fMidPoint;
                nh.min[i] = nl.min[i] + fMidPoint;
                nh.max[i] = nl.max[i] + fMidPoint;
              }
            else {
                nl.max[i] = nl.min[i] + fMidPoint * 2;
                nh.min[i] = nl.min[i] ;
                nh.max[i] = nl.max[i];
              }
          }
      }

      ///
      /// \brief volume
      /// \return
      ///
      REAL volume(){
        REAL _ret = 1.0;
        for (uint i = 0 ; i < DIM_RECT; i++) _ret *= (max[i] - min[i]);
        return _ret;
      }

      ///
      /// \brief rtree_box_nd
      ///
      aabb_3d(){
        for (unsigned int i = 0; i < DIM_RECT; i++){
            max[i] = 0.0f;
            min[i] = 0.0f;
          }
      }

      //void split()
  };

  template<typename REAL = float>
  std::ostream& operator << (std::ostream& stream,
                             aabb_3d<REAL> &nh) {
    stream << "[ rmin = {";
    for (unsigned int i = 0; i < DIM_RECT; i++)
      stream << nh.min[i] << ",";
    stream << "} rmax ={";
    for (unsigned int i = 0; i < DIM_RECT; i++)
      stream << nh.max[i] << ",";
    stream << "} ]";
    return stream;
  }
}

#endif
