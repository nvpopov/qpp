#include "basis/basis.hpp"

namespace qpp{

  qppobject_type qtype_bastype(qpp_bastype t)
  {
    switch(t)
      {
      case qbas_gauss: return qtype_basis_gauss;
      case qbas_slater: return qtype_basis_slater;
      case qbas_siesta: return qtype_basis_siesta;
      case qbas_pw: return qtype_basis_pw;
      case qbas_none: return 0;
      }
  }

};

