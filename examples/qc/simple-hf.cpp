#include <fmt/format.h>
#include <iostream>
#include <string>
#include <vector>
#include <Eigen/Dense>
#include <libint2.hpp>
#include <qc/mtable.hpp>
#include <qc/epotnuc.hpp>

using namespace qpp;

int main(){
  /*std::cout<<fmt::format("Samarium is Sm and {}\n",
                           get_atom_number_by_name("Sm"));*/
  qpp::geometry<double> water(0);
  water.add("H",          1.75524,       -0.03055,       -0.15305);
  water.add("H",          0.46128,        0.62257,        0.10589);
  water.add("O",         -0.74491,       -0.32028,       -0.01207);

  std::cout<<fmt::format("Test epotnuc for geo = {}\n",
                         qpp::epotnuc<double>(water));

  qpp::periodic_cell<double> cl(0);
  qpp::xgeometry<double, qpp::periodic_cell<double>> xwater(cl,
  {"atom","number","charge","x","y","z"},
  {type_string, type_int, type_real, type_real, type_real, type_real});
  xwater.xadd("H", 1 , 1, 1.75524,       -0.03055,       -0.15305);
  xwater.xadd("H", 1 , 1, 0.46128,        0.62257,        0.10589);
  xwater.xadd("O", 8 , 8,-0.74491,       -0.32028,       -0.01207);

  std::cout<<fmt::format("Test epotnuc for xgeo = {}\n",
                         qpp::epotnuc<double>(xwater));

}
