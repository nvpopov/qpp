#include <iostream>
#include <fstream>
#include <geom/geom.hpp>
#include <io/geomio.hpp>
#include <boost/format.hpp>			
#include <geom/zmt.hpp>
#include <time.h>
#include <stdlib.h>

// -------------- Pattern matching mechanism ---------------------

int main()
{
  qpp::geometry<3> g;
  std::ifstream inp("si.xyz");
  qpp::read_xyz(inp,g);
  
  //  qpp::write_xyz(std::cout,g);
  //  g.cell.write(std::cout);
  //  g.write(std::cout);

  g.default_ngbr_distance = 2.4;
  g.build_type_table();
  g.build_ngbr_disttable();
  g.build_ngbr_table();

  /*
  for (int i=0; i<g.size(); i++)
    for (int j=0; j<g.n_ngbr(i); j++)
      {
	qpp::index<3> k = g.ngbr_table(i,j);
	std::cout << g.atom(i) << " " << i << " " << g.atom(k) << " " << k << " " <<  norm(g.coord(i) - g.full_coord(k)) << "\n";
      }
  */

  qpp::zpattern<3> z;
  z.add(qpp::zpt_record<double>("Si",2.4));
  z.add(qpp::zpt_record<double>("Si").bond(0, 1.2,1.4));
  z.add(qpp::zpt_record<double>("Si").bond(0, 1.9,2.1).angle(1, 90.0, 110.0));
  z.add(qpp::zpt_record<double>("Si").bond(0, 1.9,2.1).angle(1, 140.0, 160.0).dyhedral(2,160.0, 180.0));

  srand (time(NULL));
  qpp::random_integer_lister lst;
  z.match(g,lst);

  for (int i=0; i< z.size(); i++)
    g.atom(z.bound(i)) = "N";

  qpp::write_xyz(std::cout,g);
}
