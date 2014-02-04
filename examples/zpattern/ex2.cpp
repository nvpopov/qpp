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
  qpp::geometry<3> cl;
  std::ifstream inp("q.xyz");
  qpp::read_xyz(inp,cl);

  int N=2, M=1, K=2;

  qpp::geometry<3>::iterator i( qpp::index<3>(0,0,0,0), 
				qpp::index<3>(cl.size()-1,N-1,M-1,K-1) );
  
  qpp::geometry<3> g( cl.cell(0)*N, cl.cell(1)*M, cl.cell(2)*K);
  for ( i=i.begin(); i!=i.end(); i++)
    g.add(cl.atom(i),cl.full_coord(i));
   
  //qpp::write_xyz(std::cout,g);
  //g.write(std::cout);
  g.add("X", 2.9253, 4.11701, 2.49663);

  g.default_ngbr_distance = 1.8;
  g.build_type_table();
  g.build_ngbr_disttable();
  g.build_ngbr_table();


  /*
  for (int i=0; i<g.size(); i++)
    for (int j=0; j<g.n_ngbr(i); j++)
      {
	qpp::index<3> k = g.ngbr(i,j);
	std::cout << g.atom(i) << " " << i << " " << g.atom(k) << " " << k << " " <<  norm(g.coord(i) - g.full_coord(k)) << "\n";
      }
  */
  
  qpp::zpattern<3> z;
  z.add(qpp::zpt_record<double>("O",1.8));
  z.add(qpp::zpt_record<double>("Cl").bond(0, 1.7,1.8));
  z.add(qpp::zpt_record<double>("Si").bond(0, 1.55,1.65).angle(1, 85.0, 100.0));
  z.add(qpp::zpt_record<double>("Si").bond(0, 1.55,2.65).angle(1, 85.0, 100.0).dyhedral(2,140.0, 160.0));

  srand (time(NULL));
  qpp::random_integer_lister lst;

  // std::cout << "alive\n";
  if ( z.match(g,lst))
    {
      for (int i=0; i< z.size(); i++)
	std::cout << g.atom(z.bound(i)) << g.coord(z.bound(i)) << "\n";
      
      for (int i=0; i< z.size(); i++)
	g.atom(z.bound(i)) = "N";
    }
      
}
