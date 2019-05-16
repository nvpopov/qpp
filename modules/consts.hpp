#ifndef QPP_CONSTS_H
#define QPP_CONSTS_H

#include<cmath>

namespace qpp {

  const auto pi = 3.141592653589793238463e0;
  const auto ang_to_bohr = 1.88973e0; // 1 Angstrom to 1 Bohr
  const auto bohr_to_angs = 1 / ang_to_bohr;
  const auto infty = HUGE_VALF;
  const auto def_isovalue_mo = 0.02; // (electrons/(bohr)^3)^2
  const auto def_isovalue_dens = 0.008; // electrons/(bohr)^3
  const auto hartree_to_ev = 27.211;

}

#endif
