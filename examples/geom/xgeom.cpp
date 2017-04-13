#include <geom/xgeom.hpp>
#include <iostream>

int main()
{
  qpp::periodic_cell<double> cl(0);
  qpp::xgeometry<double, qpp::periodic_cell<double> > g(cl,1,1,1,0,"g1");
  g.set_fields({"charge","number","hren"},{qpp::type_real,qpp::type_int,qpp::type_bool});

  g.add("C",{0,0,0},{-0.4},{6},{true});
  g.add("H",{1,0,0},{0.1},{1},{false});

  g.xfield<double>(0,0) = -0.44444;
  g.xfield<int>(0,1) = 33;

  g.write(std::cout);

  std::cout << g.xfield<bool>(0,0) << std::endl;
}

