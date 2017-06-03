#ifndef _QPP_CINSTANCE_H
#define _QPP_CINSTANCE_H
#include <cmath>
#include <string>
#include <vector>
#include <symm/cell.hpp>
#include <geom/geom.hpp>
#include <geom/xgeom.hpp>
#include <qc/mtable.hpp>


template<typename REAL, typename GEOM>
class ComputeInstance
{
public:
  GEOM *molecule;
  std::vector<std::string> vMapAtomBasis;

  ComputeInstance(GEOM *_inGeom){
    molecule = _inGeom;
  }
};

#endif
