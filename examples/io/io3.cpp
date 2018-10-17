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

  qpp::read_vasp_outcar_md(outcar, geom_l, vel_l, toten, kin_t);


//  std::cout << "av_displ = " << qpp::average_displacement_for_atom(geom_l, 1)
//            << std::endl;

//  std::cout << "vl_autoc_f_t = "
//            << qpp::velocity_autocor_func_t<double>(vel_l, 10, 2)
//            << std::endl;

  /*for (int i = 1; i < 100; i++){
      std::cout<< fmt::format(
                    "{:4} {:10.8f}", i,
                    qpp::velocity_autocor_func_t<double>(vel_l, i, 64))
               << std::endl;
    }*/

  std::vector<double> av = qpp::velocity_autocor_func(vel_l);
  for(int i = 0; i < av.size(); i++)
    std::cout<< fmt::format(
                  "{:4} {:10.8f}", i,
                  av[i])
             << std::endl;
}
