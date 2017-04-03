#include <geom/xgeom.hpp>
#include <iostream>

int main()
{
  qpp::xgeometry<0,double, qpp::periodic_cell<0,double> > g(1,1,1,"g1");
  g.field_names({"charge","number","hren"});

  g.add("C",{0,0,0},{-0.4},{6},{true});
  g.add("H",{1,0,0},{0.1},{1},{false});

  g.xfield<double>(0,0) = -0.44444;
  g.xfield<int>(0,1) = 33;

  g.write(std::cout);

  std::cout << g.xfield<bool>(0,0) << std::endl;
}

