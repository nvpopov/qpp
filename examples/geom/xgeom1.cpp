#include <geom/xgeom.hpp>
#include <iostream>

using namespace qpp;

int main()
{
  
  periodic_cell<double> cl(0);

  xgeometry<double, periodic_cell<double> > 
    G(cl,
      {"atom",      "number","charge",   "x","y","z",                    "optx","opty","optz",            "fullname"},
      {type_string, type_int, type_real, type_real, type_real, type_real,type_bool, type_bool, type_bool, type_string },
      "Rich_geometry");

  G.xadd("H", 1, 0.3, 1.1, 2.2, 3.3, true, false, false, "Hydrogen");
  G.xadd("C", 7, 0.0, 4,5,6,         false, true, true, "Carbon");
  G.xadd("Nt", 0, 0.001, 56,67,78, false, false, false, "Newtonium");

  G.write(std::cout);

  G.xinsert(0, "U", 92, 4.4, 9,8,7, true, true, true, "Uranuim");
  G.erase(3);

  G.coord(1)(0) = 7;
  G.coord(1)(1) = 8;
  G.coord(1)(2) = 9;

  G.xfield<int>(1,2) = 77;

  G.xfield<bool>(6,0) = false;
  G.xfield<std::string>(9,0) = "BoooM!!!";

  G.add("H20", {-2.,-2.,-2.});
  G.xfill(3, "H2O", -1, 0.0, -2, 2, -2, true, true, true, "Rigid_H2O_molecule");

  G.write(std::cout);

  std::cout << "1st atom charge= " << G.charge(0) << std::endl;
  std::cout << "2nd atom charge= " << G.number(1) << std::endl;

  std::cout << G.xfield<std::string>("fullname",3) << "\n";
}