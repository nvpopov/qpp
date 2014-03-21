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
typedef lace::vector3d<double> v3d;

int main()
{
  
  qpp::geometry<0,double> G;
  std::vector<v2d> p;

  //qpp::parametric_plane<double> plane;
  double R=4.2, r=1.7, rcc=1.4;

  int N=5;
  qpp::parametric_torus<double> sph(R,r);
  /*
  p.push_back(v2d(qpp::pi/2,0));
  p.push_back(sph.ruler(p[0],v2d(1,0),rcc));
  p.push_back(sph.protract(p[0],p[1],rcc,2*qpp::pi/3));
  */

  qpp::geometry<2,double> uc;
  uc.cell(0) = v3d(3*rcc,0e0,0e0);
  uc.cell(1) = v3d(0e0,std::sqrt(3.)*rcc,0e0);
  
  uc.add("C",0,0,0);
  uc.add("C",-rcc/2,std::sqrt(3.)*rcc/2,0);
  uc.add("C",rcc,0,0);
  uc.add("C",1.5*rcc,std::sqrt(3.)*rcc/2,0);

  qpp::geometry<2,double>::iterator uci(qpp::index<2>(0,-10,-10),qpp::index<2>(3,10,10));

  qpp::geometry<0,double> grph;

  for (uci = uci.begin(); uci != uci.end(); uci++)
    grph.add("C",uc.full_coord(uci));


  //  double R=(1+std::sqrt(5.))*std::sqrt(3.)*rcc/4; //c20
  //double R=3.46; //c60
  //  double R=2.18; //c24
  //  double R = 4.20; //c720
  //double r = rcc*std::sqrt(1.5);

  //  int N=5;
  //  qpp::parametric_torus<double> sph(R,r);
  //  qpp::parametric_sphere<double> sph(R);
  p.push_back(v2d(0,0));
  p.push_back(sph.ruler(p[0],v2d(0,1),rcc));
  //  p.push_back(sph.protract(p[0],p[1],rcc,0.6*qpp::pi));
  p.push_back(sph.triangul(p[0],p[1],rcc,5*qpp::pi/7));
  
  for (int i=0; i<grph.nat(); i++)
    {
      //grph.coord(i).x() -= rcc/2;
      //grph.coord(i).y() -= sqrt(3.)*rcc/2;
      grph.coord(i).z() += r;
    }

  std::ofstream gg("grph.xyz");
  qpp::write_xyz(gg, grph);
  

     
  /* for (int i=0; i<grph.nat(); i++)
    { 
      v2d p0 = sph.project(grph.coord(i));
      if ( qpp::pi/3 < p0(0) && 2*qpp::pi/3 > p0(0))
	{
	  p.push_back(p0);
	  //p0(0) *= -1;
	  //p0(1) += qpp::pi/6;
	  //p.push_back(p0);
	}
    }
  */
  for (int i=0; i<p.size(); i++)
    G.add("C", sph.map(p[i]) );

  typedef qpp::zpattern<0,double> zpt;
  std::vector<zpt> zz(6);

  double rcc_min=1.2, rcc_max = 1.6,  amin = 102.0, amax = 140.0;
  //  double rxx = 2*rcc*std::sin(amax*qpp::pi/360);
  double rxx = 2.3;

  std::cout << rxx << "\n";

  //  try {
  
    //----------------------------------------------------------------------------
    zz[0].add_point(zpt::zpt_point("C1","C"),zpt::zsearch);
    zz[0].add_point(zpt::zpt_point("C2","C"),zpt::zsearch);
    zz[0].add_point(zpt::zpt_point("C3","C"),zpt::zsearch);
    zz[0].add_point(zpt::zpt_point("C4","C"),zpt::zinsert);
    zz[0].add_point(zpt::zpt_point("CX","C"),zpt::zavoid);
    zz[0].add_point(zpt::zpt_point("CN","C"),zpt::zavoid);
    
    zz[0].add_relation(* new zpt::bond_relation("C1","C2", rcc_min, rcc_max, zz[0]));
    zz[0].add_relation(* new zpt::bond_relation("C1","C3", rcc_min, rcc_max, zz[0]));
    zz[0].add_relation(* new zpt::surfangle_relation("C2","C1","C3", amin, amax, zz[0], "alpha"));
    
    zz[0].add_relation(* new zpt::bond_relation("C1","C4", *new zpt::linear_dependence(rcc,zz[0]), zz[0]));
    zz[0].add_relation(* new zpt::surfangle_relation("C2","C1","C4", 
						     (*new zpt::linear_dependence(180.,zz[0])).term("alpha",-0.5), zz[0]));
    zz[0].add_relation(* new zpt::surfangle_relation("C3","C1","C4", amin, amax, zz[0]));
    
    zz[0].add_relation(* new zpt::bond_relation("CX","C1", 0, rxx, zz[0]));
    zz[0].add_relation(* new zpt::dyhedral_relation("C1","C2","C3","CX", -60, 60, zz[0]));
    zz[0].add_relation(* new zpt::bond_relation("CN","C4", 0, rcc, zz[0]));
    //----------------------------------------------------------------------------
    zz[1].add_point(zpt::zpt_point("C1","C"),zpt::zsearch);
    zz[1].add_point(zpt::zpt_point("C2","C"),zpt::zsearch);
    zz[1].add_point(zpt::zpt_point("C3","C"),zpt::zsearch);
    zz[1].add_point(zpt::zpt_point("C4","C"),zpt::zinsert);
    zz[1].add_point(zpt::zpt_point("CX","C"),zpt::zavoid);
    zz[1].add_point(zpt::zpt_point("CN","C"),zpt::zavoid);
    
    zz[1].add_relation(* new zpt::bond_relation("C1","C2", rcc_min, rcc_max, zz[1]));
    zz[1].add_relation(* new zpt::bond_relation("C2","C3", rcc_min, rcc_max, zz[1]));
    zz[1].add_relation(* new zpt::surfangle_relation("C1","C2","C3", amin, amax, zz[1], "alpha"));
    
    zz[1].add_relation(* new zpt::bond_relation("C3","C4", *new zpt::linear_dependence(rcc,zz[1]), zz[1]));
    zz[1].add_relation(* new zpt::surfangle_relation("C2","C3","C4", 
						     (*new zpt::linear_dependence(0,zz[1])).term("alpha",1.), zz[1]));
    zz[1].add_relation(* new zpt::dyhedral_relation("C1","C2","C3","C4",-60,60,zz[1]));
    
    zz[1].add_relation(* new zpt::bond_relation("CX","C3", 0, rxx, zz[1]));
    zz[1].add_relation(* new zpt::dyhedral_relation("C1","C2","C3","CX", -60, 60, zz[1]));
    zz[1].add_relation(* new zpt::bond_relation("CN","C4", 0, rcc, zz[1]));
    //----------------------------------------------------------------------------
    zz[2].add_point(zpt::zpt_point("C1","C"),zpt::zsearch);
    zz[2].add_point(zpt::zpt_point("C2","C"),zpt::zsearch);
    zz[2].add_point(zpt::zpt_point("C3","C"),zpt::zsearch);
    zz[2].add_point(zpt::zpt_point("C4","C"),zpt::zinsert);
    zz[2].add_point(zpt::zpt_point("CX","C"),zpt::zsearch);
    zz[2].add_point(zpt::zpt_point("CXX","C"),zpt::zavoid);
    zz[2].add_point(zpt::zpt_point("CN","C"),zpt::zavoid);
    
    zz[2].add_relation(* new zpt::bond_relation("C1","C2", rcc_min, rcc_max, zz[2]));
    zz[2].add_relation(* new zpt::bond_relation("C1","C3", rcc_min, rcc_max, zz[2]));
    zz[2].add_relation(* new zpt::surfangle_relation("C2","C1","C3", amin, amax, zz[2], "alpha"));
    zz[2].add_relation(* new zpt::bond_relation("CX","C1", rcc_max, rxx, zz[2]));
    zz[2].add_relation(* new zpt::surfangle_relation("C2","C1","CX", 60, 180, zz[2]));
    
    zz[2].add_relation(* new zpt::bond_relation("C1","C4", *new zpt::linear_dependence(rcc,zz[2]), zz[2]));
    zz[2].add_relation(* new zpt::bond_relation("CX","C4", *new zpt::linear_dependence(rcc,zz[2]), zz[2]));
    zz[2].add_relation(* new zpt::surfangle_relation("C3","C1","C4", amin, amax, zz[2]));
    zz[2].add_relation(* new zpt::surfangle_relation("C2","C1","C4", amin, amax, zz[2]));
    zz[2].add_relation(* new zpt::surfangle_relation("C1","C4","CX", amin, amax, zz[2]));
        
    zz[2].add_relation(* new zpt::bond_relation("CXX","C1", 0, rxx, zz[2]));
    zz[2].add_relation(* new zpt::dyhedral_relation("C1","C2","C3","CXX", -60, 60, zz[2]));
    zz[2].add_relation(* new zpt::bond_relation("CN","C4", 0, rcc_min, zz[2]));
    //----------------------------------------------------------------------------
    zz[3].add_point(zpt::zpt_point("C1","C"),zpt::zsearch);
    zz[3].add_point(zpt::zpt_point("C2","C"),zpt::zsearch);
    zz[3].add_point(zpt::zpt_point("C3","C"),zpt::zsearch);
    zz[3].add_point(zpt::zpt_point("C4","C"),zpt::zinsert);
    zz[3].add_point(zpt::zpt_point("CX","C"),zpt::zsearch);
    zz[3].add_point(zpt::zpt_point("CXX","C"),zpt::zavoid);
    zz[3].add_point(zpt::zpt_point("CN","C"),zpt::zavoid);

    zz[3].add_relation(* new zpt::bond_relation("C1","C2", rcc_min, rcc_max, zz[3]));
    zz[3].add_relation(* new zpt::bond_relation("C2","C3", rcc_min, rcc_max, zz[3]));
    zz[3].add_relation(* new zpt::surfangle_relation("C1","C2","C3", amin, amax, zz[3], "alpha"));
    
    zz[3].add_relation(* new zpt::bond_relation("C3","C4", *new zpt::linear_dependence(rcc,zz[3]), zz[3]));
    zz[3].add_relation(* new zpt::bond_relation("CX","C4", *new zpt::linear_dependence(rcc,zz[3]), zz[3]));
    zz[3].add_relation(* new zpt::surfangle_relation("C2","C3","C4", amin, amax, zz[3]));
    zz[3].add_relation(* new zpt::surfangle_relation("C3","C4","CX", amin, amax, zz[3]));
    
    zz[3].add_relation(* new zpt::dyhedral_relation("C1","C2","C3","C4",-45,45,zz[3]));
    
    zz[3].add_relation(* new zpt::bond_relation("CX","C3", rcc_max, rxx, zz[3]));
    zz[3].add_relation(* new zpt::surfangle_relation("C2","C3","CX", 60, 180, zz[3]));
    zz[3].add_relation(* new zpt::bond_relation("CXX","C3", 0, rxx, zz[3]));
    zz[3].add_relation(* new zpt::dyhedral_relation("C1","C2","C3","CXX", -60, 60, zz[3]));
    zz[3].add_relation(* new zpt::bond_relation("CN","C4", 0, rcc_min, zz[3]));
    //----------------------------------------------------------------------------
    
    zz[4].add_point(zpt::zpt_point("C1","C"),zpt::zsearch);
    zz[4].add_point(zpt::zpt_point("C2","C"),zpt::zsearch);
    zz[4].add_point(zpt::zpt_point("C3","C"),zpt::zsearch);
    zz[4].add_point(zpt::zpt_point("C4","C"),zpt::zinsert);
    zz[4].add_point(zpt::zpt_point("CX","C"),zpt::zavoid);
    
    zz[4].add_relation(* new zpt::bond_relation("C1","C2", 1.9, 3.0, zz[4],"a"));
    zz[4].add_relation(* new zpt::bond_relation("C2","C3", 1.9, 3.0, zz[4],"b"));
    zz[4].add_relation(* new zpt::bond_relation("C3","C1", 1.9, 3.0, zz[4],"c"));
    
    zz[4].add_relation(* new zpt::bond_relation("C1","C4", 
						(*new zpt::linear_dependence(0,zz[4])).term("a",.192).term("b",.192).term("c",.192), zz[4]));
    zz[4].add_relation(* new zpt::bond_relation("C2","C4", 
						(*new zpt::linear_dependence(0,zz[4])).term("a",.192).term("b",.192).term("c",.192), zz[4]));
    zz[4].add_relation(* new zpt::bond_relation("C3","C4", 1.1, 1.8, zz[4]));
    
    zz[4].add_relation(* new zpt::bond_relation("CX","C4", 0, rxx, zz[4]));

    //----------------------------------------------------------------------------
    zz[5].add_point(zpt::zpt_point("C1","C"),zpt::zsearch);
    zz[5].add_point(zpt::zpt_point("C2","C"),zpt::zsearch);
    zz[5].add_point(zpt::zpt_point("C3","C"),zpt::zsearch);
    zz[5].add_point(zpt::zpt_point("C4","C"),zpt::zsearch);
    zz[5].add_point(zpt::zpt_point("C5","C"),zpt::zinsert);
    zz[5].add_point(zpt::zpt_point("CN","C"),zpt::zavoid);

    zz[5].add_relation(* new zpt::bond_relation("C1","C2", rcc_min, rcc_max, zz[5]));
    zz[5].add_relation(* new zpt::bond_relation("C3","C4", rcc_min, rcc_max, zz[5]));
    zz[5].add_relation(* new zpt::bond_relation("C2","C3", 1.9, 2.6, zz[5]));

    zz[5].add_relation(* new zpt::bond_relation("C2","C5",*new zpt::linear_dependence(rcc,zz[5]), zz[5]));
    zz[5].add_relation(* new zpt::bond_relation("C3","C5",*new zpt::linear_dependence(rcc,zz[5]), zz[5]));
    
    zz[5].add_relation(* new zpt::surfangle_relation("C1","C2","C5", amin, amax, zz[5]));
    zz[5].add_relation(* new zpt::surfangle_relation("C2","C5","C3", amin, amax, zz[5]));
    zz[5].add_relation(* new zpt::surfangle_relation("C5","C3","C4", amin, amax, zz[5]));
    zz[5].add_relation(* new zpt::dyhedral_relation("C1","C2","C3","C4", -60, 60, zz[5]));

    zz[5].add_relation(* new zpt::bond_relation("C5","CN", 0, rcc_min, zz[5]));

    // ---------------------------------------------------------------------------
    qpp::init_rand();
    qpp::random_integer_lister lst,lst1,lst2;
    
    std::ofstream f("tor.xyz");
    qpp::write_xyz(f, G);
    
    G.ngbr.default_distance = 3.1;
    G.build_type_table();
    G.ngbr.build_disttable();
    G.ngbr.build();
    
    for (int i=0; i<zz.size();i++)
      zz[i].init(sph,p,G);

    bool contin = true;
    
    while(contin)
      {
	contin = false;
	lst1.set(0,zz.size()-1);
	for (int i=lst1.begin(); !lst1.end(); i=lst1.next())
	  {
	    if ( zz[i].apply_surf( lst) )
	      {
		contin = true;
		std::stringstream s;
		s << "pattern " << i << " = ";
		for (int k=0; k<zz[i].n_points(); k++)
		  s << " " << zz[i].bound(k)+1;
		
		G.setname(s.str());
		qpp::write_xyz(f,G);
	      }
	  }
      }
    //  }
    //  catch (qpp::qpp_exception<char> *e)
    //    { std::cout << e->what() << "\n";}
}
