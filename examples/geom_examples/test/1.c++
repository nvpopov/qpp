#include<iostream>
#include<geom/geom.hpp>

int main()
{
  qpp::simple_vector<int,5> a;

  for (int i=0; i<5; i++)
    a(i)=2*i+1;

  qpp::simple_vector<int,5> b(a);

  b = 2*a - a;

  for (int i=0; i<5; i++)
    std::cout << b(i) << " ";
  std::cout << "\n";
}
