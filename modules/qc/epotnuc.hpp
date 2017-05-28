#ifndef _QPP_EPOTNUC_H
#define _QPP_EPOTNUC_H
#include <cmath>
#include <string>
#include <vector>
#include <symm/cell.hpp>
#include <geom/geom.hpp>
#include <geom/xgeom.hpp>
#include <qc/mtable.hpp>

namespace qpp {
  template< typename RETVAL, typename REAL>
  RETVAL epotnuc(geometry<REAL> &ingeom)
  {
    RETVAL enuc = 0.0f;
    for(auto i = 0; i<ingeom.nat(); i++)
      for(auto j = i+1; j<ingeom.nat(); j++)
        {
          REAL dx = ingeom.coord(i).x() - ingeom.coord(j).x();
          REAL dy = ingeom.coord(i).y() - ingeom.coord(j).y();
          REAL dz = ingeom.coord(i).z() - ingeom.coord(j).z();
          REAL rsq = dx*dx + dy*dy + dz*dz;
          REAL r = sqrt(rsq);
          std::cout<<get_atom_number_by_name(ingeom.atom(i))<<" "<<
                   get_atom_number_by_name(ingeom.atom(j)) << std::endl;
          enuc += (get_atom_number_by_name(ingeom.atom(i)) *
                   get_atom_number_by_name(ingeom.atom(j)))/r;
        }
    return enuc;
  }

  template< typename RETVAL, typename REAL>
  RETVAL epotnuc(qpp::xgeometry<REAL,periodic_cell<REAL>> &ingeom)
  {
    RETVAL enuc = 0.0f;
    for(auto i = 0; i<ingeom.nat(); i++)
      for(auto j = i+1; j<ingeom.nat(); j++)
        {
          REAL dx = ingeom.coord(i).x() - ingeom.coord(j).x();
          REAL dy = ingeom.coord(i).y() - ingeom.coord(j).y();
          REAL dz = ingeom.coord(i).z() - ingeom.coord(j).z();
          REAL rsq = dx*dx + dy*dy + dz*dz;
          REAL r = sqrt(rsq);
          std::cout<<ingeom.coord(i).x()<<" "<<
                     ingeom.coord(i).y()<<" "<<
                     ingeom.coord(i).z()<<" "<<
                      ingeom.charge(i)<<" "<<
                     ingeom.charge(j)<<std::endl;
          enuc += (ingeom.charge(i) *
                   ingeom.charge(j))/r;
        }
    return enuc;
  }
}
#endif
