#include<lace/matrix.hpp>
#include<lace/vector.hpp>
#include<lace/wizard_instance.hpp>

using namespace _lace_expressions;
using namespace _lace_storage;
using _lace_main::wizard;

int main()
{
  int N=10;
  vector_expression<double> *v = &wizard<double>::V(dense).create(vector_shape(dense,N));

  for (int i=0; i<N; i++)
    {
      double *p = wizard<double>::V(dense).ptr(*v,i);
      if (p!=NULL)
	*p = i;
    }
  
  for (int i=0; i<N; i++) std::cout << *(wizard<double>::V(dense).ptr(*v,i)) << " ";
  std::cout << "\n";

  wizard<double>::V(dense).fill(*v,11e0,sub(3,6));

  for (int i=0; i<N; i++) std::cout << *(wizard<double>::V(dense).ptr(*v,i)) << " ";
  std::cout << "\n";

  wizard<double>::V(dense).scale(*v,.11111111111111e0,sub(1,10,2));

  for (int i=0; i<N; i++) std::cout << *(wizard<double>::V(dense).ptr(*v,i)) << " ";
  std::cout << "\n";

}

