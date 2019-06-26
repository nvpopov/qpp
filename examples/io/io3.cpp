#include <io/geomio.hpp>
#include <io/gulp_io.hpp>
#include <io/vasp_io.hpp>
#include <iostream>
#include <compute/analysis/dynamic_properties.hpp>
//#include <io/cp2k.hpp>

int main(){
  std::ifstream outcar("/home/nvpopov/work/python-playground/potfit_md/mddata"
                       "/laf3_v1.OUTCAR");

  std::vector<qpp::geometry<double,qpp::periodic_cell<double>>* > geom_l;
  std::vector<std::vector<qpp::vector3<double> > > vel_l;
  std::vector<double> toten;
  std::vector<double> kin_t;

}
