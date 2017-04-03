#include <iostream>
#include <symm/transform.hpp>
#include <symm/cell.hpp>


int main()
{
  qpp::periodic_cell<double> cell(4,4,4,90,90,90);

  std::cout << cell.reduce({5,4,3}) << std::endl;

  /*
  qpp::translation<decltype(cell)> t({1,1,0}, &cell);

  std::cout << t.cell << std::endl;

  std::cout << t.T << " " << (t*t).T <<  " " << (t*t*t).T <<  " " << (t*t*t*t).T <<  " " << (t*t*t*t*t).T << std::endl;
  */
  qpp::rotrans<double> r({1,1,0}, qpp::RotMtrx({1,0,0},qpp::pi));

  std::cout << r.T << " " << (r*r).T <<  " " << (r*r*r).T <<  " " << (r*r*r*r).T <<  " " << (r*r*r*r*r).T << std::endl;
  std::cout << r.R << " " << (r*r).R <<  " " << (r*r*r).R <<  " " << (r*r*r*r).R <<  " " << (r*r*r*r*r).R << std::endl;
}

