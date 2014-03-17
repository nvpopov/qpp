#include <iostream>
#include <fstream>
#include <geom/geom.hpp>
#include <io/geomio.hpp>
#include <boost/format.hpp>

// -------------- Type table & neighbours table for simple molecule ---------------------

int main()
{
  qpp::geometry<3> g;
  std::ifstream inp("si.xyz");
  qpp::read_xyz(inp,g);
  
  //  qpp::write_xyz(std::cout,g);
  g.cell.write(std::cout);
  g.write(std::cout);

  g.ngbr.default_distance = 2.6;
  g.build_type_table();
  g.ngbr.build_disttable();
  g.ngbr.build();

  for (int i=0; i<g.size(); i++)
    for (int j=0; j<g.ngbr.n(i); j++)
      {
	qpp::index<3> k = g.ngbr.table(i,j);
	std::cout << g.atom(i) << " " << i << " " << g.atom(k) << " " << k << " " <<  norm(g.coord(i) - g.full_coord(k)) << "\n";
      }
}