#include <geom/xgeom.hpp>
#include <iostream>

int main()
{
  qpp::periodic_cell<double> cl(0);
  qpp::xgeometry<double, qpp::periodic_cell<double> > g(0,"g1");
  g.set_fields({"charge","number","hren","mass","mult","word"},
	       {qpp::type_real,qpp::type_int,qpp::type_bool,qpp::type_real,qpp::type_int,qpp::type_string});

  for (int i=0; i<g.nfields(); i++)
    std::cout << i << " " <<  g.field_name(i) << " = " << g.field_type(i) << " idx= " << g._field_idx[i] <<"\n";
  std::cout << " atom " << g.ix_atom << " x " << g.ix_x << " y " << g.ix_y << " z " << g.ix_z <<
    " charge " << g.ix_charge << " number " << g.ix_number << " mass " << g.ix_mass << "\n";

  g.add("C",{0,0,0},{"carbon"},{-0.4,12.0},{6,2},{true});
  g.add("H",{1,0,0},{"hydrogen"},{0.1,1.0},{1,3},{false});
  g.xadd("O", 3., 4., 5., -1.2, 8, false, 16, 2, "oxygen");
  g.xadd("O", 8 , 6,  7, -1.2, 8, false, 16, 2, "oxygen");
  g.xadd("O", 8 , 6,  7, -1.2, 8, true, 16.3, 2, "hjhjhj");
  g.xinsert(3,"N", 11, 12, 13, -.6, 7, true, 14, 1, "nitrogen");

  /*  
  g.xfield<double>(4,0) = -.3333333;
  std::cout << " f40= " <<  g.xfield<double>(4,0) << "\n";

  g.xfield<double>(1,0) = -0.44444;
  g.xfield<int>(5,1) = 33;
  
  g.xfield<double>("x",0) = -111.111;
  std::cout << "asdasd= " << g.xfield<bool>("hren",0) << "\n";
  */

  g.write(std::cout);

  //  std::cout << g.xfield<bool>(6,1) << std::endl;
}

