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

REAL R=3.85, rcc=1.4;
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

int progress( void *instance, const REAL *x, const REAL *g, REAL fx, REAL xnorm, REAL gnorm, 
	      REAL step, int n, int k, int ls)
{
  qpp::write_xyz(f,G);
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

//-------------------------------------------------------------------------------------------

int main()
{
  std::vector<v2d> p;

  //qpp::parametric_plane<REAL> plane;
  REAL R=4.2, r=1.7, rcc=1.4;

  //  qpp::parametric_torus<REAL> mfold(R,r);
  //  mfold.geomtol = 1e-4;
  /*
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

  //  REAL R=(1+std::sqrt(5.))*std::sqrt(3.)*rcc/4; //c20
  //REAL R=3.46; //c60
  //  REAL R=2.18; //c24
  //  REAL R = 4.20; //c720
  //REAL r = rcc*std::sqrt(1.5);

  //  int N=5;
  //  qpp::parametric_torus<REAL> mfold(R,r);
  //  qpp::parametric_mfoldere<REAL> mfold(R);
  //p.push_back(v2d(0,0));
  //p.push_back(mfold.ruler(p[0],v2d(0,1),rcc));
  //std::cout << "here11\n";

  //  p.push_back(mfold.protract(p[0],p[1],rcc,0.6*qpp::pi));
  //p.push_back(mfold.triangul(p[0],p[1],rcc,5*qpp::pi/7));
  //std::cout << "here12\n";
  p.push_back(v2d(qpp::pi/2,0));
  p.push_back(mfold.ruler(p[0],v2d(1,0),rcc));
  p.push_back(mfold.triangul(p[0],p[1],rcc,3*qpp::pi/5));
  
  for (int i=0; i<grph.nat(); i++)
    {
      //grph.coord(i).x() -= rcc/2;
      //grph.coord(i).y() -= sqrt(3.)*rcc/2;
      grph.coord(i).z() += r;
    }

  std::cout << "here2\n";

  std::ofstream gg("grph.xyz");
  qpp::write_xyz(gg, grph);
  

     
  /* for (int i=0; i<grph.nat(); i++)
    { 
      v2d p0 = mfold.project(grph.coord(i));
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
    G.add("C", mfold.map(p[i]) );


  std::cout << "here3\n";

  typedef qpp::zpattern<0,REAL> zpt;
  std::vector<zpt> zz(6);

  REAL rcc_min=1.2, rcc_max = 1.6,  amin = 102.0, amax = 140.0;
  //  REAL rxx = 2*rcc*std::sin(amax*qpp::pi/360);
  REAL rxx = 2.3;

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
     
    //    std::ofstream f("tor.xyz");
    qpp::write_xyz(f, G);
    
    G.ngbr.default_distance = 3.1;
    G.build_type_table();
    G.ngbr.build_disttable();
    G.ngbr.build();
    
    for (int i=0; i<zz.size();i++)
      {
	zz[i].init(mfold,p,G);
	//	zz[i].geomtol = 1e-3;
      }

    bool contin = true;
    
    while(contin)
      {

	if ( G.nat() > 10)
	  {
	    optimize_surf(p);
	    G.ngbr.build();
	  }
	

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
