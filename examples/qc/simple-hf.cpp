#include <fmt/format.h>
#include <iostream>
#include <string>
#include <vector>
#include <Eigen/Dense>
#include <libint2.hpp>
#include <qc/mtable.hpp>
#include <qc/epotnuc.hpp>
#include <consts.hpp>
#include <cstdlib>
#include <ctime>

using namespace qpp;

int main(){

  qpp::geometry<double> water(0);
  water.add("H",0.757*ang_to_bohr, 0.586*ang_to_bohr, 0.0*ang_to_bohr);
  water.add("H",-0.757*ang_to_bohr, 0.586*ang_to_bohr, 0.0*ang_to_bohr);
  water.add("O",0.0*ang_to_bohr,0.0*ang_to_bohr,0.0*ang_to_bohr);

  std::cout<<fmt::format("Epotnuc = {}\n", qpp::epotnuc(water));

}
