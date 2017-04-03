#include <iostream>
#include <fstream>
#include <geom/geom.hpp>
#include <io/geomio.hpp>
#include <boost/format.hpp>

// -------------- Type table & neighbours table for simple molecule ---------------------

using namespace qpp;

int main()
{
  qpp::geometry<3,double> g;
  std::ifstream inp("si.xyz");
  qpp::read_xyz(inp,g);
  
  //  qpp::write_xyz(std::cout,g);
  //g.cell.write(std::cout);
  //write_xyz(std::cout,g);

  bonding_table<double> bt;
  bt.default_distance = 2.6;

  neighbours_table<3,double> ngbr(g,bt);  
  neighbours_table<3,double> rngbr(g,bt);  

  g.build_type_table();

  /*
  rngbr.build_disttable();
  rngbr.reference_mode = true;
  rngbr.build();

  std::cout << "Reference ngbr table:\n";
  for (int i=0; i<g.size(); i++)
    for (int j=0; j<rngbr.n(i); j++)
      {
	qpp::atom_index<3> k = rngbr.table(i,j);
	std::cout << g.atom(i) << " " << i << " " << g.atom(k) << " " << k.atom << k.cell << " " <<  norm(g.position(i) - g.position(k)) << "\n";
      }
  */
  ngbr.transl_mode = false;

  ngbr.build_disttable();
  ngbr.build();

  std::cout << "ngbr table:\n";
  for (int i=0; i<g.size(); i++)
    for (int j=0; j<ngbr.n(i); j++)
      {
	qpp::atom_index<3> k = ngbr.table(i,j);
	std::cout << g.atom(i) << " " << i << " " << g.atom(k) << " " << k.atom << k.cell << " " <<  norm(g.position(i) - g.position(k)) << "\n";
      }
}
