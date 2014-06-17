#include <iostream>
#include <fstream>
#include <geom/geom.hpp>
#include <io/geomio.hpp>
#include <boost/format.hpp>			
#include <geom/zpt.hpp>

int main()
{
try{
  std::ifstream inp("t1.xyz");
  qpp::geometry<0> g;
  qpp::read_xyz(inp,g);

  //qpp::write_xyz(std::cout,g);

  g.build_type_table();
  g.ngbr.default_distance = 1.7;
  g.ngbr.build_disttable();
  g.ngbr.build();

  //std::cout << "ngbr table ready\n";

  qpp::zpattern<0> z(g,"z");

  typedef qpp::zpattern<0> zpt;

  z.add_point(zpt::zpt_point("C1","C"),zpt::zsearch);
  z.add_point(zpt::zpt_point("C2","C"),zpt::zsearch);
  z.add_point(zpt::zpt_point("C3","C"),zpt::zsearch);

  double rcc_min=1.2, rcc_max = 1.6, rcc=1.4, a_min = 102.0, a_max = 140.0;

  z.add_relation(* new zpt::bond_relation("C1","C2", rcc_min, rcc_max, z, "b1"));
  z.add_relation(* new zpt::bond_relation("C1","C3", rcc_min, rcc_max, z, "b2"));
  z.add_relation(* new zpt::angle_relation("C1","C2","C3", a_min, a_max, z));
  z.add_relation(* new zpt::bond_relation("C2","C3", rcc_min, rcc_max, z, "b3"));
  z.add_relation(* new zpt::angle_relation("C1","C2","C3", 
		(*new zpt::linear_dependence(120e0,z)).term("b1",1./3).term("b2",1./3).term("b3",1./3), z));

  std::cout << "pattern formed\n";
  
  qpp::parametric_torus<double> tor(6,3);
  std::vector<lace::vector2d<double> > prm;

  while (true)
    {
      z.unbind_all();
      for (int i=0; i<z.n_points(); i++)
	{
	  int a;
	  std::cout << "bind " << z.point(i).nickname << " ?(0/1)\n";
	  std::cin >> a;
	  if (a!=0)
	    {
	      std::cout <<  z.point(i).nickname << " =\n";
	      std::cin >> a;
	      z.bind(i,a);
	    }
	}
      for (int i=0; i<z.n_rel(); i++)
	{
	  z.rel(i).write(std::cout);
	  std::cout << "\n is_defined = " << z.rel(i).is_defined() << " value = " << z.rel(i).value() 
		    << " n_undefined = " << z.rel(i).n_undefined() << " satisfy = " << z.rel(i).satisfy() << "\n";
	  if (z.rel(i).is_exact())
	    std::cout << " lidep defined = " << z.rel(i).formula().is_defined() << " value= " << z.rel(i).formula().value() << "\n";
	  for (int j=0; j<z.n_point_of_rel(i); j++)
	    {
	      int k = z.rel(i).point(j);
	      std::cout << " " << z.rel(i).point_nick(j) << " " << k << " is_bound= " << z.point(k).is_bound << " to= " <<  z.point(k).bound;
	    }
	  std::cout << "\n";
	}
    }
 }
catch (qpp::qpp_exception & err)
   {
     std::cout << err.what()<< "\n";
   }
}
