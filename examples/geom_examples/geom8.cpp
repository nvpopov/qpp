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
#include <geom/zmt.hpp>

// Constructing molecule via Z-matrix on the parametric surface

using namespace qpp;

lace::vector2d<double> pt(double theta, double phi)
{
  return  lace::vector2d<double>(theta*qpp::pi/180, phi*qpp::pi/180);
}

int main()
{
 
  qpp::geometry<0> G, G1;
  std::vector<lace::vector2d<double> > parm;

  double a = 6, b = 3;
  qpp::parametric_torus<double> tor(a,b);

  qpp::zmatrix<double> z;

  /*
  z.add(qpp::zmt_record<double>("C"));
  z.add(qpp::zmt_record<double>("O", 0, 1.35 ));
  z.add(qpp::zmt_record<double>("O", 0, 1.20, 1, 125.1 ));
  z.add(qpp::zmt_record<double>("H", 1, 0.97, 0, 106.6, 2, 0 ));
  z.add(qpp::zmt_record<double>("H", 0, 1.10, 1, 109.5, 3, 180.0));
  */

  double RCC = 1.4, RXH = 2.4;
  z.add(qpp::zmt_record<double>("X"));
  z.add(qpp::zmt_record<double>("C", 0, RCC));
  z.add(qpp::zmt_record<double>("C", 0, RCC, 1, 60));
  z.add(qpp::zmt_record<double>("C", 0, RCC, 2, 60, 1, 180));
  z.add(qpp::zmt_record<double>("C", 0, RCC, 3, 60, 2, 180));
  z.add(qpp::zmt_record<double>("C", 0, RCC, 4, 60, 3, 180));
  z.add(qpp::zmt_record<double>("C", 0, RCC, 5, 60, 4, 180));
  z.add(qpp::zmt_record<double>("H", 0, RXH, 1, 60, 6, 180));
  z.add(qpp::zmt_record<double>("H", 0, RXH, 2, 60, 1, 180));
  z.add(qpp::zmt_record<double>("H", 0, RXH, 3, 60, 2, 180));
  z.add(qpp::zmt_record<double>("H", 0, RXH, 4, 60, 3, 180));
  z.add(qpp::zmt_record<double>("H", 0, RXH, 5, 60, 4, 180));
  z.add(qpp::zmt_record<double>("H", 0, RXH, 6, 60, 5, 180));


  int N = int(2*qpp::pi*(a+b)/6);

  for (int n=0; n<N; n++)
    z.zmt2surf(tor, pt(180,360.0*n/N),lace::vector2d<double>(1,0),-1, G, parm);
 
  /*  N = int(2*qpp::pi*(a-b)/6);

  for (int n=0; n<N; n++)
    z.zmt2surf(tor, pt(0,360.0*(n+.5)/N),lace::vector2d<double>(1,1),-1, G, parm);
  */

  N = int(2*qpp::pi*(a-.5*a)/6);

  for (int n=0; n<N; n++)
    {
      z.zmt2surf(tor, pt(60,360.0*n/N),lace::vector2d<double>(1,1),-1, G, parm);
      z.zmt2surf(tor, pt(-60,360.0*(n+.5)/N),lace::vector2d<double>(1,1),-1, G, parm);
    }
  /* 
  for (double theta = 0; theta < 2*pi; theta += 2*pi/n)
    for (double phi = 0; phi < 2*pi; phi += 2*pi/m)
      G.add("N", tor.parm2xyz(theta,phi));
  */

  /*
  z.zmt2cart(G);
  */
  write_xyz(std::cout,G);
 
}

