#include <geom/shape.hpp>
#include <geom/geom.hpp>
#include <io/geomio.hpp>
#include <time.h>
#include <stdlib.h>

typedef qpp::vector3d<double> v3d;

double rnd()
{
  return rand() / (RAND_MAX + 1.);
}

void init_rand()
{
  srand(time(NULL));
}


int main()
{

  init_rand();

  qpp::shape_box<double> p1(v3d(2,0,0),v3d(0,1,0),v3d(0,0,1),"abc"), 
    p2({1,0,0},{0,2,0},{0,0,1});

  qpp::shape_sphere<double> s1(1),s2(1,v3d(1.5,0,0));    

  qpp::shape<double> & sh = s1 ^ s2;

  //sh.write(std::cout);
  //std::cout << "\n";

  qpp::geometry<double> g(0);

  qpp::vector3d<double> r1 = sh.rmin(), r2 = sh.rmax();
  int N = 1000000, N1=0;

  for (int i=0; i<N; i++)
    {
      qpp::vector3d<double> r;
      for (int j=0; j<3; j++)
	r(j) = r1(j) + rnd()*(r2(j)-r1(j));
      if (sh.within(r)) N1++;
	//	g.add("H",r);
    }

  double V = (r2(0)-r1(0))*(r2(1)-r1(1))*(r2(2)-r1(2))*N1/N;
  std::cout << N1 <<  " " << V << std::endl;

  //qpp::write_xyz(std::cout,g);

}
