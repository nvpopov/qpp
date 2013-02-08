#include <iostream>
#include <string>
#include <geom/geom.hpp>

int main()
{
  lace::vector3d<double> v1(1.0,0,0), v2(0,1,0), v3(0,0,1);
  qpp::geometry<qpp::empty_atom,3,double> g555(v1,v2,v3);


  g555.add(qpp::empty_atom(),0,0,0);
  g555.add(qpp::empty_atom(),.5,.5,0);

  qpp::geometry<qpp::empty_atom,3,double>::iterator i(g555);

//   i = qpp::geometry<std::string,3>::index(3,3,5,6);

//   std::cout << (i == qpp::geometry<std::string,3>::index(3,4,5,6)) << "\n";
//   std::cout << (i != qpp::geometry<std::string,3>::index(3,4,5,6)) << "\n";

//   std::cout << i.begin().atom() << " " << i.begin().cell(0) << " " << i.begin().cell(1) << " " << i.begin().cell(2) << "\n";
//   std::cout << i.end().atom() << " " << i.end().cell(0) << " " << i.end().cell(1) << " " << i.end().cell(2) << "\n";

  for ( i=i.begin(); i != i.end(); i++)
    std::cout << i.atom() << " " << i.cell(0) << " " << i.cell(1) << " " << i.cell(2) << "\n";
  
}
