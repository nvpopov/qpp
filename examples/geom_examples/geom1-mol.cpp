#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>
#include <boost/format.hpp>
//#include<iostream>
//#include <istream>
//#include <string>
//#include <streambuf>
#include<geom/geom.hpp>
//#include<geom/molecule.hpp>
//#include<symm/shenflis.hpp>
//#include<io/molio.hpp>


int main()
{
  qpp::molecule<3,double> M("test");
  //  qpp::geometry<3,double> G;
  std::ifstream inp("si.xyz");

  /*M.add(qpp::qpp_atom("Li",3),lace::vector3d<double>(1,0,0));
  M.add(qpp::qpp_atom("Li",3),lace::vector3d<double>(1,1,0));
  M.add(qpp::classical_atom("Li_cl",3),lace::vector3d<double>(1,1,1));
  M.insert(0,qpp::qpp_atom("Li",3),lace::vector3d<double>(0,0,0));
  */


  qpp::xyz_molecule_input<3,double>(inp).read(M);

  std::cout << "after read\n";

  M.build_type_table();

  qpp::qpp_molecule_output<3,double>(std::cout).write(M);

  //  M.add(qpp::generic_atom("Li"),lace::vector3d<double>(1,0,0));
  //  M.add(qpp::generic_atom("Li"),lace::vector3d<double>(1,1,0));
  //  M.add(qpp::generic_atom("Li"),lace::vector3d<double>(1,1,1));
  //  M.insert(0,qpp::generic_atom("Li"),lace::vector3d<double>(0,0,0));

  //for (int i=0; i<M.size(); i++)
  //  std::cout << M.atom(i).info() << " " << M.coord(i) << "\n";
  //  read_xyz(inp, G);
  
  //  write_xyz(std::cout, G);

  //  M.build_type_table();

  //  std::cout << "Type table:\n";
  //for(int i=0; i < M.natom_types(); i++)
  //  std::cout << i << " " << M.atom_of_type(i).name << "\n";

  //std::cout << "\n\n";

  //  qpp::molecule<std::string,3,double>::index ii(14,-1,2,6);
  //  std::cout << ii << "\n";

  //  M.set_default_nbr_distance(0.0);
  //  M.nbr_distance("Si","Si") = 2.3;
  //  M.build_nbr_table();

  //  std::cout << "Nbr table:\n";
  //  for (int i=0; i < M.size(); i++)
  //    {
  //      std::cout << boost::format("%i %-4s %12.6f %12.6f %12.6f") % M.atm_type_table(i) % M.atom(i) 
  //	% M.atom_coord(i)(0) % M.atom_coord(i)(1) % M.atom_coord(i)(2);
  //    for (int j=0; j<M.nnbr(i); j++)
  //	std::cout << " " << M.nbr_table(i,j);
  //    std::cout << "\n";
      //  }
}

