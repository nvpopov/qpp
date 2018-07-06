#include <fmt/format.h>
#include <iostream>
#include <fstream>
#include <geom/geom.hpp>
#include <io/geomio.hpp>


// -------------- Type table & neighbours table for simple molecule ---------------------

int main()
{
  qpp::geometry<double> g(3);
  std::ifstream inp("si.xyz");
  qpp::read_xyz(inp,g);
  g.build_type_table();
  
  //  qpp::write_xyz(std::cout,g);
  //g.cell->write(std::cout);
  //g.write(std::cout);

  qpp::bonding_table<double> bt;
  bt.default_distance = 2.6;

  //std::cout << "alive1\n";

  qpp::neighbours_table<double> ngbr(g,bt);

  ngbr.transl_mode=true;
  //ngbr.reference_mode = true;

  //std::cout << "alive2\n";

  //ngbr.build_disttable();

  //std::cout << "alive3\n";

  ngbr.build();

  //std::cout << "alive4\n";

  for (int i=0; i<g.size(); i++)
    for (int j=0; j<ngbr.n(i); j++){
	qpp::index k = ngbr.table(i,j);
	std::cout << g.atom(i) << " " << i << " " <<
		     g.atom(k) << " " << k << " " <<
		     (g.pos(i) - g.pos(k)).norm() << "\n";
      }
}
