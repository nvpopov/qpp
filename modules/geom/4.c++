#include <iostream>
#include <boost/format.hpp>

double glob;

double f(double x)
{
  std::cout << boost::format("%12.8f\n") % glob;

  return glob = int(x);
}


int main()
{
  glob = 6;
  double x = 3.14;
  f(x);

  std::cout << glob << std::endl;
}
