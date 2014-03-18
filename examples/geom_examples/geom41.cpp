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

typedef lace::vector2d<double> v2d;
typedef lace::vector3d<double> v3d;

int main()
{
 
  qpp::geometry<0> G, G1;

  double a = 8, b = 4;
  //qpp::parametric_torus<double> mfold(a,b);
  //qpp::parametric_plane<double> mfold;
  qpp::parametric_sphere<double> mfold(b);

  int nn = int(2*qpp::pi*b/3);
  int m = int(2*qpp::pi*a/3);

  for (double theta = 0; theta < pi; theta += pi/nn)
    for (double phi = 0; phi < 2*pi; phi += 2*pi/m)
      G.add("C", mfold.parm2cart(theta,phi));

  v2d a1(0,0.1), a2(pi/4,pi/7);
  //v2d a1(-1,0), a2(-3,-2);
  double b1 = 3, b2=5, alp;

  std::vector<v2d> z;

  G.add("O",mfold.map(a1));
  G.add("O",mfold.map(a2));

  v3d r2 = mfold.map(a2), n = mfold.normal(a2), r1 = mfold.map(a1);

  r1 -= n*scal(r1-r2,n);

  G.add("F",r1);

  for (alp=0; alp<pi; alp+=.02)
    //for (b2=.3; b2<5; b2+=.4)
    {
      v2d a3 = mfold.protract(a1,a2,b2,alp);
      v3d r3 = mfold.map(a3);
      double aalp = mfold.surface_angle(a1,a2,a3);

      r3 -= n*scal(r3-r2,n);

      std::stringstream s;
      s  << alp*180/pi << " " << aalp*180/pi;
      G1.copy(G);
      G1.setname(s.str());
      G1.add("N",mfold.map(a3));
      G1.add("F",r3);
      qpp::write_xyz(std::cout,G1);
    }
  
}

