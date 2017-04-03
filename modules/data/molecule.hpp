#ifndef _QPP_MOLECULE_H
#define _QPP_MOLECULE_H

#include <data/atom.hpp>
#include <classic/potentials.hpp>

namespace qpp{

  template< int DIM, class REAL, class CELL>
  class molecule{
  public:
    CELL * cell;
    geometry<DIM,REAL,CELL> * geom;
    std::vector<qpp_atom<FREAL>*> atoms;

  };

};

#endif
