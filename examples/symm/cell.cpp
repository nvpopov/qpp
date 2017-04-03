#include <symm/cell.hpp>
#include <iostream>

int main()
{
  qpp::periodic_cell<double> cl(2,2,4,90,90,60);

  for (int i=0; i<cl.DIM; i++)
    std::cout << cl.v[i] << std::endl;
}
