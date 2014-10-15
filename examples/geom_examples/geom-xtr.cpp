#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>
#include <boost/format.hpp>
#include<geom/atom.hpp>
#include<geom/geom.hpp>
#include<geom/geom_extras.hpp>
//#include<geom/molecule.hpp>
//#include<io/molio.hpp>

using namespace qpp;

int main()
{
 
  qpp::xtr_geometry<3,double> G(4,1,1);

  G.xreal_name(0)="charge";

  G.add("Li",lace::vector3d<double>(1,0,0), {.95, 1.1,2.2,3.3}, {11}, {false});
  G.add("Li",lace::vector3d<double>(1,1,0), {-1.90, -0.34, -0.35, -0.36}, {42}, {true});
  G.add("Li_cl",1,1,1);

  G.insert(0, "Li", lace::vector3d<double>(0,0,0), {1.1, 2.2,3.3},{13},{false});
  G.erase(G.nat()-1);

  G.insert(G.nat(),"F_shl",lace::vector3d<double>(1,1,1),{-1,4,5,6},{7},{true});
  G.add("Cl",lace::vector3d<double>(2,1,1));


  G.write(std::cout);
  
}

