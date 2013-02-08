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
#include<geom/molecule.hpp>
#include<symm/shenflis.hpp>
#include<geom/molio.hpp>


int main()
{
  qpp::molecule<std::string,3,double> M;
  std::ifstream inp("si.xyz");

  read_xyz(inp, M);
  
  //  write_xyz(std::cout, geom);

  M.build_type_table();

  std::cout << "Type table:\n";
  for(int i=0; i < M.natm_types(); i++)
    std::cout << i << " " << M.atom_of_type(i) << "\n";

  std::cout << "\n\n";

  //  qpp::molecule<std::string,3,double>::index ii(14,-1,2,6);
  //  std::cout << ii << "\n";

  M.set_default_nbr_distance(0.0);
  M.nbr_distance("Si","Si") = 2.3;
  M.build_nbr_table();

  std::cout << "Nbr table:\n";
  for (int i=0; i < M.size(); i++)
    {
      std::cout << boost::format("%i %-4s %12.6f %12.6f %12.6f") % M.atm_type_table(i) % M.atom(i) 
	% M.atom_coord(i)(0) % M.atom_coord(i)(1) % M.atom_coord(i)(2);
      for (int j=0; j<M.nnbr(i); j++)
	std::cout << " " << M.nbr_table(i,j);
      std::cout << "\n";
    }
}

