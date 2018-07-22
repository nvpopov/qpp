#include <fmt/format.h>
#include <iostream>
#include <symm/gcell.hpp>
#include <geom/lace3d.hpp>
#include <geom/geom.hpp>
#include <geom/builders.hpp>
#include <string>


using namespace qpp;

int main()
{
  auto C4 = RotMtrx<double>({0,0,1},pi/2);
  auto C3 = RotMtrx<double>({1,1,1},2*pi/3);
  auto C31 = RotMtrx<double>({1,-1,-1},2*pi/3);
  auto S6 = RotMtrx<double>({1,1,1},pi/3)*Sigma<double>({1,1,1});
  matrix3<double> Inv = matrix3<double>::Identity()*-1.0f;

  /*
  generalized_cell<4,double,decltype(C4)> G({C4,C3,C31,Inv});
  geometry<4,double,decltype(G)> geom(G);
  */
  generalized_cell<double,decltype(C4)> G({C4,S6});
  G.auto_orders();


  geometry<double,decltype(G)> geom(G);

  geom.auto_symmetrize = true;
  geom.auto_update_types = true;

  geom.default_symmetrize_radius = 1;

  geom.add("C", 0, 0.1, 1.);
  geom.add("H",1,2,3);

  geometry<double> geom2(0);
  replicate(geom2, geom, G, G.begin(), G.end(), crowd_exclude );

  std::cout << geom2.nat() << "\n\n";
  for (int at=0; at<geom2.nat(); at++)
      std::cout<<fmt::format("{} {:3.5f} {:3.4f}",
                             geom2.atom(at),
                             geom2.coord(at).x(),
                             geom2.coord(at).y())<<std::endl;
   /* std::cout << boost::format("%-2s %10.6f %10.6f %10.6f\n") % geom2.atom(at) %
      geom2.coord(at).x() % geom2.coord(at).y()  % geom2.coord(at).z(); */
}


