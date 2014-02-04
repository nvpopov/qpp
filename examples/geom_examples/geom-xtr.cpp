#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>
#include <boost/format.hpp>
#include<geom/atom.hpp>
#include<geom/geom.hpp>
#include<geom/molecule.hpp>
#include<io/molio.hpp>

using namespace qpp;

int main()
{
 
  qpp::xtr_geometry<qpp_atom*,3,double> G(true,3,1,1);


  G.add_point(new qpp::qpp_atom("Li",3),lace::vector3d<double>(1,0,0), .95, {1.1,2.2,3.3}, {11}, {false});
  G.add_point(new qpp::qpp_atom("Li",3),lace::vector3d<double>(1,1,0), -1.90, {-0.34, -0.35, -0.36}, {42}, {true});
  G.add_point(new qpp::classical_atom("Li_cl",3),1,1,1);

  G.insert_point(0,new qpp::qpp_atom("Li",3),    lace::vector3d<double>(0,0,0), 1.1, {2.2,3.3},{13},{false});
  G.write(std::cout);
  
}

