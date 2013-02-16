#ifndef _H_SIMPLE_PRN
#define _H_SIMPLE_PRN
#include <lace/lace.hpp>
#include <iostream>

namespace lace{
  
  template<class VALTYPE>
  class fmt
  {
  public:
    static std::string fm(VALTYPE x)
    { 
      std::stringstream ss;
      ss << boost::format("%10.5f ") % x;
      return ss.str();
    }
  };
  
  template<>
  class fmt<lace::dcomplex>
  {
  public:
    static std::string fm(lace::dcomplex x)
    {
      std::stringstream ss;
      ss << x << " ";
      return ss.str();
    }
  };
  
  template <matrix_type MT , class VALTYPE>
  void prnmtr(lace::matrix<VALTYPE,MT> &A)
  {
    for(int i=0; i<A.size(0); i++)
      {
	for(int j=0; j<A.size(1); j++)
	  std::cout <<  fmt<VALTYPE>::fm(A(i,j));
	std::cout << "\n";
      }
  }
  
  template <class VALTYPE,vector_type VT >
  void prnvtr(vector<VALTYPE,VT> &A)
  {
    for(int i=0; i<A.size(); i++)
      std::cout << boost::format("%10.5f ") % A(i);
    std::cout << "\n";
  }
  
};

#endif
