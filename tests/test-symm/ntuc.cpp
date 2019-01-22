#include <symm/groups.hpp>
#include <symm/autosymm.hpp>
#include <symm/gen_cell.hpp>
#include <symm/cell.hpp>
#include <symm/group_theory.hpp>
#include <iostream>
#include <fmt/format.h>
#include <geom/xgeom.hpp>
#include <io/geomio.hpp>

using namespace qpp;

int main () {

  xgeometry<double, periodic_cell<double> > uc(3);
  std::ifstream uc_io("../examples/pyqpp/tysonite.uc");
  read_xyzq(uc_io, uc);
  std::cout << uc.cell.v[0].to_string_vec()
      << uc.cell.v[1].to_string_vec() << uc.cell.v[2].to_string_vec() << std::endl;
  array_group<rotrans<double,true> > cg;
  find_cryst_symm<double>(cg, uc, 0.0001);
}
