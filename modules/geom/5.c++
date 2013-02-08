#include <iostream>
#include <ostream>
#include <string>
#include <geom/geom.hpp>
#include <lace/lace3d.hpp>
#include <cmath>

void writexyz(qpp::geometry<3> &g, std::ostream &s)
{
  s << g.size() << "\n\n";
  for (int i=0; i < g.size(); i++)
    s << "si " << g.r(i).x() << " " << g.r(i).y() << " " <<  g.r(i).z() << "\n";
}


int main()
{
  typedef lace::vector3d<double> vec;
  typedef lace::matrix3d<double> mtr;  

  qpp::geometry<3> uc( vec(0,1,1), vec(1,0,1), vec(1,1,0) );
  uc.add( .25,  .25,  .25);
  uc.add(-.25, -.25, -.25);

  qpp::geometry<3> g;
  g = replicate(uc,4,4,4);
  
  writexyz(g,std::cout);
}
