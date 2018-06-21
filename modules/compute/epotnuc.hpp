#ifndef _QPP_EPOTNUC_H
#define _QPP_EPOTNUC_H
#include <cmath>
#include <string>
#include <vector>
#include <symm/cell.hpp>
#include <geom/geom.hpp>
#include <geom/xgeom.hpp>

/*
namespace qpp {
  template<typename REAL = double>
  REAL calc_geom_q1q2(geometry<REAL> &geom,int _i, int _j)
  {
    return(get_atom_number_by_name(geom.atom(_i))
           *get_atom_number_by_name(geom.atom(_j)));
  }

  template<typename REAL = double>
  REAL calc_geom_q1q2(xgeometry<REAL,periodic_cell<REAL>> &geom,
                      int _i, int _j)
  {
    return(geom.charge(_i)*geom.charge(_j));
  }

  template<typename REAL = double, typename GEOMTYPE>
  REAL epotnuc(GEOMTYPE &ingeom)
  {
    REAL enuc = 0.0f;
    #pragma omp parallel for shared(enuc)
    for(auto i = 0; i<ingeom.nat(); i++)
      for(auto j = i+1; j<ingeom.nat(); j++)
        {
          REAL dx = ingeom.r(i)(0) - ingeom.r(j)(0);
          REAL dy = ingeom.r(i)(1) - ingeom.r(j)(1);
          REAL dz = ingeom.r(i)(2) - ingeom.r(j)(2);
          REAL rsq = dx*dx + dy*dy + dz*dz;
          REAL r = sqrt(rsq);
          REAL _enuc = (calc_geom_q1q2(ingeom,i,j))/r;
          enuc += _enuc;
        }
    return enuc;
  }


}*/
#endif
