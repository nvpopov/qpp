#include<lace/blas_mtr.hpp>
#include<lace/blas_vtr.hpp>
#include<iostream>
#include<boost/format.hpp>
#include<lace/wizard_instance.hpp>
#include<lace/vector.hpp>
#include <lace/lace.hpp>

using namespace _lace_storage;
using namespace _lace_main;
using namespace _lace_expressions;

int main()
{
  int N = 20;
  //  vector_storage<double,dense> v(N), u(N);
  vector_expression<double> *u = & wizard<double>::V(dense).create(vector_shape(dense,N)),
    *v = & wizard<double>::V(dense).create(vector_shape(dense,N));

  //  fill_vtr(v,0e0);
  wizard<double>::V(dense).fill(*v,0e0);

  for (int i=0; i<N; i++)
    *(wizard<double>::V(dense).ptr(*u,i)) = i;

  std::cout << " ------- v -------\n";
  for (int i=0; i<N; i++)
    std::cout << boost::format("%8.3f")%*(wizard<double>::V(dense).ptr(*v,i));
  std::cout << "\n";

  std::cout << " ------- u -------\n";
  for (int i=0; i<N; i++)
    std::cout << boost::format("%8.3f")%*(wizard<double>::V(dense).ptr(*u,i));
  std::cout << "\n";

  //add_vtr(v,sub(0,10,2),u,sub(1,15,3),1e0);
  wizard<double>::VV(dense,dense).VpV(*v,sub(0,10,2),*u,sub(1,15,3),1e0);

  std::cout << " ------- v -------\n";
  for (int i=0; i<N; i++)
    std::cout << boost::format("%8.3f")%*(wizard<double>::V(dense).ptr(*v,i));
  std::cout << "\n";
}

