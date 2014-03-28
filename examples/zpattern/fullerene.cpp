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
#include <stdlib.h>  
#include <lbfgs.h>

typedef double REAL;

typedef lace::vector2d<REAL> v2d;
typedef lace::vector3d<REAL> v3d;

//REAL R=5, r=2.42, rcc=1.45;
REAL R=4.25, r=1.7, rcc=1.45;
qpp::parametric_sphere<REAL> mfold(R);
qpp::geometry<0,REAL> G;
std::ofstream f("fl.xyz");

// -----------------------------------------------------------------------------------------

template< int DIM, class VALTYPE=REAL, class ATLABEL = std::string, class charT = char, 
	  class traits = std::char_traits<charT> >
VALTYPE gulp_energy(qpp::geometry<DIM,VALTYPE,ATLABEL,charT,traits> & geom, 
		    std::vector< lace::vector3d<VALTYPE> > & grad)
{
  std::ofstream f("coord.xyz");
  qpp::write_xyz(f,geom);
  f.close();
  system("gulp_script");

  std::ifstream dat("tor.dat");
  VALTYPE E;
  dat >> E;
  for (int i=0; i<geom.nat(); i++)
    dat >> grad[i](0) >> grad[i](1) >> grad[i](2);
  return E;
}

//-------------------------------------------------------------------------------------------

REAL surf_grad(void *instance, const REAL *x, REAL *g, const int n, const REAL step)
{

  //  std::cout << "surf_grad\n";
  //  qpp::write_xyz(f,G);

  for (int i=0; i<G.nat(); i++)
    {
      v2d p(x[2*i],x[2*i+1]);
      G.coord(i) = mfold.map(p);
    }

  //  std::cout << "surf_grad1\n";

  std::vector<v3d> grad(G.nat());
  REAL E = gulp_energy(G,grad);

  v3d sgrad(0e0,0e0,0e0);
  for (int i=0; i<G.nat(); i++)
    sgrad += grad[i];
 
  /* 
  std::cout << "Energy = " << E << "\n";
  for (int i=0; i<G.nat(); i++)
    std::cout << boost::format("%13.8f %13.8f %13.8f\n") % grad[i](0) % grad[i](1) % grad[i](2);  

  std::cout << boost::format("Sum grad = %13.8f %13.8f %13.8f\n") % sgrad(0) % sgrad(1) % sgrad(2);  
  */
  //  std::cout << "surf_grad2\n";

  for (int i=0; i<G.nat(); i++)
    {
      v2d pgrd(0e0,0e0);
      for (int j=0; j<2; j++)
	for (int k=0; k<3; k++)
	  //pgrd(j) += mfold.dx_dxi(x[2*i],x[2*i+1],k,j)*(grad[i](k) - sgrad(k)/G.nat());
	  pgrd(j) += mfold.dx_dxi(x[2*i],x[2*i+1],k,j)*grad[i](k);
      g[2*i] = pgrd(0);
      g[2*i+1] = pgrd(1);
    }

  /*
  std::cout << "2d gradients\n";
  for (int i=0; i<G.nat(); i++)
    std::cout << boost::format("%13.8f %13.8f\n") % g[2*i] %  g[2*i+1];
  std::cout << "\n\n";
  */
  //  std::cout << "surf_grad3\n";

  return E;
}

//-------------------------------------------------------------------------------------------

int iter=0;

int progress( void *instance, const REAL *x, const REAL *g, REAL fx, REAL xnorm, REAL gnorm, 
	      REAL step, int n, int k, int ls)
{
  if (iter==0)
    qpp::write_xyz(f,G);
  iter++;
  iter = iter%10;
  printf("Iteration %d:\n", k);
  printf("  fx = %f\n", fx);
  printf("  xnorm = %f, gnorm = %f, step = %f\n", xnorm, gnorm, step);
  printf("\n");
  return 0;    
}

//-------------------------------------------------------------------------------------------

void optimize_surf( std::vector< lace::vector2d<REAL> > & parm)
{
  lbfgs_parameter_t param;
  lbfgs_parameter_init(&param);
  param.gtol = 5e-1;
  param.xtol = 1e-3;
  param.min_step = 1e-4;
  param.max_iterations = 100;
  //  param.max_step = 1e-1;

  int N = 2*G.nat();
  REAL x[N];
  for (int i=0; i<G.nat(); i++)
    {
      x[2*i] = parm[i](0);
      x[2*i+1] = parm[i](1);
    }

  REAL energ;

  std::cout << "optimize_surf preparations done\n";
  std::cout << "max_step= " << param.max_step  << "min_step= " << param.min_step << "\n";

  int ret = lbfgs(N, x, &energ, surf_grad, progress, NULL, &param);

   for (int i=0; i<G.nat(); i++)
    {
      parm[i](0) = x[2*i];
      parm[i](1) = x[2*i+1];
      G.coord(i) = mfold.map(parm[i]);
    }
 
  
    /* Report the result. */
  printf("L-BFGS optimization terminated with status code = %d\n", ret);
  printf("  energ = %f\n", energ);
}

void conf1(std::vector<v2d> & p)
{
  REAL phi0 = std::asin(0.5*rcc/(R-r));
  p.push_back(v2d(0e0, phi0));
  p.push_back(v2d(0e0,-phi0));
  p.push_back(v2d(0e0,2*qpp::pi/3+phi0));
  p.push_back(v2d(0e0,2*qpp::pi/3-phi0));
  p.push_back(v2d(0e0,4*qpp::pi/3+phi0));
  p.push_back(v2d(0e0,4*qpp::pi/3-phi0));

  v2d p1 = mfold.triangul(p[0],p[1],rcc, 0.7*qpp::pi);
  p.push_back(p1);
  p.push_back(v2d(-p1.x, p1.y));
  p.push_back(v2d( p1.x,-p1.y));
  p.push_back(v2d(-p1.x,-p1.y));

  p1.y += 2*qpp::pi/3;
  p.push_back(p1);
  p.push_back(v2d(-p1.x, p1.y));
  p.push_back(v2d( p1.x,-p1.y));
  p.push_back(v2d(-p1.x,-p1.y));

  p1.y += 2*qpp::pi/3;
  p.push_back(p1);
  p.push_back(v2d(-p1.x, p1.y));
  p.push_back(v2d( p1.x,-p1.y));
  p.push_back(v2d(-p1.x,-p1.y));
  
  v2d p2 = mfold.triangul(p[9],p[11],rcc, 2*qpp::pi/3);
  p.push_back(p2);
  p.push_back(v2d(-p2.x, p2.y));
  p.push_back(v2d( p2.x,-p2.y));
  p.push_back(v2d(-p2.x,-p2.y));

  p2.y +=  2*qpp::pi/3;
  p.push_back(p2);
  p.push_back(v2d(-p2.x, p2.y));
  p.push_back(v2d( p2.x,-p2.y));
  p.push_back(v2d(-p2.x,-p2.y));

  p2.y +=  2*qpp::pi/3;
  p.push_back(p2);
  p.push_back(v2d(-p2.x, p2.y));
  p.push_back(v2d( p2.x,-p2.y));
  p.push_back(v2d(-p2.x,-p2.y));
}

//-------------------------------------------------

void conf0(std::vector<v2d> & p)
{
  p.push_back(v2d(qpp::pi/2,0));
  p.push_back(mfold.ruler(p[0],v2d(0,1),rcc));  
  p.push_back(mfold.triangul(p[0],p[1],rcc,3*qpp::pi/5));
}

//-------------------------------------------------------------------------------------------

int main()
{
  std::vector<v2d> p;

  //qpp::parametric_plane<REAL> plane;
  //  REAL R=4.2, r=1.7, rcc=1.4;

  //  qpp::parametric_torus<REAL> mfold(R,r);
  //  mfold.geomtol = 1e-4;
  /*
  p.push_back(v2d(qpp::pi/2,0));
  p.push_back(mfold.ruler(p[0],v2d(1,0),rcc));
  p.push_back(mfold.protract(p[0],p[1],rcc,2*qpp::pi/3));
  */

  qpp::geometry<2,REAL> uc;
  uc.cell(0) = v3d(3*rcc,0e0,0e0);
  uc.cell(1) = v3d(0e0,std::sqrt(3.)*rcc,0e0);
  
  uc.add("C",0,0,0);
  uc.add("C",-rcc/2,std::sqrt(3.)*rcc/2,0);
  uc.add("C",rcc,0,0);
  uc.add("C",1.5*rcc,std::sqrt(3.)*rcc/2,0);

  qpp::geometry<2,REAL>::iterator uci(qpp::index<2>(0,-10,-10),qpp::index<2>(3,10,10));

  qpp::geometry<0,REAL> grph;

  for (uci = uci.begin(); uci != uci.end(); uci++)
    grph.add("C",uc.full_coord(uci));


  std::cout << "here1\n";

  conf0(p);

  //  REAL R=(1+std::sqrt(5.))*std::sqrt(3.)*rcc/4; //c20
  //REAL R=3.46; //c60
  //  REAL R=2.18; //c24
  //  REAL R = 4.20; //c720
  //REAL r = rcc*std::sqrt(1.5);

  //  int N=5;
  //  qpp::parametric_torus<REAL> mfold(R,r);
  //  qpp::parametric_mfoldere<REAL> mfold(R);

  
  for (int i=0; i<grph.nat(); i++)
    {
      //grph.coord(i).x() -= rcc/2;
      //grph.coord(i).y() -= sqrt(3.)*rcc/2;
      grph.coord(i).z() += r;
    }

  std::cout << "here2\n";

  std::ofstream gg("grph.xyz");
  qpp::write_xyz(gg, grph);
  

  /*
  for (int i=0; i<grph.nat(); i++)
    { 
      v2d p0 = mfold.project(grph.coord(i));
      if ( qpp::pi/3 < p0(0) && 2*qpp::pi/3 > p0(0))
	{
	  p.push_back(p0);
	  //p.push_back(v2d(-p0.x,p0.y+qpp::pi));
	  //p0(0) *= -1;
	  //p0(1) += qpp::pi/6;
	  //p.push_back(p0);
	}
    }
  */
  for (int i=0; i<p.size(); i++)
    G.add("C", mfold.map(p[i]) );


  std::cout << "here3\n";

  typedef qpp::zpattern<0,REAL> zpt;
  std::vector<zpt*> zz,zd;

  REAL rcc_min=1.25, rcc_max = 1.6,  amin = 102.0, amax = 140.0;
  //  REAL rxx = 2*rcc*std::sin(amax*qpp::pi/360);
  REAL rxx = 2.3;

  std::cout << rxx << "\n";

  //  try {
  
  int iz=0;
  zpt zempt;
  
    //----------------------------------------------------------------------------
    iz = zz.size();
    zz.push_back(new zpt);
    zz[iz]->setname("1");
    
    zz[iz]->add_point(zpt::zpt_point("C1","C"),zpt::zsearch);
    zz[iz]->add_point(zpt::zpt_point("C2","C"),zpt::zsearch);
    zz[iz]->add_point(zpt::zpt_point("C3","C"),zpt::zsearch);
    zz[iz]->add_point(zpt::zpt_point("C4","C"),zpt::zinsert);
    zz[iz]->add_point(zpt::zpt_point("CX","C"),zpt::zavoid);
    zz[iz]->add_point(zpt::zpt_point("CN","C"),zpt::zavoid);
    
    zz[iz]->add_relation(* new zpt::bond_relation("C1","C2", rcc_min, rcc_max, *zz[iz]));
    zz[iz]->add_relation(* new zpt::bond_relation("C1","C3", rcc_min, rcc_max, *zz[iz]));
    zz[iz]->add_relation(* new zpt::surfangle_relation("C2","C1","C3", amin, amax, *zz[iz], "alpha"));
    
    zz[iz]->add_relation(* new zpt::bond_relation("C1","C4", *new zpt::linear_dependence(rcc,*zz[iz]), *zz[iz]));
    zz[iz]->add_relation(* new zpt::surfangle_relation("C2","C1","C4", 
						     (*new zpt::linear_dependence(180.,*zz[iz])).term("alpha",-0.5), *zz[iz]));
    zz[iz]->add_relation(* new zpt::surfangle_relation("C3","C1","C4", amin, amax, *zz[iz]));
    
    zz[iz]->add_relation(* new zpt::bond_relation("CX","C1", 0, rxx, *zz[iz]));
    zz[iz]->add_relation(* new zpt::dyhedral_relation("C1","C2","C3","CX", -60, 60, *zz[iz]));
    zz[iz]->add_relation(* new zpt::bond_relation("CN","C4", 0, rcc, *zz[iz]));
    //----------------------------------------------------------------------------
    iz = zz.size();
    zz.push_back(new zpt);
    zz[iz]->setname("2");

    zz[iz]->add_point(zpt::zpt_point("C1","C"),zpt::zsearch);
    zz[iz]->add_point(zpt::zpt_point("C2","C"),zpt::zsearch);
    zz[iz]->add_point(zpt::zpt_point("C3","C"),zpt::zsearch);
    zz[iz]->add_point(zpt::zpt_point("C4","C"),zpt::zinsert);
    zz[iz]->add_point(zpt::zpt_point("CX","C"),zpt::zavoid);
    zz[iz]->add_point(zpt::zpt_point("CN","C"),zpt::zavoid);
    
    zz[iz]->add_relation(* new zpt::bond_relation("C1","C2", rcc_min, rcc_max, *zz[iz]));
    zz[iz]->add_relation(* new zpt::bond_relation("C2","C3", rcc_min, rcc_max, *zz[iz]));
    zz[iz]->add_relation(* new zpt::surfangle_relation("C1","C2","C3", amin, amax, *zz[iz], "alpha"));
    
    zz[iz]->add_relation(* new zpt::bond_relation("C3","C4", *new zpt::linear_dependence(rcc,*zz[iz]), *zz[iz]));
    zz[iz]->add_relation(* new zpt::surfangle_relation("C2","C3","C4", 
						     (*new zpt::linear_dependence(0,*zz[iz])).term("alpha",1.), *zz[iz]));
    zz[iz]->add_relation(* new zpt::dyhedral_relation("C1","C2","C3","C4",-60,60,*zz[iz]));
    
    zz[iz]->add_relation(* new zpt::bond_relation("CX","C3", 0, rxx, *zz[iz]));
    zz[iz]->add_relation(* new zpt::dyhedral_relation("C1","C2","C3","CX", -60, 60, *zz[iz]));
    zz[iz]->add_relation(* new zpt::bond_relation("CN","C4", 0, rcc, *zz[iz]));
    //----------------------------------------------------------------------------
    iz = zz.size();
    zz.push_back(new zpt);
    zz[iz]->setname("3");

    zz[iz]->add_point(zpt::zpt_point("C1","C"),zpt::zsearch);
    zz[iz]->add_point(zpt::zpt_point("C2","C"),zpt::zsearch);
    zz[iz]->add_point(zpt::zpt_point("C3","C"),zpt::zsearch);
    zz[iz]->add_point(zpt::zpt_point("C4","C"),zpt::zinsert);
    zz[iz]->add_point(zpt::zpt_point("CX","C"),zpt::zsearch);
    zz[iz]->add_point(zpt::zpt_point("CXX","C"),zpt::zavoid);
    zz[iz]->add_point(zpt::zpt_point("CN","C"),zpt::zavoid);
    
    zz[iz]->add_relation(* new zpt::bond_relation("C1","C2", rcc_min, rcc_max, *zz[iz]));
    zz[iz]->add_relation(* new zpt::bond_relation("C1","C3", rcc_min, rcc_max, *zz[iz]));
    zz[iz]->add_relation(* new zpt::surfangle_relation("C2","C1","C3", amin, amax, *zz[iz], "alpha"));
    zz[iz]->add_relation(* new zpt::bond_relation("CX","C1", rcc_max, rxx, *zz[iz]));
    zz[iz]->add_relation(* new zpt::surfangle_relation("C2","C1","CX", 60, 180, *zz[iz]));
    
    zz[iz]->add_relation(* new zpt::bond_relation("C1","C4", *new zpt::linear_dependence(rcc,*zz[iz]), *zz[iz]));
    zz[iz]->add_relation(* new zpt::bond_relation("CX","C4", *new zpt::linear_dependence(rcc,*zz[iz]), *zz[iz]));
    zz[iz]->add_relation(* new zpt::surfangle_relation("C3","C1","C4", amin, amax, *zz[iz]));
    zz[iz]->add_relation(* new zpt::surfangle_relation("C2","C1","C4", amin, amax, *zz[iz]));
    zz[iz]->add_relation(* new zpt::surfangle_relation("C1","C4","CX", amin, amax, *zz[iz]));
        
    zz[iz]->add_relation(* new zpt::bond_relation("CXX","C1", 0, rxx, *zz[iz]));
    zz[iz]->add_relation(* new zpt::dyhedral_relation("C1","C2","C3","CXX", -60, 60, *zz[iz]));
    zz[iz]->add_relation(* new zpt::bond_relation("CN","C4", 0, rcc_min, *zz[iz]));
    //----------------------------------------------------------------------------
    iz = zz.size();
    zz.push_back(new zpt);
    zz[iz]->setname("4");

    zz[iz]->add_point(zpt::zpt_point("C1","C"),zpt::zsearch);
    zz[iz]->add_point(zpt::zpt_point("C2","C"),zpt::zsearch);
    zz[iz]->add_point(zpt::zpt_point("C3","C"),zpt::zsearch);
    zz[iz]->add_point(zpt::zpt_point("C4","C"),zpt::zinsert);
    zz[iz]->add_point(zpt::zpt_point("CX","C"),zpt::zsearch);
    zz[iz]->add_point(zpt::zpt_point("CXX","C"),zpt::zavoid);
    zz[iz]->add_point(zpt::zpt_point("CN","C"),zpt::zavoid);

    zz[iz]->add_relation(* new zpt::bond_relation("C1","C2", rcc_min, rcc_max, *zz[iz]));
    zz[iz]->add_relation(* new zpt::bond_relation("C2","C3", rcc_min, rcc_max, *zz[iz]));
    zz[iz]->add_relation(* new zpt::surfangle_relation("C1","C2","C3", amin, amax, *zz[iz], "alpha"));
    
    zz[iz]->add_relation(* new zpt::bond_relation("C3","C4", *new zpt::linear_dependence(rcc,*zz[iz]), *zz[iz]));
    zz[iz]->add_relation(* new zpt::bond_relation("CX","C4", *new zpt::linear_dependence(rcc,*zz[iz]), *zz[iz]));
    zz[iz]->add_relation(* new zpt::surfangle_relation("C2","C3","C4", amin, amax, *zz[iz]));
    zz[iz]->add_relation(* new zpt::surfangle_relation("C3","C4","CX", amin, amax, *zz[iz]));
    
    zz[iz]->add_relation(* new zpt::dyhedral_relation("C1","C2","C3","C4",-45,45,*zz[iz]));
    
    zz[iz]->add_relation(* new zpt::bond_relation("CX","C3", rcc_max, rxx, *zz[iz]));
    zz[iz]->add_relation(* new zpt::surfangle_relation("C2","C3","CX", 60, 180, *zz[iz]));
    zz[iz]->add_relation(* new zpt::bond_relation("CXX","C3", 0, rxx, *zz[iz]));
    zz[iz]->add_relation(* new zpt::dyhedral_relation("C1","C2","C3","CXX", -60, 60, *zz[iz]));
    zz[iz]->add_relation(* new zpt::bond_relation("CN","C4", 0, rcc_min, *zz[iz]));
    
    //----------------------------------------------------------------------------
    
    iz = zz.size();
    zz.push_back(new zpt);
    zz[iz]->setname("5");

    zz[iz]->add_point(zpt::zpt_point("C1","C"),zpt::zsearch);
    zz[iz]->add_point(zpt::zpt_point("C2","C"),zpt::zsearch);
    zz[iz]->add_point(zpt::zpt_point("C3","C"),zpt::zsearch);
    zz[iz]->add_point(zpt::zpt_point("C4","C"),zpt::zinsert);
    zz[iz]->add_point(zpt::zpt_point("CX","C"),zpt::zavoid);
    
    zz[iz]->add_relation(* new zpt::bond_relation("C1","C2", 1.9, 3.0, *zz[iz],"a"));
    zz[iz]->add_relation(* new zpt::bond_relation("C2","C3", 1.9, 3.0, *zz[iz],"b"));
    zz[iz]->add_relation(* new zpt::bond_relation("C3","C1", 1.9, 3.0, *zz[iz],"c"));
    
    zz[iz]->add_relation(* new zpt::bond_relation("C1","C4", 
						(*new zpt::linear_dependence(0,*zz[iz])).term("a",.192).term("b",.192).term("c",.192), *zz[iz]));
    zz[iz]->add_relation(* new zpt::bond_relation("C2","C4", 
						(*new zpt::linear_dependence(0,*zz[iz])).term("a",.192).term("b",.192).term("c",.192), *zz[iz]));
    zz[iz]->add_relation(* new zpt::bond_relation("C3","C4", 1.1, 1.8, *zz[iz]));
    
    zz[iz]->add_relation(* new zpt::bond_relation("CX","C4", 0, rxx, *zz[iz]));

    //----------------------------------------------------------------------------
    iz = zz.size();
    zz.push_back(new zpt);
    zz[iz]->setname("6");

    zz[iz]->add_point(zpt::zpt_point("C1","C"),zpt::zsearch);
    zz[iz]->add_point(zpt::zpt_point("C2","C"),zpt::zsearch);
    zz[iz]->add_point(zpt::zpt_point("C3","C"),zpt::zsearch);
    zz[iz]->add_point(zpt::zpt_point("C4","C"),zpt::zsearch);
    zz[iz]->add_point(zpt::zpt_point("C5","C"),zpt::zinsert);
    zz[iz]->add_point(zpt::zpt_point("CN","C"),zpt::zavoid);

    zz[iz]->add_relation(* new zpt::bond_relation("C1","C2", rcc_min, rcc_max, *zz[iz]));
    zz[iz]->add_relation(* new zpt::bond_relation("C3","C4", rcc_min, rcc_max, *zz[iz]));
    zz[iz]->add_relation(* new zpt::bond_relation("C2","C3", 1.9, 2.6, *zz[iz]));

    zz[iz]->add_relation(* new zpt::bond_relation("C2","C5",*new zpt::linear_dependence(rcc,*zz[iz]), *zz[iz]));
    zz[iz]->add_relation(* new zpt::bond_relation("C3","C5",*new zpt::linear_dependence(rcc,*zz[iz]), *zz[iz]));
    
    zz[iz]->add_relation(* new zpt::surfangle_relation("C1","C2","C5", amin, amax, *zz[iz]));
    zz[iz]->add_relation(* new zpt::surfangle_relation("C2","C5","C3", amin, amax, *zz[iz]));
    zz[iz]->add_relation(* new zpt::surfangle_relation("C5","C3","C4", amin, amax, *zz[iz]));
    zz[iz]->add_relation(* new zpt::dyhedral_relation("C1","C2","C3","C4", -60, 60, *zz[iz]));

    zz[iz]->add_relation(* new zpt::bond_relation("C5","CN", 0, rcc_min, *zz[iz]));

    // ---------------------------------------------------------------------------
    iz = zd.size();
    zd.push_back(new zpt);
    zd[iz]->setname("del square");
    
    zd[iz]->add_point(zpt::zpt_point("C1","C"),zpt::zdelete);
    zd[iz]->add_point(zpt::zpt_point("C2","C"),zpt::zdelete);
    zd[iz]->add_point(zpt::zpt_point("C3","C"),zpt::zdelete);
    zd[iz]->add_point(zpt::zpt_point("C4","C"),zpt::zdelete);
    
    zd[iz]->add_relation(* new zpt::bond_relation("C1","C2", 0, 1.8, *zd[iz]));
    zd[iz]->add_relation(* new zpt::bond_relation("C2","C3", 0, 1.8, *zd[iz]));
    zd[iz]->add_relation(* new zpt::bond_relation("C3","C4", 0, 1.8, *zd[iz]));
    zd[iz]->add_relation(* new zpt::bond_relation("C4","C1", 0, 1.8, *zd[iz]));
    zd[iz]->add_relation(* new zpt::surfangle_relation("C1","C2","C3", 70, 115, *zd[iz]));
    zd[iz]->add_relation(* new zpt::surfangle_relation("C2","C3","C4", 70, 115, *zd[iz]));
    zd[iz]->add_relation(* new zpt::surfangle_relation("C3","C4","C1", 70, 115, *zd[iz]));
    zd[iz]->add_relation(* new zpt::surfangle_relation("C4","C1","C2", 70, 115, *zd[iz]));
    // ---------------------------------------------------------------------------
    iz = zd.size();
    zd.push_back(new zpt);
    zd[iz]->setname("del cross");
    
    zd[iz]->add_point(zpt::zpt_point("C0","C"),zpt::zdelete);
    zd[iz]->add_point(zpt::zpt_point("C1","C"),zpt::zdelete);
    zd[iz]->add_point(zpt::zpt_point("C2","C"),zpt::zdelete);
    zd[iz]->add_point(zpt::zpt_point("C3","C"),zpt::zdelete);
    zd[iz]->add_point(zpt::zpt_point("C4","C"),zpt::zdelete);
    
    zd[iz]->add_relation(* new zpt::bond_relation("C1","C0", 0, rxx, *zd[iz]));
    zd[iz]->add_relation(* new zpt::bond_relation("C2","C0", 0, rxx, *zd[iz]));
    zd[iz]->add_relation(* new zpt::bond_relation("C3","C0", 0, rxx, *zd[iz]));
    zd[iz]->add_relation(* new zpt::bond_relation("C4","C0", 0, rxx, *zd[iz]));
    zd[iz]->add_relation(* new zpt::surfangle_relation("C1","C0","C2", 70, 115, *zd[iz]));
    zd[iz]->add_relation(* new zpt::surfangle_relation("C2","C0","C3", 70, 115, *zd[iz]));
    zd[iz]->add_relation(* new zpt::surfangle_relation("C3","C0","C4", 70, 115, *zd[iz]));
    zd[iz]->add_relation(* new zpt::surfangle_relation("C4","C0","C1", 70, 115, *zd[iz]));
    // ---------------------------------------------------------------------------
    iz = zd.size();
    zd.push_back(new zpt);
    zd[iz]->setname("del triangle");
    
    zd[iz]->add_point(zpt::zpt_point("C1","C"),zpt::zdelete);
    zd[iz]->add_point(zpt::zpt_point("C2","C"),zpt::zdelete);
    zd[iz]->add_point(zpt::zpt_point("C3","C"),zpt::zdelete);
    
    zd[iz]->add_relation(* new zpt::bond_relation("C1","C2", 0, 1.8, *zd[iz]));
    zd[iz]->add_relation(* new zpt::bond_relation("C2","C3", 0, 1.8, *zd[iz]));
    zd[iz]->add_relation(* new zpt::bond_relation("C3","C1", 0, 1.8, *zd[iz]));
    // ---------------------------------------------------------------------------
    iz = zd.size();
    zd.push_back(new zpt);
    zd[iz]->setname("del 2fold");
    
    zd[iz]->add_point(zpt::zpt_point("C0","C"),zpt::zdelete);
    zd[iz]->add_point(zpt::zpt_point("C1","C"),zpt::zdelete);
    zd[iz]->add_point(zpt::zpt_point("C2","C"),zpt::zdelete);
    zd[iz]->add_point(zpt::zpt_point("C3","C"),zpt::zsearch);    
    zd[iz]->add_point(zpt::zpt_point("C4","C"),zpt::zsearch);    
    
    zd[iz]->add_relation(* new zpt::bond_relation("C1","C0", 0, rcc_max, *zd[iz]));
    zd[iz]->add_relation(* new zpt::bond_relation("C2","C0", 0, rcc_max, *zd[iz]));
    zd[iz]->add_relation(* new zpt::bond_relation("C3","C0", rcc_max, rxx, *zd[iz]));
    zd[iz]->add_relation(* new zpt::bond_relation("C4","C0", rcc_max, rxx, *zd[iz]));
    zd[iz]->add_relation(* new zpt::dyhedral_relation("C1","C3","C2","C4", -60, 60, *zd[iz]));
    zd[iz]->add_relation(* new zpt::angle_relation("C0","C1","C3", 0, 90, *zd[iz]));
    zd[iz]->add_relation(* new zpt::angle_relation("C0","C1","C4", 0, 90, *zd[iz]));
    zd[iz]->add_relation(* new zpt::angle_relation("C0","C2","C3", 0, 90, *zd[iz]));
    zd[iz]->add_relation(* new zpt::angle_relation("C0","C2","C4", 0, 90, *zd[iz]));
    // ---------------------------------------------------------------------------

    qpp::init_rand();
    qpp::random_integer_lister lst,lst1,lst2;
     
    //    std::ofstream f("tor.xyz");
    qpp::write_xyz(f, G);
    
    G.ngbr.default_distance = 3.1;
    G.build_type_table();
    G.ngbr.build_disttable();
    G.ngbr.build();
    
    for (int i=0; i<zz.size();i++)
      zz[i]->init(mfold,p,G);

    for (int i=0; i<zd.size();i++)
      zd[i]->init(mfold,p,G);

    bool contin = true, contin1 = true, finished=false;;

    do{
      contin = true;
      while(contin)
	{
	  
	  if ( G.nat() > 20)
	    {
	      optimize_surf(p);
	      G.ngbr.build();
	    }
	  
	  
	  contin = false;
	  lst1.set(0,zz.size()-1);
	  for (int i=lst1.begin(); !lst1.end(); i=lst1.next())
	    {
	      if ( zz[i]->apply_surf( lst) )
		{
		  contin = true;
		  
		  std::stringstream s;
		  s << "pattern " << i << " = ";
		  for (int k=0; k<zz[i]->n_points(); k++)
		    s << " " << zz[i]->bound(k)+1;
		  
		  G.setname(s.str());
		  qpp::write_xyz(f,G);
		}
	    }
	  
	}

      finished = true;
      contin1 = true;
      while(contin1)
	{	  	  	  
	  contin1 = false;
	  lst1.set(0,zd.size()-1);
	  for (int i=lst1.begin(); !lst1.end(); i=lst1.next())
	    {
	      if ( zd[i]->apply_surf( lst) )
		{
		  contin1 = true;
		  finished = false;
		  
		  std::stringstream s;
		  s << "pattern " << i << " = ";
		  for (int k=0; k<zd[i]->n_points(); k++)
		    s << " " << zd[i]->bound(k)+1;
		  
		  G.setname(s.str());
		  qpp::write_xyz(f,G);
		}
	    }
	  
	}
    } while(!finished);


    //  }
    //  catch (qpp::qpp_exception<char> *e)
    //    { std::cout << e->what() << "\n";}
    /*
    std::cout << 
      LBFGSERR_LOGICERROR << "\n" <<
    LBFGSERR_OUTOFMEMORY << "\n" <<
    LBFGSERR_CANCELED << "\n" <<
    LBFGSERR_INVALID_N << "\n" <<
    LBFGSERR_INVALID_N_SSE << "\n" <<
    LBFGSERR_INVALID_X_SSE << "\n" <<
    LBFGSERR_INVALID_EPSILON << "\n" <<
    LBFGSERR_INVALID_TESTPERIOD << "\n" <<
    LBFGSERR_INVALID_DELTA << "\n" <<
    LBFGSERR_INVALID_LINESEARCH << "\n" <<
    LBFGSERR_INVALID_MINSTEP << "\n" <<
    LBFGSERR_INVALID_MAXSTEP << "\n" <<
    LBFGSERR_INVALID_FTOL << "\n" <<
    LBFGSERR_INVALID_WOLFE << "\n" <<
    LBFGSERR_INVALID_GTOL << "\n" <<
    LBFGSERR_INVALID_XTOL << "\n" <<
    LBFGSERR_INVALID_MAXLINESEARCH << "\n" <<
    LBFGSERR_INVALID_ORTHANTWISE << "\n" <<
    LBFGSERR_INVALID_ORTHANTWISE_START << "\n" <<
    LBFGSERR_INVALID_ORTHANTWISE_END << "\n" <<
    LBFGSERR_OUTOFINTERVAL << "\n" <<
      "INCORRECT_TMINMAX= " << LBFGSERR_INCORRECT_TMINMAX << "\n" <<
      "ROUNDING_ERROR= " << LBFGSERR_ROUNDING_ERROR << "\n" <<
    LBFGSERR_MINIMUMSTEP << "\n" <<
    LBFGSERR_MAXIMUMSTEP << "\n" <<
    LBFGSERR_MAXIMUMLINESEARCH << "\n" <<
    LBFGSERR_MAXIMUMITERATION << "\n" <<
    LBFGSERR_WIDTHTOOSMALL << "\n" <<
    LBFGSERR_INVALIDPARAMETERS << "\n" <<
      LBFGSERR_INCREASEGRADIENT << "\n";
    */
}
