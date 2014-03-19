#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>
#include <boost/format.hpp>
#include<geom/atom.hpp>
#include<geom/geom.hpp>
#include<geom/manyfold.hpp>
#include <geom/zpt.hpp>
#include <io/geomio.hpp>

typedef lace::vector2d<double> v2d;

int main()
{
  
  qpp::geometry<0,double> G;
  std::vector<v2d> p;

  //qpp::parametric_plane<double> plane;
  double rcc_min=1.2, rcc_max = 1.6, rcc=1.4, amin = 102.0, amax = 140.0;


  //  double R=(1+std::sqrt(5.))*std::sqrt(3.)*rcc/4; //c20
  //double R=3.46; //c60
  double R=3.8; //c70
  //  double R=2.18; //c24
  //double R=11.85; //c720

  int N=5;
  qpp::parametric_sphere<double> sph(R);
  p.push_back(v2d(qpp::pi/2,0));
  p.push_back(sph.ruler(p[0],v2d(1,0),rcc));
  //  p.push_back(sph.protract(p[0],p[1],rcc,0.6*qpp::pi));
  p.push_back(sph.triangul(p[0],p[1],rcc,3*qpp::pi/5));
  

  for (int i=0; i<p.size(); i++)
    G.add("C", sph.map(p[i]) );

  typedef qpp::zpattern<0,double> zpt;
  std::vector<zpt> z1(3),z2(2);
  
  // ----------------------------------------------------------------- 
  z1[0].add_point(zpt::zpt_point("C1","C"),zpt::zsearch);
  z1[0].add_point(zpt::zpt_point("C2","C"),zpt::zsearch);
  z1[0].add_point(zpt::zpt_point("C3","C"),zpt::zsearch);
  z1[0].add_point(zpt::zpt_point("C4","C"),zpt::zinsert);
  z1[0].add_point(zpt::zpt_point("CX","C"),zpt::zavoid);
  
  z1[0].add_relation(* new zpt::bond_relation("C1","C2", rcc_min, rcc_max, z1[0]));
  z1[0].add_relation(* new zpt::bond_relation("C2","C3", rcc_min, rcc_max, z1[0]));
  z1[0].add_relation(* new zpt::surfangle_relation("C1","C2","C3", amin, amax, z1[0], "alpha"));
  z1[0].add_relation(* new zpt::bond_relation("C2","C4", *new zpt::linear_dependence(rcc,z1[0]), z1[0]));
  z1[0].add_relation(* new zpt::surfangle_relation("C1","C2","C4", 
						   (*new zpt::linear_dependence(180,z1[0])).term("alpha",-0.5), z1[0]));
    //z1[0].add_relation(* new zpt::angle_relation("C1","C2","C4", 
    //					       *new zpt::linear_dependence(120,z1[0]), z1[0]));
  z1[0].add_relation(* new zpt::surfangle_relation("C3","C2","C4", amin, amax, z1[0]));
  z1[0].add_relation(* new zpt::bond_relation("CX","C4", 0, rcc_min, z1[0]));
  // -----------------------------------------------------------------
  z1[1].add_point(zpt::zpt_point("C1","C"),zpt::zsearch);
  z1[1].add_point(zpt::zpt_point("C2","C"),zpt::zsearch);
  z1[1].add_point(zpt::zpt_point("C3","C"),zpt::zsearch);
  z1[1].add_point(zpt::zpt_point("C4","C"),zpt::zinsert);
  z1[1].add_point(zpt::zpt_point("CX","C"),zpt::zavoid);
  //  z1[1].add_point(zpt::zpt_point("CXX","C"),zpt::zavoid);
  
  z1[1].add_relation(* new zpt::bond_relation("C1","C2", rcc_min, rcc_max, z1[1]));
  z1[1].add_relation(* new zpt::bond_relation("C2","C3", rcc_min, rcc_max, z1[1]));
  z1[1].add_relation(* new zpt::angle_relation("C1","C2","C3", amin, amax, z1[1], "alpha"));
  z1[1].add_relation(* new zpt::bond_relation("C3","C4", *new zpt::linear_dependence(rcc,z1[1]), z1[1]));
  z1[1].add_relation(* new zpt::angle_relation("C2","C3","C4", 
					       (*new zpt::linear_dependence(0,z1[1])).term("alpha",1.), z1[1]));
  z1[1].add_relation(* new zpt::dyhedral_relation("C1","C2","C3","C4",-20,20,z1[1]));
  z1[1].add_relation(* new zpt::bond_relation("CX","C4", 0, rcc_min, z1[1]));
  //z1[1].add_relation(* new zpt::bond_relation("CXX","C4", 0, rcc_max, z1[1]));
  //z1[1].add_relation(* new zpt::angle_relation("C3","C4","CXX", 0, 80, z1[1]));
  // ----------------------------------------------------------------- 
  std::cout << "trng\n";
  z1[2].add_point(zpt::zpt_point("C1","C"),zpt::zsearch);
  z1[2].add_point(zpt::zpt_point("C2","C"),zpt::zsearch);
  z1[2].add_point(zpt::zpt_point("C3","C"),zpt::zsearch);
  z1[2].add_point(zpt::zpt_point("C4","C"),zpt::zinsert);
  z1[2].add_point(zpt::zpt_point("CX","C"),zpt::zavoid);
  
  z1[2].add_relation(* new zpt::bond_relation("C1","C2", 1.9, 3.0, z1[2],"a"));
  z1[2].add_relation(* new zpt::bond_relation("C2","C3", 1.9, 3.0, z1[2],"b"));
  z1[2].add_relation(* new zpt::bond_relation("C3","C1", 1.9, 3.0, z1[2],"c"));

  z1[2].add_relation(* new zpt::bond_relation("C1","C4", 
	            (*new zpt::linear_dependence(0,z1[2])).term("a",.192).term("b",.192).term("c",.192), z1[2]));
  z1[2].add_relation(* new zpt::bond_relation("C2","C4", 
	            (*new zpt::linear_dependence(0,z1[2])).term("a",.192).term("b",.192).term("c",.192), z1[2]));
  z1[2].add_relation(* new zpt::bond_relation("C3","C4", 1.1, 1.8, z1[2]));

  z1[2].add_relation(* new zpt::bond_relation("CX","C4", 0, rcc_max, z1[2]));
  // -----------------------------------------------------------------
  z2[0].add_point(zpt::zpt_point("C1","C"),zpt::zsearch);
  z2[0].add_point(zpt::zpt_point("C2","C"),zpt::zsearch);
  z2[0].add_point(zpt::zpt_point("C3","C"),zpt::zsearch);
  z2[0].add_point(zpt::zpt_point("C4","C"),zpt::zinsert);
  z2[0].add_point(zpt::zpt_point("C5","C"),zpt::zinsert);
  z2[0].add_point(zpt::zpt_point("CX1","C"),zpt::zavoid);
  z2[0].add_point(zpt::zpt_point("CX2","C"),zpt::zavoid);
  
  z2[0].add_relation(* new zpt::bond_relation("C1","C2", rcc_min, rcc_max, z2[0]));
  z2[0].add_relation(* new zpt::bond_relation("C2","C3", rcc_min, rcc_max, z2[0]));
  z2[0].add_relation(* new zpt::angle_relation("C1","C2","C3", amin, 110, z2[0]));
  z2[0].add_relation(* new zpt::bond_relation("C3","C4", *new zpt::linear_dependence(rcc,z2[0]), z2[0]));
  z2[0].add_relation(* new zpt::angle_relation("C2","C3","C4", 
					       *new zpt::linear_dependence(108,z2[0]), z2[0]));
  z2[0].add_relation(* new zpt::bond_relation("C4","C5", *new zpt::linear_dependence(rcc,z2[0]), z2[0]));
  z2[0].add_relation(* new zpt::bond_relation("C1","C5", *new zpt::linear_dependence(rcc,z2[0]), z2[0]));
  z2[0].add_relation(* new zpt::angle_relation("C2","C3","C4", amin, amax, z2[0]));
  z2[0].add_relation(* new zpt::angle_relation("C4","C5","C1", amin, amax, z2[0]));
  z2[0].add_relation(* new zpt::angle_relation("C5","C1","C2", amin, amax, z2[0]));
  
  z2[0].add_relation(* new zpt::bond_relation("CX1","C4", 0, rcc_min, z2[0]));
  z2[0].add_relation(* new zpt::bond_relation("CX2","C5", 0, rcc_min, z2[0]));
  // -----------------------------------------------------------------
  // -----------------------------------------------------------------
  z2[1].add_point(zpt::zpt_point("C1","C"),zpt::zsearch);
  z2[1].add_point(zpt::zpt_point("C2","C"),zpt::zsearch);
  z2[1].add_point(zpt::zpt_point("C3","C"),zpt::zsearch);
  z2[1].add_point(zpt::zpt_point("C4","C"),zpt::zsearch);
  z2[1].add_point(zpt::zpt_point("C5","C"),zpt::zinsert);
  z2[1].add_point(zpt::zpt_point("C6","C"),zpt::zinsert);
  z2[1].add_point(zpt::zpt_point("CX1","C"),zpt::zavoid);
  z2[1].add_point(zpt::zpt_point("CX2","C"),zpt::zavoid);
  
  z2[1].add_relation(* new zpt::bond_relation("C1","C2", rcc_min, rcc_max, z2[1]));
  z2[1].add_relation(* new zpt::bond_relation("C2","C3", rcc_min, rcc_max, z2[1]));
  z2[1].add_relation(* new zpt::bond_relation("C3","C4", rcc_min, rcc_max, z2[1]));
  z2[1].add_relation(* new zpt::angle_relation("C1","C2","C3", 110, amax,  z2[1]));
  z2[1].add_relation(* new zpt::angle_relation("C2","C3","C4", 110, amax,  z2[1]));
  z2[1].add_relation(* new zpt::bond_relation("C4","C5", *new zpt::linear_dependence(rcc,z2[1]), z2[1]));
  z2[1].add_relation(* new zpt::angle_relation("C3","C4","C5", 
					       *new zpt::linear_dependence(120,z2[1]), z2[1]));
  z2[1].add_relation(* new zpt::bond_relation("C5","C6", *new zpt::linear_dependence(rcc,z2[1]), z2[1]));
  z2[1].add_relation(* new zpt::bond_relation("C1","C6", *new zpt::linear_dependence(rcc,z2[1]), z2[1]));
  z2[1].add_relation(* new zpt::angle_relation("C4","C5","C6", amin, amax, z2[1]));
  z2[1].add_relation(* new zpt::angle_relation("C5","C6","C1", amin, amax, z2[1]));
  z2[1].add_relation(* new zpt::angle_relation("C6","C1","C2", amin, amax, z2[1]));
  
  z2[1].add_relation(* new zpt::bond_relation("CX1","C5", 0, rcc_min, z2[1]));
  z2[1].add_relation(* new zpt::bond_relation("CX2","C6", 0, rcc_min, z2[1]));
  //----------------------------------------------------------------------------
  /*  z2[2].add_point(zpt::zpt_point("C1","C"),zpt::zsearch);
  z2[2].add_point(zpt::zpt_point("C2","C"),zpt::zdelete);
  z2[2].add_point(zpt::zpt_point("C3","C"),zpt::zdelete);

  z2[2].add_relation(* new zpt::bond_relation("C1","C2", 0, 1.8, z2[2]));
  z2[2].add_relation(* new zpt::bond_relation("C2","C3", 0, 1.8, z2[2]));
  z2[2].add_relation(* new zpt::bond_relation("C3","C1", 0, 1.8, z2[2]));*/
  //----------------------------------------------------------------------------

  qpp::init_rand();
  qpp::random_integer_lister lst,lst1,lst2;

  std::ofstream f("fl.xyz");
  qpp::write_xyz(f, G);

  G.ngbr.default_distance = 3.1;
  G.build_type_table();
  G.ngbr.build_disttable();
  G.ngbr.build();
  
  bool contin = true;

  try {
    while(contin)
      {
	contin = false;
	lst1.set(0,z1.size()-1);
	for (int i=lst1.begin(); !lst1.end(); i=lst1.next())
	  {
	    bool queue2 = true;
	    while(queue2)
	      {
		queue2 = false;
		lst2.set(0,z2.size()-1);
		for (int j=lst2.begin(); !lst2.end(); j=lst2.next())
		  if (z2[j].apply(sph,p,G,lst) )
		    {
		      queue2 = true;
		      std::stringstream s;
		      s << "queue 2 pattern " << j << " = ";
		      for (int k=0; k<z2[j].n_points(); k++)
			s << " " << z2[j].bound(k);
		      
		      G.setname(s.str());
		      for (int k=0; k<z2[j].n_points(); k++)
			if (z2[j].point_type(k)!=zpt::zavoid)
			  G.atom(z2[j].bound(k)) = "N";
		      qpp::write_xyz(f,G);
		      for (int k=0; k<z2[j].n_points(); k++)
			if (z2[j].point_type(k)!=zpt::zavoid)
			  G.atom(z2[j].bound(k)) = "C";
		      qpp::write_xyz(f,G);
		    }
	      }
	    if ( z1[i].apply(sph,p,G,lst) )
	      {
		contin = true;
		std::stringstream s;
		s << "queue 1 pattern " << i << " = ";
		for (int k=0; k<z1[i].n_points(); k++)
		  s << " " << z1[i].bound(k);
		
		G.setname(s.str());
		for (int k=0; k<z1[i].n_points(); k++)
		  if (z1[i].point_type(k)!=zpt::zavoid)
		    G.atom(z1[i].bound(k)) = "N";
		qpp::write_xyz(f,G);
		for (int k=0; k<z1[i].n_points(); k++)
		  if (z1[i].point_type(k)!=zpt::zavoid)
		    G.atom(z1[i].bound(k)) = "C";
		qpp::write_xyz(f,G);
	      }
	    }
      }
  }
  catch (qpp::qpp_exception<char> *e)
    { std::cout << e->what() << "\n";}
}
