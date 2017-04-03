#include <symm/index.hpp>
#include <iostream>
#include <ctime>
#include <cmath>

int main()
{
  
  std::clock_t t1 = std::clock();

  double x=0e0;
  for (qpp::iterator j({0,-100,-100,-100,0},{10,100,100,100,0}); !j.end(); j++)
    x += std::sin(j(0));

  //for (qpp::iterator j({0,-10,-10,-10,0},{10,10,10,10,0}); !j.end(); j++)
  //  {}
  //std::cout << j << std::endl;

  // std::cout << x << "\n";

  std::clock_t t2 = std::clock();
  double elapsed = double(t2 - t1) / CLOCKS_PER_SEC;

  std::cout << "Elpsed: " << elapsed << " x = " << x << "\n";

}
