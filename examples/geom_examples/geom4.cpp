#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>
#include <boost/format.hpp>
#include<geom/atom.hpp>
#include<geom/geom.hpp>
//#include<geom/molecule.hpp>
#include<geom/manyfold.hpp>
//#include<io/molio.hpp>
#include <io/geomio.hpp>

// Parametric surface (torus) functionality

using namespace qpp;

lace::vector2d<double> pt(double theta, double phi)
{
  return  lace::vector2d<double>(theta*qpp::pi/180, phi*qpp::pi/180);
}

int main()
{
 
  qpp::geometry<0> G, G1;

  double a = 8, b = 4;
  //qpp::parametric_torus<double> mfold(a,b);
  qpp::parametric_sphere<double> mfold(b);

  int n = int(2*qpp::pi*b/3);
  int m = int(2*qpp::pi*a/3);

  for (double theta = 0; theta < pi; theta += pi/n)
    for (double phi = 0; phi < 2*pi; phi += 2*pi/m)
      G.add("C", mfold.parm2cart(theta,phi));


  int nstep=1000,
    nhlx=7,
    nrot=3;
  
  for (int i=0; i<nstep; i++)
    {
      double phi = 2*pi*i/nstep;
      double theta = nhlx*phi;
      lace::vector2d<double> r0(qpp::pi/4,0);
      lace::vector2d<double> g(mfold.gdiag(r0)),
	n(std::cos(nrot*phi)/g(0),std::sin(nrot*phi)/g(1)), r, r2;
      // lace::vector2d<double> n(1,nrot*phi), r;

      G1.copy(G);
      
      //      lace::vector2d<double> r0(theta,phi),r2;
      //      lace::vector2d<double> r0(qpp::pi,0),r2;
      //      lace::vector2d<double> r0(qpp::pi/2,0),r2;
      G1.add("O", mfold.map(r0));

      r =  mfold.ruler(r0, n, 1.3);
      
      r2 = mfold.triangul(r,r0, 3,nrot*phi);

      G1.add("N",mfold.map(r));
      G1.add("Al",mfold.map(r2));

      std::stringstream s;
      s << nrot*phi*180/qpp::pi;
      G1.setname(s.str());

      write_xyz(std::cout,G1);
    }
  
}

