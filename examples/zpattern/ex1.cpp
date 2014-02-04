#include <iostream>
#include <fstream>
#include <geom/geom.hpp>
#include <io/geomio.hpp>
#include <boost/format.hpp>			
#include <geom/zmt.hpp>
#include <time.h>
#include <stdlib.h>

// -------------- Type table & neighbours table for simple molecule ---------------------

int main()
{
  int N=2, M=2, K=1;
  qpp::geometry<3> uc;
  std::ifstream inp("a-quartz.uc");
  qpp::read_xyz(inp,uc);
  
  //qpp::write_xyz(std::cout, uc);

  qpp::geometry<3>::iterator i( qpp::index<3>(0,0,0,0), 
				qpp::index<3>(uc.size()-1,N-1,M-1,K-1) );

  qpp::geometry<3> g( uc.cell(0)*N, uc.cell(1)*M, uc.cell(2)*K);
  for ( i=i.begin(); i!=i.end(); i++)
    {
      //     std::cout << uc.atom(i) << uc.full_coord(i)<< "\n";
      g.add(uc.atom(i),uc.full_coord(i));
    }
  
  g.add("Cl",(g.coord(5)+g.coord(16)+g.coord(23))/3);

  qpp::write_xyz(std::cout, g);

  //  qpp::write_xyz(std::cout,g);
  //  g.cell.write(std::cout);
  //  g.write(std::cout);
  /*
  g.default_ngbr_distance = 1.8;
  g.build_type_table();
  g.build_ngbr_disttable();
  g.build_ngbr_table();
  
  for (int i=0; i<g.size(); i++)
    {
      qpp::geometry<3> g1;
      for (int j=0; j<g.size(); j++)
	g1.add(g.atom(j), g.coord(j));
      g1.atom(i) = "Cl";
      for (int j=0; j<g.n_ngbr(i); j++)
	g1.atom( g.ngbr_table(i,j) ) = "S";
      qpp::write_xyz(std::cout, g1);
    }
  */
  /*
  for (int i=0; i<g.size(); i++)
    for (int j=0; j<g.n_ngbr(i); j++)
      {
	qpp::index<3> k = g.ngbr_table(i,j);
	std::cout << g.atom(i) << " " << i << " " << g.atom(k) << " " << k << " " <<  norm(g.coord(i) - g.full_coord(k)) << "\n";
      }
  */
  /*
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
  */
}
