#include <iostream>
#include <fstream>
#include <geom/geom.hpp>
#include <io/geomio.hpp>
#include <boost/format.hpp>			
#include <geom/zmt.hpp>
#include <geom/zpt.hpp>
#include <time.h>
#include <stdlib.h>

// -------------- Type table & neighbours table for simple molecule ---------------------

typedef qpp::zpattern<3> zpt;

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

  g.ngbr.default_distance = 1.8;
  g.build_type_table();
  g.ngbr.build_disttable();
  g.ngbr.build();
  
  qpp::zpattern<3> z(g,"hren");

  try
    {
      
      z.add_point(zpt::zpt_point("C1","C"),zpt::zsearch);
      z.add_point(zpt::zpt_point("C2","C"),zpt::zsearch);
      z.add_point(zpt::zpt_point("C3","C"),zpt::zsearch);
      z.add_point(zpt::zpt_point("Cnew","C"),zpt::zinsert);
      z.add_point(zpt::zpt_point("Cbad","C"),zpt::zavoid);
      
      double rcc_min=1.2, rcc_max = 1.6, rcc=1.4, amin = 102.0, amax = 140.0;

      z.add_relation(* new zpt::bond_relation("C1","C2", rcc_min, rcc_max, z));
      z.add_relation(* new zpt::bond_relation("C1","C3", rcc_min, rcc_max,z));
      z.add_relation(* new zpt::angle_relation("C2","C1","C3", amin, amax, z,"alpha"));
      z.add_relation(* new zpt::bond_relation("C1","Cnew", *new zpt::linear_dependence(rcc, z), z));
      z.add_relation(* new zpt::angle_relation("Cnew","C1","C2",
					       (*new zpt::linear_dependence(180,z)).term("alpha",-0.5),z));
      z.add_relation(* new zpt::dyhedral_relation("Cnew", "C1", "C2", "C3", -30.0, 30.0, z));
      z.add_relation(* new zpt::bond_relation("Cnew", "Cbad", 0e0, rcc, z));
      
      z.write(std::cout);
      z.debug();
    }
  
  catch ( qpp::qpp_exception<char> & e)
    {
      std::cout << e.what() << "\n";
    }
  
  /*
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
  */
      
}
