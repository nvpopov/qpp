#include<iostream>
#include<geom/geom.hpp>

typedef lace::vector3d<double> vec3d;

int main()
{
  double pi = 3.14159265358979323844e0;
  qpp::periodic_cell<3> c(2,2,4,pi/2,pi/2,pi/3);



  std::cout << c.reduce_cntr(vec3d(2,2,2)) << "\n";

  qpp::periodic_cell<0> c0;
}
