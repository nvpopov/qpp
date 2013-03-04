#include <cstring>
#include <iostream>
#include <lace/lace.hpp>
#include <boost/format.hpp>

using namespace lace;

template <class VALTYPE,_lace_storage::vector_type VT >
void prnvtr(_lace_expressions::vector<VALTYPE,VT> &A)
{
  for(int i=0; i<A.size(); i++)
    std::cout << boost::format("%10.5f ") % A(i);
  std::cout << "\n";
}

int main()
{
  vector<double,dense> u(10),v(5);

  for (int i=0; i<10; i++)
    u(i) = i+1;
  v = u(sub(0,9,2));
  prnvtr(v);
}