#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>
#include <boost/format.hpp>

#include<geom/geom.hpp>
#include<constants.hpp>

// periodic_cell examples

using namespace qpp;

int main()
{
  periodic_cell<3> fcc(1,1,1,pi/3,pi/3,pi/3);

  for (int i=0; i<3; i++)
    std::cout << fcc(i) << "\n";

  fcc(0) = lace::vector3d<double>(0,1,1);
  fcc(1) = lace::vector3d<double>(1,0,1);
  fcc(2) = lace::vector3d<double>(1,1,0);

  lace::vector3d<double> r(2,0,0);

  std::cout << "cartesian r=" << r << " => fractional f=" << fcc.cart2frac(r) << "\n"; 

  r.set(.5,.5,.5);

  std::cout << "fractional f=" << r << " => cartesian r=" << fcc.frac2cart(r) << "\n"; 
  
}

