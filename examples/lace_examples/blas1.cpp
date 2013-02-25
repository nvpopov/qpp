#include<lace/blas_mtr.hpp>
#include<lace/blas_vtr.hpp>
#include<iostream>

using namespace _lace_storage;

using _lace_expressions::sub;

int main()
{
  int N=10;
  vector_storage<double,dense> v(vector_shape(dense,N));

  for (int i=0; i<v.size(); i++)
    v(i) = i;

  for (int i=0; i<v.size(); i++)
    std::cout << v(i) << " ";
  std::cout << "\n";

  fill_vtr(v,11e0,sub(0,10,3));
  for (int i=0; i<v.size(); i++)
    std::cout << v(i) << " ";
  std::cout << "\n";

  scale_vtr(v,0.5);
  for (int i=0; i<v.size(); i++)
    std::cout << v(i) << " ";
  std::cout << "\n";
}
