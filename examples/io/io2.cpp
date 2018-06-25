#include <io/geomio.hpp>
#include <io/gulp_io.hpp>
#include <io/vasp_io.hpp>
#include <iostream>

int main(){
  std::ifstream gulp1("../examples/io/ref_data/caf2.ginp");
  qpp::periodic_cell<double> cell(3);
  qpp::geometry<double,decltype(cell)> g1(cell);
  qpp::read_gulp_simple_input(gulp1, g1);
  std::cout << g1.cell.v[0] << g1.cell.v[1] << g1.cell.v[0] << std::endl;

  for (int i = 0; i < g1.nat(); i++)
    std::cout << g1.atom(i) << " "<< g1.pos(i) << std::endl;


  std::ifstream gulp2("../examples/io/ref_data/baf2-va.ginp");
  qpp::periodic_cell<double> cell2(3);
  qpp::geometry<double,decltype(cell2)> g2(cell2);
  qpp::read_gulp_simple_input(gulp2, g2);
  std::cout << g2.cell.v[0] << g2.cell.v[1] << g2.cell.v[0] << std::endl;

  for (int i = 0; i < g2.nat(); i++)
    std::cout << g2.atom(i) << " "<< g2.pos(i) << std::endl;

  std::cout<<std::endl<<"Testing write_gulp_simple_input:"<<std::endl;
  qpp::write_gulp_simple_input(std::cout, g1);

  std::cout<<std::endl<<"Testing write_vasp_poscar:"<<std::endl;
  std::ifstream poscar("../examples/io/ref_data/La44F148.POSCAR");
  qpp::periodic_cell<double> cell3(3);
  qpp::geometry<double,decltype(cell3)> g3(cell3);
  qpp::read_vasp_poscar(poscar, g3);
  //g3.build_type_table();
  qpp::write_vasp_poscar(std::cout, g3);

}
