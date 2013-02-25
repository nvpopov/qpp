#include<lace/blas_mtr.hpp>
#include<lace/blas_vtr.hpp>
#include<iostream>
#include<boost/format.hpp>

using namespace _lace_storage;

using _lace_expressions::sub;

int main()
{
  int N = 20;
  vector_storage<double,dense> v(N), u(N);

  fill_vtr(v,0e0);

  for (int i=0; i<N; i++)
    u(i) = i;

  std::cout << " ------- v -------\n";
  for (int i=0; i<N; i++)
    std::cout << boost::format("%8.3f")%v(i);
  std::cout << "\n";

  std::cout << " ------- u -------\n";
  for (int i=0; i<N; i++)
    std::cout << boost::format("%8.3f")%u(i);
  std::cout << "\n";

  add_vtr(v,sub(0,10,2),u,sub(1,15,3),1e0);

  std::cout << " ------- v -------\n";
  for (int i=0; i<N; i++)
    std::cout << boost::format("%8.3f")%v(i);
  std::cout << "\n";
}

