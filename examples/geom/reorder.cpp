#include <iostream>
#include <geom/geom.hpp>
#include <io/geomio.hpp>
#include <symm/autosymm.hpp>

using namespace qpp;

int main()
{

  geometry<double> g(0);

  g.add("C1", 1, 1, 1);
  g.add("C2", 1, 1, 0);
  g.add("C3", 1, 0, 0);
  g.add("C4", 0, 0, 0);

  geometry<double> g1(g);

  g1.reorder({2,0,3,1});

  /*
  write_xyz(std::cout,g);

  g.sort([](const geometry<double> & geom, int i)->double {return norm(geom.pos(i));});
  */
  
  g.coord(0)={1.1,1,1};

  write_xyz(std::cout,g);

  write_xyz(std::cout,g1);

  std::vector<int> ord;

  std::cout << " equiv= " << equiv_geoms(ord,g1,g,.15) << "\n";
  
  for (int i=0; i<ord.size(); i++)
    std::cout << "g[" << i << "] == g1[" << ord[i] << "]\n";

}
