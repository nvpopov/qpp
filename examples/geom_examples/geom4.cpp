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
  qpp::parametric_torus<double> tor(a,b);

  int n = int(2*qpp::pi*b/3);
  int m = int(2*qpp::pi*a/3);

  for (double theta = 0; theta < 2*pi; theta += 2*pi/n)
    for (double phi = 0; phi < 2*pi; phi += 2*pi/m)
      G.add("C", tor.parm2xyz(theta,phi));


  int nstep=200,
    nhlx=7,
    nrot=3;
  
  for (int i=0; i<nstep; i++)
    {
      double phi = 2*pi*i/nstep;
      double theta = nhlx*phi;
      lace::vector2d<double> n(std::cos(nrot*phi),std::sin(nrot*phi)), r;

      G1.copy(G);
      
      //      lace::vector2d<double> r0(theta,phi),r2;
      lace::vector2d<double> r0(qpp::pi,0),r2;
      G1.add("O", tor.d2d3(r0));

      r =  tor.ruler(r0, n, 0.3);
      
      r2 = tor.protractor(r,r0,0.5,nrot*phi);

      G1.add("N",tor.parm2xyz(r.x,r.y));
      G1.add("Al",tor.parm2xyz(r2.x,r2.y));

      std::stringstream s;
      s << nrot*phi*180/qpp::pi;
      G1.setname(s.str());

      write_xyz(std::cout,G1);
    }
  
}

