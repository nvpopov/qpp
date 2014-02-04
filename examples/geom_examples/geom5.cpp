#include <geom/zmt.hpp>
#include <io/geomio.hpp>
#include <stdlib.h>     /* srand, rand*/
#include <time.h>       /* time */

int main()
{
  /*
  qpp::zmatrix<double> z;
  qpp::geometry<std::string,0,double> g;

  z.add(qpp::zmt_record<double>("Ca"));
  z.add(qpp::zmt_record<double>("F", 0,2.39));
  z.add(qpp::zmt_record<double>("F", 0,2.39, 1, 109.47));
  z.add(qpp::zmt_record<double>("F", 0,2.39, 1, 109.47, 2, 120));
  z.add(qpp::zmt_record<double>("F", 0,2.39, 1, 109.47, 2, 240));
  z.add(qpp::zmt_record<double>("F", 0,2.39, 1, 180, 2,0));
  z.add(qpp::zmt_record<double>("F", 0,2.39, 2, 180, 3,0));
  z.add(qpp::zmt_record<double>("F", 0,2.39, 3, 180, 2,0));
  z.add(qpp::zmt_record<double>("F", 0,2.39, 4, 180, 2,0));

  //z.write(std::cout);
  z.zmt2cart(g);
  write_xyz(std::cout,g);
  */
  qpp::zpattern<0,double> z;
  z.add(qpp::zpt_record<double>("C",2.0));
  z.add(qpp::zpt_record<double>("C").bond(0, 1.3,1.5));
  z.add(qpp::zpt_record<double>("C").bond(0, 1.3,1.5).angle(1, 105.0, 115.0));
  z.add(qpp::zpt_record<double>("C").bond(0, 1.3,1.5).angle(1, 105.0, 115.0).dyhedral(2,115.0, 125.0));
  z.write(std::cout);
  
  qpp::zmatrix<> *zm = & z.average();
  zm -> write(std::cout);

  qpp::geometry<0> g;
  zm -> zmt2cart(g);
  write_xyz(std::cout,g);
  
  g.coord(2) = lace::vector3d<double>(1.115570,     0.000000,    -0.478828);

  std::cout << 0 << " " << z(0).comply(g.atom(0)) << "\n";
  std::cout << 1 << " " << z(1).comply(g.atom(1), g.coord(1), g.coord(z(1).at1)) << "\n";
  std::cout << 2 << " " << z(2).comply(g.atom(2), g.coord(2), g.coord(z(2).at1), g.coord(z(2).at2)) << "\n";
  for (int i=3; i<z.size(); i++)
    std::cout << i << " " << z(i).comply(g.atom(i), g.coord(i), g.coord(z(i).at1), g.coord(z(i).at2), g.coord(z(i).at3)) << "\n";

}

