#include <iostream>
#include <typeinfo>
#include <geom/lace3d.hpp>
#include <symm/transform.hpp>

using namespace qpp;

int main()
{
  matrix4<double> A, I = matrix4<double>::Identity();
  A <<
    0,  1,  0, -2,
    1,  0,  0,  2,
    0,  0,  1,  0,
    0,  0,  0,  1;

  //std::cout << A << std::endl;
  //std::cout << A-I << std::endl;

  auto RR = rotrans<double>({2,1,0},RotMtrx<double>({0,0,1},pi/3));
  
  //A = rotrans4d(RR);
  //  A = -I;
  
  std::cout << A << std::endl;
 
  A = A - I;
  
  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> x = A.fullPivLu().kernel();
  //auto x = A.fullPivLu().kernel();
  for (int i=0; i< x.cols(); i++)
    x.col(i).normalize();

  std::cout << typeid(x).name() << std::endl;

  std::cout << x << std::endl;
  //std::cout << x << std::endl;
  //std::cout <<  A.fullPivLu().threshold() << std::endl;

  periodic_cell<double> cl({1,0,0},{0,1,0},{0,0,1});
  rotrans<double,true> r({.5,.5,.5}, RotMtrx({1,0,0},pi/4), &cl);

  auto r1 = rotrans_shift(r,{1,-1,0});
  std::cout << "r1= " << r1.T << r1.R << "\n";
}
