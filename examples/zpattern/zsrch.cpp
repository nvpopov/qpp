#include <iostream>
#include <fstream>
#include <geom/geom.hpp>
#include <io/geomio.hpp>
#include <boost/format.hpp>			
#include <geom/zpt.hpp>

int main()
{
  std::ifstream inp("t1.xyz");
  qpp::geometry<0> g;
  qpp::read_xyz(inp,g);

  qpp::parametric_torus<double> tor(6,3.3);
  std::vector<lace::vector2d<double> > prm;
  for (int i=0; i<g.nat(); i++)
    {
      lace::vector2d<double> r = tor.project(g.coord(i));
      prm.push_back(r);
      g.coord(i) = tor.map(r);
    }

  g.build_type_table();
  g.ngbr.default_distance = 1.7;
  g.ngbr.build_disttable();
  g.ngbr.build();

  std::cout << "ngbr table ready\n";

  for (int i=0; i<g.nat(); i++)
    {
      std::cout << i;
      for (int j=0; j<g.ngbr.n(i); j++)
	std::cout << " " << g.ngbr(i,j) << " " << norm(g.full_coord(i)-g.full_coord(g.ngbr(i,j)));
      std::cout << "\n";
    }

  //  qpp::zpattern<0> z(g,"triang"), z1(g,"penta");
  qpp::zpattern<0> z1(g,"penta");

  typedef qpp::zpattern<0> zpt;
  /*
  z.add_point(zpt::zpt_point("C1","C"),zpt::zsearch);
  z.add_point(zpt::zpt_point("C2","C"),zpt::zsearch);
  z.add_point(zpt::zpt_point("C3","C"),zpt::zsearch);
  */
  double rcc_min=1.2, rcc_max = 1.6, rcc=1.4, amin = 102.0, amax = 140.0;
  /*
  z.add_relation(* new zpt::bond_relation("C1","C2", rcc_min, rcc_max, z));
  z.add_relation(* new zpt::bond_relation("C1","C3", rcc_min, rcc_max, z));
  z.add_relation(* new zpt::bond_relation("C2","C3", rcc_min, rcc_max, z));
  */
  z1.add_point(zpt::zpt_point("C1","C"),zpt::zsearch);
  z1.add_point(zpt::zpt_point("C2","C"),zpt::zsearch);
  z1.add_point(zpt::zpt_point("C3","C"),zpt::zsearch);
  z1.add_point(zpt::zpt_point("C4","C"),zpt::zsearch);
  z1.add_point(zpt::zpt_point("C5","N"),zpt::zinsert);
  z1.add_point(zpt::zpt_point("CX","C"),zpt::zavoid);

  z1.add_relation(* new zpt::bond_relation("C1","C2", rcc_min, rcc_max, z1));
  z1.add_relation(* new zpt::bond_relation("C2","C3", rcc_min, rcc_max, z1));
  z1.add_relation(* new zpt::bond_relation("C3","C4", rcc_min, rcc_max, z1));
  z1.add_relation(* new zpt::angle_relation("C1","C2","C3", 90, amax, z1));
  z1.add_relation(* new zpt::angle_relation("C2","C3","C4", 90, amax, z1));
  z1.add_relation(* new zpt::angle_relation("C3","C4","C5", 90, amax, z1));
  z1.add_relation(* new zpt::angle_relation("C4","C5","C1", 90, amax, z1));
  z1.add_relation(* new zpt::angle_relation("C5","C1","C2", 90, amax, z1));
  z1.add_relation(* new zpt::bond_relation("C1","C5", *new zpt::linear_dependence(rcc,z1), z1));
  z1.add_relation(* new zpt::bond_relation("C4","C5", *new zpt::linear_dependence(rcc,z1), z1));
  z1.add_relation(* new zpt::dyhedral_relation("C4","C5","C1","C2", -20, 20, z1));
  z1.add_relation(* new zpt::bond_relation("C5","CX", 0, rcc_min, z1));

  std::cout << "pattern formed\n";
  
  qpp::random_integer_lister cnt;
  qpp::init_rand();

  /*  for (int i=0; i<10; i++)
    {
      z.apply(tor,prm,g,cnt);
      }*/
  try
    { z1.apply(tor,prm,g,cnt);}
  catch (qpp::qpp_exception<char> *e)
    { std::cout << e->what() << "\n";}
 
  for (int i=0; i<z1.n_points(); i++)
    {
      std::cout << z1.point(i).nickname << " = "  << z1.bound(i) << "\n";
      g.atom(z1.bound(i)) = "N";
    }
  for (int i=0; i<z1.n_rel(); i++)
    {
      for (int j = 0; j<z1.rel(i).n_points(); j++)
	std::cout << z1.rel(i).point_nick(j) << " ";
      std::cout << z1.rel(i).value() << "\n";
    }

  std::ofstream out("t2.xyz");
  qpp::write_xyz(out,g);

}
