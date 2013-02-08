#include <iostream>
#include <lace/lace3d.hpp>

int main(){
  double a = 1, b=3, c=3.1, d=1.1;
  lace::vector3d<lace::dcomplex> x;
  x = lace::solve_cubeq<double>(a,b,c,d);
  std::cout << x <<"\n";
  for (int i=0; i<3; i++)
    std::cout << d+(c+(b+a*x(i))*x(i))*x(i) <<"\n";

}
