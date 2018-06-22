#include <iostream>
#include <geom/geom.hpp>
#include <data/ptable.hpp>
#include <io/vasp_io.hpp>

template<int N>
struct Fact{
  static const int value = N * Fact<N-1>::value;
};

template<>
struct Fact<0>{
  static const int value = 1;
};

int main(){
  qpp::periodic_cell<double> cell({4,0,0},{0,6,0},{0,0,4});

  qpp::geometry<double,decltype(cell)> g(cell);

  g.add("Carbon",       -1.676283510,      0.000000000,      1.911126199);
  g.add("Oxygen",       -1.753146399,      1.141923181,      1.514919538);
  g.add("Oxygen",       -1.604477009,     -1.066694960,      1.079653080);
  g.add("Hydrogen",       -1.628395866,     -0.711301327,      0.174843873);
  g.add("Coronium",       0,5,0);
  g.add("Carbon",       -1.647886655,     -0.422100383,      3.375898205);
  g.add("Hydrogen",       -2.475776531,     -1.122649475,      3.538396631);
  g.add("Coronium",       0,0,0);
  g.add("Newtonium",      0,0,0);
  g.add("Hydrogen",       -2.565816675,      1.205870339,      4.156284306);
  g.add("Hydrogen",       -0.956315270,      1.314146931,      4.156322052);
  g.add("Hydrogen",       -0.733613146,     -1.005425023,      3.538407817);
  g.insert(6, "Nitrogen",       -1.721124037,      0.666230718,      4.332560746);

  g.shadow(0,true);
  g.shadow(1,true);  

  g.build_type_table();

  std::cout << " --- Atomic types: ---\n";
  
  for (int i=0; i<g.n_atom_types(); i++)
    std::cout << i << " = " << g.atom_of_type(i) << "\n";

  for ( qpp::iterator I(qpp::index::D(3).all(-1),qpp::index::D(3).all(1));
        !I.end(); I++)
    for (int at=0; at<g.nat(); at++)
      std::cout << g.atom(at) << " " << at << " " << I << " " << g.r(at,I) << "\n";

  std::cout << "--- Source geom: ---\n";
  std::vector<qpp::datum> v = {"Chugunium",11.,12.,13.};
  g.set_fields(-1,v);

  for (int at=0; at<g.nat(); at++){
      g.get_fields(at,v);
      for (int j=0; j<v.size(); j++)
	std::cout << v[j] << " ";
      std::cout << "\n";
    }
  
  /* 
  std::cout<<qpp::ptable::symbol_by_number(2)<<std::endl;
  std::cout<<Fact<4>::value <<std::endl;

  qpp::periodic_cell<double> cell2({1,0,0},{0,1,0},{0,0,1});
  qpp::geometry<double, decltype(cell2)> g2(cell2);

  qpp::periodic_cell<double> cell3({1,0,0},{0,1,0},{0,0,1});
  qpp::geometry<double, decltype(cell3)> g3(cell3);

  std::ifstream poscar("../examples/io/ref_data/La44F148.POSCAR");
  std::ifstream outcar("/home/nvpopov/work/python-playground/potfit_md/mddata"
                       "/laf3_v1.OUTCAR");

  std::vector<qpp::geometry<double,qpp::periodic_cell<double>>* > geom_l;
  std::vector<std::vector<qpp::vector3d<double> > >vel_l;
  std::vector<double> toten;
  std::vector<double> kin_t;

  qpp::read_vasp_poscar(poscar, g2);
  qpp::read_vasp_outcar_md(outcar, geom_l, vel_l, toten, kin_t);
  std::cout << g2.nat() << std::endl;
  std::cout << g2.cell << std::endl;

  std::cout << geom_l[111]->cell << std::endl;
  std::cout << geom_l[1491]->atom(0) << geom_l[1491]->r(0) << std::endl;
  std::cout << "force test = " << vel_l[0][0] << std::endl;

  std::cout << "total en num " << toten.size() << std::endl;
  std::cout << "temp num " << kin_t.size() << std::endl;
  */
}

