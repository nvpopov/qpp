#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>
#include <boost/format.hpp>
#include<geom/atom.hpp>
#include<geom/geom.hpp>
#include<geom/manyfold.hpp>
#include <geom/zmt.hpp>
#include <io/geomio.hpp>

typedef lace::vector2d<double> v2d;

int main()
{
  
  qpp::geometry<0,double> G;
  std::vector<v2d> p;

  //qpp::parametric_plane<double> plane;

  double rcc = 1.4, rnelse = 1.6, rfree = 1.25,
    rcc_min = 1.25, rcc_max = 1.6;

  int N=5;
  qpp::parametric_torus<double> tor(6, 3*N*rcc/(2*qpp::pi));
  //p.push_back(v2d(qpp::pi/2,0));
  /*  p.push_back(v2d(0,0));
  p.push_back(tor.ruler(p[0],v2d(0,1),rcc));
  p.push_back(tor.protractor(p[0],p[1],rcc,-2*qpp::pi/3));
  */

  for (int n=0; n<N; n++)
    {
      v2d p1(2*qpp::pi*n/N,0);
      v2d p2(2*qpp::pi*(3*n+1)/(3*N),0);
      p.push_back(p1);
      p.push_back(p2);
      p.push_back(tor.protract(p1,p2,rcc,-2*qpp::pi/3));
      p.push_back(tor.protract(p2,p1,rcc,2*qpp::pi/3));
    }

  for (int i=0; i<p.size(); i++)
    G.add("C", tor.map(p[i]) );

  std::vector<qpp::zpattern<0,double> > zz(4);

  // -----------------------------------------------------------------
  zz[0].add(qpp::zpt_record<double>("C",rnelse));
  //  zz[0].add(qpp::zpt_record<double>("C"));
  zz[0].add(qpp::zpt_record<double>("C",rfree).bond(0, rcc_min, rcc_max));
  zz[0].add(qpp::zpt_record<double>("C",rfree).bond(0, rcc_min, rcc_max).angle(1, 105, 135));
  zz[0].no_atoms(qpp::zmt_record<double>("",0, rcc, 1, 120, 2, 180), rfree );
  zz[0].to_insert( qpp::zmt_record<double>("C",0, rcc, 1, 120, 2, 180) );

  // -----------------------------------------------------------------
  zz[1].add(qpp::zpt_record<double>("C",rnelse));
  //  zz[1].add(qpp::zpt_record<double>("C"));
  zz[1].add(qpp::zpt_record<double>("C").bond(0, rcc_min, rcc_max));
  zz[1].add(qpp::zpt_record<double>("C").bond(1, rcc_min, rcc_max).angle(0, 105, 135));
  zz[1].no_atoms( qpp::zmt_record<double>("",0, rcc, 1, 120, 2, 0), rfree );
  zz[1].to_insert( qpp::zmt_record<double>("C",0, rcc, 1, 120, 2, 0) );
  // -----------------------------------------------------------------
  zz[2].add(qpp::zpt_record<double>("C"));
  zz[2].add(qpp::zpt_record<double>("C").bond(0, rcc_min, rcc_max));
  zz[2].add(qpp::zpt_record<double>("C").bond(0, 1.6*rcc_min, 1.6*rcc_max).angle(1, 65, 75));
  zz[2].to_insert( qpp::zmt_record<double>("C",0, rcc, 1, 120, 2, 0) );
  zz[2].no_atoms( qpp::zmt_record<double>("",0, rcc, 1, 120, 2, 0), rnelse, qpp::no_atoms_record<double>::except_pattern );
  //------------------------------------------------------------------
  zz[3].add(qpp::zpt_record<double>("C"));
  zz[3].add(qpp::zpt_record<double>("C").bond(0, rcc_min, rcc_max));
  zz[3].add(qpp::zpt_record<double>("C").bond(0, 1.7*rcc_min, 1.8*rcc_max).angle(1, 90, 115));
  zz[3].to_insert( qpp::zmt_record<double>("C",0, rcc, 1, 120, 2, 0) );
  zz[3].no_atoms( qpp::zmt_record<double>("",0, rcc, 1, 120, 2, 0), rnelse, qpp::no_atoms_record<double>::except_pattern  );
  
  /*
  zz[2].add(qpp::zpt_record<double>("C",rnelse));
  zz[2].add(qpp::zpt_record<double>("C").bond(0, rcc_min, rcc_max));
  zz[2].add(qpp::zpt_record<double>("C").bond(1, rcc_min, rcc_max).angle(0, 110, 130));
  zz[2].to_insert( qpp::zmt_record<double>("C",0, rcc, 1, 120, 2, 180) );
  */

  srand (time(NULL));
  qpp::random_integer_lister lst;

  std::ofstream f("grph.xyz");
  qpp::write_xyz(f, G);

  G.default_ngbr_distance = 3.2;
  G.build_type_table();
  G.build_ngbr_disttable();
  G.build_ngbr_table();
  
  bool contin = true;

  //  for (int tc=0; tc<2000; tc++)
  while(contin)
    {
      contin = false;
      for (int i=0; i<zz.size(); i++)
	{
	  //debug
	  /*
	  std::cout << "pattern " << i << "\n";
	  for (int j=0; j<G.size(); j++)
	    {
	      std::cout << j;
	      for (int k=0; k<G.n_ngbr(j); k++)
		std::cout << " " << G.ngbr(j,k);
	      std::cout << "\n";
	    }
	  */
	  if ( zz[i].match(G,lst) )
	    {

	      std::stringstream s;
	      s << "pattern " << i << " = ";
	      for (int j=0; j<zz[i].size(); j++)
		s << zz[i].bound(j);
	      
	      contin = true;
	      //std::cout << "match " << i << "\n";
	      zz[i].replace_surf(tor, p, G);
	      //std::cout << "after replace " << i << "\n";
	      
	      G.build_type_table();
	      /*
	      std::cout << "typetable: n= "<< G.n_atom_types()<< "\n";
	      for (int j=0; j<G.size(); j++)
		std::cout << G.type_table(j) << " " << G.atom_of_type( G.type_table(j)) << "\n";
	      */
	      G.build_ngbr_disttable();

	      G.build_ngbr_table();

	      //	      std::cout << "ngbr\n";
	      G.setname(s.str());
	      qpp::write_xyz(f,G);
	      //for (int j=0; j<p.size(); j++)
	      //		std::cout << p[j].x << " " << p[j].y << "\n";
	    }
	}
    }
}
