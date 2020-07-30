#include <iostream>
#include <symm/autosymm.hpp>
#include <mathf/math.hpp>

//using namespace qpp;

int main(){

  double a = 2.76;
  qpp::periodic_cell<double> cell({0,a,a}, {a,0,a}, {a,a,0});

  qpp::rotrans<double,true> r(
			      qpp::vector3<double>(0,a,a),
			      qpp::RotMtrx({0,0,1}, qpp::pi/6)*qpp::Sigma(qpp::vector3<double>(0,0,1)),
			      & cell);

  for (qpp::index I: qpp::inspect_rotrans(r,1e-5))
    std::cout << I << "\n";
}

