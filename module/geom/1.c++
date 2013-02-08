#include <iostream>
#include <string>
#include <geom/geom.hpp>
#include <lace/lace3d.hpp>
#include <cmath>

int main()
{
//   lace::vector3d<double> v1(1.0,0,0), v2(0,1,0), v3(0,0,1);
//   qpp::geometry<std::string,3> g(v1,v2,v3);
//   qpp::geometry<std::string,3>::index i(0,3,4,5);


//   g.add("Li",0,0,0);
//   g.add("Cl",.5,.5,0);

//   std::cout << g.r_atom(0) << "\n";
//   std::cout << g.r_atom(1) << "\n";

//   i = qpp::geometry<std::string,3>::index(1,2,2,2);

//   std::cout << g.atom(i.atom()) << g.r(i) << "\n";
//   i.setatom(1);
//   std::cout << g.atom(i.atom()) << g.r(1) << "\n";

  //  while(1) i++;

  typedef lace::vector3d<double> vec;
  typedef lace::matrix3d<double> mtr;  

//   double pi = std::atan(1e0)*4;

//   qpp::rotrans<double> 
//     A( vec(0,0,.5) ), 
//     B( RotMtrx(vec(0,0,1), pi*2/3) );

  lace::vector3d<double> v1(1,1,0), v2(0,1,1), v3(1,0,1);
  qpp::geometry<3> g(v1,v2,v3);

  vec f = g.frac2cart( vec(1.122,2.133,3.678) );
  std::cout << f << "\n";

  std::cout << g.cart2frac(f) << "\n";

}


