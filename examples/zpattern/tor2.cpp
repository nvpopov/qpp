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
#include <geom/geom_extras.hpp>
#include <io/geomio.hpp>
#include <stdlib.h>  
#include <lbfgs.h>

using qpp::pi;

typedef double REAL;

typedef lace::vector2d<REAL> v2d;
typedef lace::vector3d<REAL> v3d;

//REAL R=5, r=2.42, rcc=1.45;
REAL R=3.6, r=1.7, rcc=1.45;
qpp::parametric_surface<REAL> * mfold;
qpp::geometry<0,REAL> G;

#define DIM 0
typedef qpp::geometry<DIM,REAL,qpp::surf_symplicator<DIM,REAL> > surfgeom;
typedef qpp::zpattern<DIM,REAL,qpp::surf_symplicator<DIM,REAL> > zpt;

surfgeom * g;

// -----------------------------------------------------------------------------------------

template <int DIM2>
void g2G(surfgeom & g, qpp::geometry<DIM2,REAL> &G)
{
  G.clear();

  for (int i=0; i<g.nat(); i++)
    G.add(g.atom(i), g.position(i) );
  
  qpp::index<DIM> Ibgn, Iend(g.nat()-1);
  for (int d=0; d<DIM; d++)
    Iend.cell(d) = g.symm().order[d]-1;

  surfgeom::iterator I(Ibgn,Iend); 

  for ( I=I.begin(); I!=I.end(); I++ )
    if ( I != qpp::index<DIM>(I.atom()) )
      {
	lace::vector3d<double> r = g.position(I);
	bool found = false;
	for (int j=0; j<G.nat(); j++)
	  if ( G.atom(j)==g.atom(I) && norm(G.coord(j)-r) < g.geomtol)
	    {
	      found = true;
	      break;
	    }
	if (!found)
      G.add(g.atom(I), r );
      }
}

// -----------------------------------------------------------------------------------------

template< int DIM2, class VALTYPE=REAL>
VALTYPE gulp_energy(qpp::geometry<DIM2,VALTYPE> & geom, std::vector< lace::vector3d<VALTYPE> > & grad)
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

REAL surf_grad(void *instance, const REAL *x, REAL *grd, const int n, const REAL step)
{

  //  std::cout << "surf_grad\n";
  //  qpp::write_xyz(f,G);

  for (int i=0; i<g->nat(); i++)
    {
      g->coord(i) = v3d(x[2*i],x[2*i+1], 0);
    }

  g2G(*g,G);

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

  for (int i=0; i<g->nat(); i++)
    {
      v2d pgrd(0e0,0e0);
      for (int j=0; j<2; j++)
	for (int k=0; k<3; k++)
	  //pgrd(j) += mfold->dx_dxi(x[2*i],x[2*i+1],k,j)*(grad[i](k) - sgrad(k)/G.nat());
	  pgrd(j) += mfold->dx_dxi(x[2*i],x[2*i+1],k,j)*grad[i](k);
      grd[2*i] = pgrd(0);
      grd[2*i+1] = pgrd(1);
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
    qpp::write_xyz(std::cout,G);
  iter++;
  iter = iter%10;
  std::cerr<<boost::format("Iteration %d:\n")% k;
  std::cerr<<boost::format("  fx = %f\n")% fx;
  std::cerr<<boost::format("  xnorm = %f, gnorm = %f, step = %f\n")% xnorm % gnorm % step;
  std::cerr<<"\n";
  return 0;    
}

//-------------------------------------------------------------------------------------------

void optimize_surf( surfgeom & g)
{
  lbfgs_parameter_t param;
  lbfgs_parameter_init(&param);
  param.gtol = 5e-1;
  param.xtol = 1e-3;
  param.min_step = 1e-4;
  param.max_iterations = 100;
  //  param.max_step = 1e-1;

  int N = 2*g.nat();
  REAL x[N];
  for (int i=0; i<g.nat(); i++)
    {
      x[2*i] = g.coord(i)(0);
      x[2*i+1] = g.coord(i)(1);
    }

  REAL energ;

  std::cerr << "optimize_surf preparations done\n";
  std::cerr << "max_step= " << param.max_step  << "min_step= " << param.min_step << "\n";

  int ret = lbfgs(N, x, &energ, surf_grad, progress, NULL, &param);

  for (int i=0; i<g.nat(); i++)
    {
      g.coord(i)(0) = x[2*i];
      g.coord(i)(1) = x[2*i+1];

      g.symm().symmtrap(g.coord(i),1e-2);
    }
  
  g2G(g,G);
  
  // Report the result. 
  std::cerr<<boost::format("L-BFGS optimization terminated with status code = %d\n")%ret;
  std::cerr<<boost::format("  energ = %f\n")% energ;
}


/*
void conf2(std::vector<v2d> & p)
{
  REAL theta = std::asin(std::sqrt(3.0)*rcc/(4*r));
  REAL phi = std::asin(0.5*rcc/(R-r));

  p.push_back(v2d( theta, phi));
  p.push_back(v2d( theta,-phi));
  p.push_back(v2d( -theta, phi+qpp::pi));
  p.push_back(v2d( -theta,-phi+qpp::pi));
  p.push_back(v2d( -theta, phi+qpp::pi/3));
  p.push_back(v2d( -theta,-phi+qpp::pi/3));
  p.push_back(v2d(  theta, phi+2*qpp::pi/3));
  p.push_back(v2d(  theta,-phi+2*qpp::pi/3));
  p.push_back(v2d(  theta, phi-2*qpp::pi/3));
  p.push_back(v2d(  theta,-phi-2*qpp::pi/3));
  p.push_back(v2d( -theta, phi-qpp::pi/3));
  p.push_back(v2d( -theta,-phi-qpp::pi/3));

  v2d p1 = mfold->triangul(p[0],p[1],rcc,-2*qpp::pi/3);
  p.push_back(p1);
  p.push_back(v2d( p1.x, -p1.y));
  p.push_back(v2d(-p1.x, pi-p1.y));
  p.push_back(v2d(-p1.x, pi+p1.y));
  p.push_back(v2d( p1.x,  p1.y+2*pi/3));
  p.push_back(v2d( p1.x, -p1.y+2*pi/3));
  p.push_back(v2d( p1.x,  p1.y-2*pi/3));
  p.push_back(v2d( p1.x, -p1.y-2*pi/3));
  p.push_back(v2d(-p1.x,  p1.y+pi/3));
  p.push_back(v2d(-p1.x, -p1.y+pi/3));
  p.push_back(v2d(-p1.x,  p1.y-pi/3));
  p.push_back(v2d(-p1.x, -p1.y-pi/3));

  p.push_back(v2d(-p1.x, 0));  
  p.push_back(v2d( p1.x, pi));  
  p.push_back(v2d( p1.x, pi/3));  
  p.push_back(v2d( p1.x,-pi/3));  
  p.push_back(v2d(-p1.x, 2*pi/3));  
  p.push_back(v2d(-p1.x,-2*pi/3));  
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

  v2d p1 = mfold->triangul(p[0],p[1],rcc, 0.7*qpp::pi);
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
  
  v2d p2 = mfold->triangul(p[9],p[11],rcc, 2*qpp::pi/3);
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
*/

void conf1(surfgeom & g)
{
  v2d p0(0,0);
  v2d p1 = mfold->ruler(p0,v2d(0,1),rcc);  
  v2d p2 = mfold->ruler(p0,v2d(0,-1),rcc);  
  v2d p3 = mfold->ruler(p0,v2d(1, 0),rcc);  
  v2d p4 = mfold->ruler(p0,v2d(-1,0),rcc);  
  v2d p5 = mfold->triangul(p0,p3,rcc,2*pi/3);  

  g.add("C",p0.x,p0.y,0e0);
  g.add("C",p1.x,p1.y,0e0);
  g.add("C",p2.x,p2.y,0e0);
  g.add("C",p3.x,p3.y,0e0);
  g.add("C",p4.x,p4.y,0e0);
  g.add("C",p5.x,p5.y,0e0);

}

void conf0(surfgeom & g)
{
  v2d p0(0.3,0);
  v2d p1 = mfold->ruler(p0,v2d(.3,1),rcc);  
  v2d p2 = mfold->triangul(p0,p1,rcc,3*qpp::pi/5);
  g.add("C",p0.x,p0.y,0e0);
  g.add("C",p1.x,p1.y,0e0);
  g.add("C",p2.x,p2.y,0e0);
}

void conf2(surfgeom & g)
{
  v2d p0(0,1);
  v2d p1 = mfold->ruler(p0,v2d(.3,1),rcc);  
  v2d p2 = mfold->triangul(p0,p1,rcc, 3*qpp::pi/5);
  g.add("C",p0.x,p0.y,0e0);
}

//-------------------------------------------------------------------------------------------

template <int DIMM,class CREAL=double, class TRANSFORM = qpp::periodic_cell<DIMM,CREAL> >   
class zpt_array{
  
  std::vector<qpp::zpattern<DIMM,CREAL,TRANSFORM>*> zz;
  int _max_pri;
  std::vector<std::vector<int> > _pri;
  int _curr_pri, _last;

public:

  zpt_array()
  {
    _max_pri = 0;
  }
  
  void add(qpp::zpattern<DIMM,CREAL,TRANSFORM> & z)
  {
    zz.push_back(&z);

    std::cerr << z.name() << " " << z.priority << "\n";

    if (z.priority > _max_pri )
      _max_pri = z.priority;
    
    if (_pri.size()<_max_pri+1)
      _pri.resize(_max_pri+1);
    
    _pri[z.priority].push_back(zz.size()-1);
  }

  int nzpt()
  {
    return zz.size();
  }

  int maxpri()
  {
    return _max_pri;
  }

  int npri(int p)
  {
    return _pri[p].size();
  }

  int last()
  {
    return _last;
  }

  qpp::zpattern<DIMM,CREAL,TRANSFORM> & operator()(int i)
  {
    return *zz[i];
  }

  qpp::zpattern<DIMM,CREAL,TRANSFORM> & operator()(int p, int i)
  {
    return *zz[_pri[p][i]];
  }

  void init( qpp::geometry<DIMM, CREAL,TRANSFORM> &g, CREAL st_rad = 0e0)
  {
    for (int i=0; i<zz.size(); i++)
      zz[i]->init(g,st_rad);
    _curr_pri = 0;
  }

  void init_surf( qpp::geometry<DIMM, CREAL,TRANSFORM> &g, CREAL st_rad = 0e0)
  {
    for (int i=0; i<zz.size(); i++)
      zz[i]->init_surf(g,st_rad);
    _curr_pri = 0;
  }

  void reset()
  {
    _curr_pri=0;
  }

  bool apply(qpp::integer_lister &lst)
  {
    qpp::integer_lister * lst1 = lst.copy();
    bool res = false;

    while (_curr_pri <= _max_pri)
      {
	lst1->set(0,npri(_curr_pri)-1);
	for (int i=lst1->begin(); !lst1->end(); i=lst1->next())
	  if ( (*this)(_curr_pri,i).apply(lst) )
	    {
	      res = true;
	      _last = _pri[_curr_pri][i];
	      reset();
	      break;
	    }
	if (res)
	  break;

	_curr_pri++;
      }

    delete lst1;
    return res;
  }

};

//-------------------------------------------------------------------------------------------

int main(int argc, char* argv[])
{
  try{  
  R = atof(argv[1]);
  r = atof(argv[2]);
  std::ifstream zinp(argv[3]);
  
  mfold = new qpp::parametric_torus<REAL>(R,r);
  //mfold = new qpp::parametric_sphere<REAL>(R);

  qpp::surf_symplicator<DIM,REAL> symm(*mfold);  
  g = new surfgeom(symm);
  g->geomtol = 1e-5;

  conf0(*g);
  g2G(*g,G);

  //  std::vector<zpt*> zz;

  std::vector<qpp::qpp_object*> decls;
  qpp::qpp_read(zinp,decls);

  zpt_array<DIM,REAL,qpp::surf_symplicator<DIM,REAL> > zz;

  std::cerr << "alive\n";

  for (int i=0; i<decls.size(); i++)
    if (decls[i]-> category() == "zpattern")
      zz.add(*qpp::decl2zpt<DIM, REAL, qpp::surf_symplicator<DIM,REAL> >
	     ((qpp::qpp_declaration*)decls[i]));

  std::cerr << "alive1\n";

  qpp::init_rand();
  qpp::random_integer_lister lst;
     
  qpp::write_xyz(std::cout, G);
  
  //  for (int i=0; i<zz.size();i++)
  zz.init_surf(*g, 0.8);

  bool contin=true, opted=false;
  
  int natopt=0;

  while(contin)
    {	
      contin = false;
      if (zz.apply(lst))
	{
	  contin = true;
	  opted = false;
	  
	  g2G(*g,G);
	  std::stringstream s;
	  int i = zz.last();

	  s << "pattern " << i << " pri= " << zz(i).priority << " "  << zz(i).name() << " = ";
	  for (int k=0; k<zz(i).n_points(); k++)
	    s << " " << zz(i).bound(k)+1;
	  
	  G.setname(s.str());
	  qpp::write_xyz(std::cout,G); 
	}

      if ( G.nat() - natopt > 7 || (!contin && !opted))
	{
	  optimize_surf(*g);
	  natopt = G.nat();
	  opted = true;
	  contin = true;
	  zz.reset();
	} 
     
      /*      lst1.set(0,zz.size()-1);
      for (int i=lst1.begin(); !lst1.end(); i=lst1.next())
	{
	  if ( zz[i]->apply( lst) )
	    {
	      contin = true;
	      opted = false;
	      
	      g2G(*g,G);
	      std::stringstream s;
	      s << "pattern " << i << " " << zz[i]->name() << " = ";
	      for (int k=0; k<zz[i]->n_points(); k++)
		s << " " << zz[i]->bound(k)+1;
	      
	      G.setname(s.str());
	      qpp::write_xyz(std::cout,G);
	    }
	}
      */
      //if ( G.nat() - natopt > 10)


    }    
  }
  catch (qpp::qpp_exception & e)
    {
      std::cerr << e.what() << "\n";
      exit(1);
    }
}
