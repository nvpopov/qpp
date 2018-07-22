#ifndef _QPP_DYNAMIC_PROPS_H
#define _QPP_DYNAMIC_PROPS_H

#include <iostream>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <io/strfun.hpp>

#include <geom/lace3d.hpp>
//#include <lace/lace.hpp>
//#include <symm/symm.hpp>
#include <geom/geom.hpp>
#include <geom/xgeom.hpp>
#include <geom/ngbr.hpp>
//#include <geom/geom_extras.hpp>
//#include <geom/molecule.hpp>

#include <vector>
#include <cmath>
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>
#include <ios>
#include <algorithm>

namespace qpp {
  template<class REAL, class CELL>
  REAL average_displacement_for_atom(
      std::vector<geometry<REAL,CELL>* > &geom_list,
      const int atmIdx){
    REAL retval = 0.0f;
    for(size_t i = 1; i < geom_list.size() ; i++){
        qpp::vector3<REAL> dx =
            geom_list[i]->r(0) - geom_list[i]->r(atmIdx);
        REAL dx_n = dx.norm2();
        retval += dx_n;
      }
    return retval / geom_list.size();
  }

  template<class REAL>
  std::vector<REAL> velocity_autocor_func(
      const std::vector<std::vector<qpp::vector3<REAL> > > &vl,
      const int timeStep = 1){
    std::vector<REAL> retvec;
    int totalSteps = vl.size() / timeStep;
    int totalAtoms = vl[0].size();
    REAL dot00 = 0.0f;

    for(int i = 0; i < totalAtoms; i++){
        qpp::vector3<REAL> v0i = vl[0][i];
      dot00 += v0i.dot(v0i);
      }
    dot00 /= totalAtoms;

    for(int i = 0; i < vl.size(); i+= timeStep){

        REAL retval = 0.0f;

        for(int q =0; q < vl[i].size(); q++){
            qpp::vector3<REAL> v1 = vl[0][q];
            qpp::vector3<REAL> v2 = vl[i][q];
            retval += v1.dot(v2) / dot00;
          }

        retvec.push_back((retval/totalAtoms));

      }
    return retvec;

  }
}

#endif
