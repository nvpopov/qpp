#ifndef _QPP_GEOMANIP_H
#define _QPP_GEOMANIP_H

#include <geom/geom.hpp>
#include <geom/shape.hpp>

namespace qpp{

  enum{
    geomanip_fromcells = 0x001,
    geomanip_fromatoms = 0x002,

    geomanip_sumcharge = 0x004,
    geomanip_exclude   = 0x008,
    geomanip_merge     = 0x010
  };

  template< int DIM, class CREAL=double, class TRANSFORM = periodic_cell<DIM,CREAL> >
  void merge(geometry<DIM,CREAL,TRANSFORM> & g1, geometry<DIM,CREAL,TRANSFORM> & g2, 
	     int geomanip_opt = geomanip_merge, CREAL r_coincide = 0.1e0)
  {
    geometry<DIM,CREAL,TRANSFORM>::neighbours_table crowd(g1);
  }


};

#endif
